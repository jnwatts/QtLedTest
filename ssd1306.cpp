#include "ssd1306.h"
#include "ui_ssd1306.h"

SSD1306::SSD1306(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SSD1306)
{
    ui->setupUi(this);

    this->ui->ledMatrix->setBackgroundMode(Qt::TransparentMode);

    setPixelOnColor(QLedMatrix::White);
    setPixelOffColor(this->ui->ledMatrix->darkLedColor().rgb());
    this->setDisplayResolution(128, 32);
    _reset();
}

SSD1306::~SSD1306()
{
    delete ui;
}

void SSD1306::setPixelOnColor(QRgb color)
{
    onColor = color;
}

void SSD1306::setPixelOffColor(QRgb color)
{
    offColor = color;
}

void SSD1306::setDisplayResolution(int columns, int rows)
{
    if (columns < 128)
        columns = 128;
    if (rows < 32)
        rows = 32;
    this->ui->ledMatrix->setColumnCount(columns);
    this->ui->ledMatrix->setRowCount(rows);
    ram.resize(numColumns() * numPages());
}

void SSD1306::setCSn(bool CSn)
{
    _CSn = CSn;
}

void SSD1306::putByte(bool D_Cn, uint8_t D0_7)
{
    if (!_CSn) {
        if (D_Cn) {
            _processDataByte(D0_7);
        } else {
            _processCommandByte(D0_7);
        }
    }
    _update();
}

void SSD1306::setPixel(int x, int y, int value)
{
    this->ui->ledMatrix->setColorAt(y, x, (value == 0 ? offColor : onColor));
}

int SSD1306::numColumns()
{
    return this->ui->ledMatrix->columnCount();
}

int SSD1306::numPages()
{
    return this->ui->ledMatrix->rowCount() / 8;
}

void SSD1306::_reset()
{
    _command_state = CS_IDLE;
    _CSn = true;
    
    reg[REG_ENTIRE_DISPLAY_ON] = 0;
    reg[REG_NORMAL_INVERSE] = 0;
    reg[REG_DISPLAY_ON_OFF] = 0;
    reg[REG_MEM_ADDR_MODE] = 0x02;
    reg[REG_COL_ADDR_START] = 0;
    reg[REG_COL_ADDR_STOP] = 127;
    reg[REG_PAGE_ADDR_START] = 0;
    reg[REG_PAGE_ADDR_STOP] = 7;
    reg[REG_PAGE_START_ADDR] = 0;
    
    for (int page = 0; page < numPages(); ++page) {
        for (int col = 0; col < numColumns(); ++col) {
            ram[page * numColumns() + col] = 0x00;
        }
    }
}

void SSD1306::_update()
{
    for (int page = 0; page < numPages(); ++page) {
        for (int col = 0; col < numColumns(); ++col) {
            uint8_t data = ram[page * numColumns() + col];
            for (int y = 0; y < 8; ++y) {
                int row = page * 8 + y;
                bool value = false;
                if (reg[REG_DISPLAY_ON_OFF]) {
                    if (reg[REG_ENTIRE_DISPLAY_ON]) {
                        value = true;
                    } else {
                        value = (data & (1 << y));
                        if (reg[REG_NORMAL_INVERSE])
                            value = !value;
                    }
                }
                if (row < this->ui->ledMatrix->rowCount() && col < this->ui->ledMatrix->columnCount())
                    this->ui->ledMatrix->setColorAt(row, col, (value ? onColor : offColor));
            }
        }
    }
}

void SSD1306::_processDataByte(uint8_t d)
{
    ram[_getOffset(true)] = d;
}

void SSD1306::_processCommandByte(uint8_t d)
{
    switch (_command_state) {
    case CS_IDLE:
        if ((d & 0xF0) == 0x20) {
            if (d == CMD_SET_MEM_ADDR_MODE) {
                _command_state = CS_ONE_ARG;
                _cur_cmd = d;
            } else if (d == CMD_SET_COL_ADDR || d == CMD_SET_PAGE_ADDR) {
                _command_state = CS_TWO_ARG;
                _cur_cmd = d;
            }
        } else {
            bool handled = true;
            switch (d & 0xFE) {
            case CMD_SET_ENTIRE_DISPLAY_ON:
                reg[REG_ENTIRE_DISPLAY_ON] = d & 0x01;
                break;
            case CMD_SET_NORMAL_INVERSE:
                reg[REG_NORMAL_INVERSE] = d & 0x01;
                break;
            case CMD_SET_DISPLAY_ON_OFF:
                reg[REG_DISPLAY_ON_OFF] = d & 0x01;
                break;
            default:
                handled = false;
                break;
            }
            if (handled)
                break;
            
            handled = true;
            switch (d & 0xF8) {
            case CMD_SET_PAGE_START_ADDR:
                reg[REG_PTR_PAGE] = d & 0x03;
                break;
            default:
                handled = false;
            }
            if (handled)
                break;
            
            handled = true;
            switch (d & 0xF0) {
            case CMD_SET_LOW_COL_START:
                reg[REG_PTR_COL] &= 0x0F;
                reg[REG_PTR_COL] |= d & 0x0F;
                break;
            case CMD_SET_HIGH_COL_START:
                reg[REG_PTR_COL] &= 0xF0;
                reg[REG_PTR_COL] |= (d << 4) & 0xF0;
                break;
                //TODO: More commands
            default:
                handled = false;
                break;
            }
            if (handled)
                break;
        }
        break;
    case CS_ONE_ARG:
        _cur_args[0] = d;
        switch (_cur_cmd) {
        case CMD_SET_MEM_ADDR_MODE:
            // A is index 0
            reg[REG_MEM_ADDR_MODE] = _cur_args[0] & 0x07;
            break;
        case CMD_SET_COL_ADDR:
            // A is index 1
            reg[REG_COL_ADDR_START] = _cur_args[1] & 0x7F;
            // B is index 0
            reg[REG_COL_ADDR_STOP] = _cur_args[0] & 0x7F;
            // Reset PTR_COL
            reg[REG_PTR_COL] = reg[REG_COL_ADDR_START];
            break;
        case CMD_SET_PAGE_ADDR:
            // A is index 1
            reg[REG_PAGE_ADDR_START] = _cur_args[1] & 0x7F;
            // B is index 0
            reg[REG_PAGE_ADDR_STOP] = _cur_args[0] & 0x7F;
            // Reset PTR_PAGE
            reg[REG_PTR_PAGE] = reg[REG_PAGE_ADDR_START];
            break;
        }
        _command_state = CS_IDLE;
        break;
    case CS_TWO_ARG:
        _command_state = CS_ONE_ARG;
        _cur_args[1] = d;
        break;
    default:
        break;
    }
}

void SSD1306::_resetCommandState()
{
    _command_state = CS_IDLE;
}

int SSD1306::_getOffset(bool increment)
{
    int offset = reg[REG_PTR_PAGE] * numColumns() + reg[REG_PTR_COL];
    
    if (increment) {
        // Increment pointer and check bounds
        switch (reg[REG_MEM_ADDR_MODE]) {
        case REGVAL_MEM_ADDR_MODE_PAGE:
            reg[REG_PTR_COL]++;
            if (reg[REG_PTR_COL] > reg[REG_COL_ADDR_STOP]) {
                reg[REG_PTR_COL] = reg[REG_COL_ADDR_START];
            }
            break;
        case REGVAL_MEM_ADDR_MODE_HORIZ:
            reg[REG_PTR_COL]++;
            if (reg[REG_PTR_COL] > reg[REG_COL_ADDR_STOP]) {
                reg[REG_PTR_COL] = reg[REG_COL_ADDR_START];
                reg[REG_PTR_PAGE]++;
                if (reg[REG_PTR_PAGE] > reg[REG_PAGE_ADDR_STOP]) {
                    reg[REG_PTR_PAGE] = reg[REG_PAGE_ADDR_START];
                }
            }
            break;
        case REGVAL_MEM_ADDR_MDOE_VERT:
            reg[REG_PTR_PAGE]++;
            if (reg[REG_PTR_PAGE] > reg[REG_PAGE_ADDR_STOP]) {
                reg[REG_PTR_PAGE] = reg[REG_PAGE_ADDR_START];
                reg[REG_PTR_COL]++;
                if (reg[REG_PTR_COL] > reg[REG_COL_ADDR_STOP]) {
                    reg[REG_PTR_COL] = reg[REG_COL_ADDR_START];
                }
            }
            break;
        }
    }
    if (offset < numColumns() * numPages())
        return offset;
    else
        return 0;
}
