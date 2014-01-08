/*
 * This file is part of QtLedTest.
 *
 * QtLedTest is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QtLedTest is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QtLedTest.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QThread>
#include "ssd1306.h"
#include "ssd1306_worker.h"
#include "ui_ssd1306.h"

SSD1306::SSD1306(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SSD1306),
    _work(NULL)
{
    ui->setupUi(this);

    _realistic = true;
    _RSTn = false;
    _CSn = true;
    _enabled = false;

//    this->ui->ledMatrix->setBackgroundMode(Qt::TransparentMode);

    setPixelOnColor(QLedMatrix::White);
    setPixelOffColor(this->ui->ledMatrix->darkLedColor().rgb());
    this->setDisplayResolution(128, 32);
    _work = new SSD1306_Worker(this);
    connect(_work, SIGNAL(update_display(int)), this, SLOT(_update_display(int)));
    connect(this, SIGNAL(submitByte(bool,uint8_t)), _work, SLOT(receiveByte(bool,uint8_t)));
    _work->start();
    _reset();
}

SSD1306::~SSD1306()
{
    if (_work)
        delete _work;
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

void SSD1306::setRealistic(bool realistic)
{
    _realistic = realistic;
    _work->setEnabled(realistic);
}

bool SSD1306::realistic(void)
{
    return _realistic;
}

void SSD1306::setRSTn(bool RSTn)
{
    if (_RSTn && !RSTn) {
        // Falling edge
        _setEnabled(false);
        _reset();
    } else if (!_RSTn && RSTn) {
        // Rising edge
        _setEnabled(true);
    }
    _RSTn = RSTn;
}

void SSD1306::setCSn(bool CSn)
{
    _CSn = CSn;
}

void SSD1306::putByte(bool D_Cn, uint8_t D0_7)
{
    if (_realistic) {
        emit submitByte(D_Cn, D0_7);
    } else {
        _processByte(D_Cn, D0_7);
    }
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

int SSD1306::maxOffset()
{
    return numColumns() * numPages();
}

void SSD1306::_update_display(int offset)
{
    uint8_t data = ram[offset];
    int col = offset % numColumns();
    int page = offset / numColumns();
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

void SSD1306::_reset()
{
    _command_state = CS_IDLE;
    _CSn = true;
    
    reg[REG_CONTRAST_CONTROL] = 0x7F;
    reg[REG_ENTIRE_DISPLAY_ON] = 0;
    reg[REG_NORMAL_INVERSE] = 0;
    reg[REG_DISPLAY_ON_OFF] = 0;
    reg[REG_MEM_ADDR_MODE] = 0x02;
    reg[REG_COL_ADDR_START] = 0;
    reg[REG_COL_ADDR_STOP] = 127;
    reg[REG_PAGE_ADDR_START] = 0;
    reg[REG_PAGE_ADDR_STOP] = 7;
    reg[REG_PAGE_START_ADDR] = 0;
    reg[REG_MULTIPLEX_RATIO] = 63;
    reg[REG_DISPLAY_CLOCK_DIVIDE_RATIO] =  0;

    disp_ptr_page = mem_ptr_page = reg[REG_PAGE_ADDR_START];
    disp_ptr_col = mem_ptr_col = reg[REG_COL_ADDR_START];
    
    for (int page = 0; page < numPages(); ++page) {
        for (int col = 0; col < numColumns(); ++col) {
            ram[page * numColumns() + col] = 0x00;
        }
    }
}

void SSD1306::_setEnabled(bool value)
{
    _enabled = value;
}

void SSD1306::_update()
{
    for (int page = 0; page < numPages(); ++page) {
        for (int col = 0; col < numColumns(); ++col) {
            _update_display(page * numColumns() + col);
        }
    }
}

bool SSD1306::_processByte(bool D_Cn, uint8_t D0_7)
{
    bool ret = false;
    if (!_CSn) {
        if (D_Cn) {
            ret = _processDataByte(D0_7);
        } else {
            ret = _processCommandByte(D0_7);
        }
    }
    return ret;
}

bool SSD1306::_processDataByte(uint8_t d)
{
    int offset = _getOffset(mem_ptr_page, mem_ptr_col);
    ram[offset] = d;
    _increment(&mem_ptr_page, &mem_ptr_col, reg[REG_MEM_ADDR_MODE]);
    if (!_realistic)
        _update_display(offset);
    return true;
}

bool SSD1306::_processCommandByte(uint8_t d)
{
    bool handled = false;
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
            handled = true;
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
                mem_ptr_page = d & 0x03;
                break;
            default:
                handled = false;
            }
            if (handled)
                break;
            
            handled = true;
            switch (d & 0xF0) {
            case CMD_SET_LOW_COL_START:
                mem_ptr_col &= 0x0F;
                mem_ptr_col |= d & 0x0F;
                break;
            case CMD_SET_HIGH_COL_START:
                mem_ptr_col &= 0xF0;
                mem_ptr_col |= (d << 4) & 0xF0;
                break;
                //TODO: More commands
            default:
                handled = false;
                break;
            }
        }
        break;
    case CS_ONE_ARG:
        _cur_args[0] = d;
        handled = true;
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
            mem_ptr_col = reg[REG_COL_ADDR_START];
            break;
        case CMD_SET_PAGE_ADDR:
            // A is index 1
            reg[REG_PAGE_ADDR_START] = _cur_args[1] & 0x7F;
            // B is index 0
            reg[REG_PAGE_ADDR_STOP] = _cur_args[0] & 0x7F;
            // Reset PTR_PAGE
            mem_ptr_page = reg[REG_PAGE_ADDR_START];
            break;
        default:
            handled = false;
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
    return handled;
}

void SSD1306::_resetCommandState()
{
    _command_state = CS_IDLE;
}

void SSD1306::_emit_FR(bool active)
{
    emit FR(active);
}

float SSD1306::_framePeriod(void)
{
    float frame_rate = _getFosc() / ( (float)(reg[REG_DISPLAY_CLOCK_DIVIDE_RATIO] + 1) * (2.0 + 2.0 + (float)(50 + reg[REG_CONTRAST_CONTROL])) * (float)(reg[REG_MULTIPLEX_RATIO] + 1) );
    float frame_period = 1.0 / frame_rate;
    return frame_period;
}

float SSD1306::_displayPeriod()
{
    float display_rate = _getFosc() / (float)(reg[REG_DISPLAY_CLOCK_DIVIDE_RATIO] + 1);
    float display_period = 1.0 / display_rate;
    return display_period;
}

int SSD1306::_getFosc()
{
    //TODO: Allow changing of this based on CL (setExtClockRate()) and CLS pins
    return 370000;
}

int SSD1306::_getOffset(int page, int col)
{
    int offset = page * numColumns() + col;
    if (offset < maxOffset())
        return offset;
    else
        return 0;
}

bool SSD1306::_increment(int *page, int *col, int mode)
{
    bool ret = false;
    switch (mode) {
    case REGVAL_MEM_ADDR_MODE_PAGE:
        if (++*col > reg[REG_COL_ADDR_STOP]) {
            *col = reg[REG_COL_ADDR_START];
            ret = true;
        }
        break;
    case REGVAL_MEM_ADDR_MODE_HORIZ:
        if (++*col > reg[REG_COL_ADDR_STOP]) {
            *col = reg[REG_COL_ADDR_START];
            if (++*page > reg[REG_PAGE_ADDR_STOP]) {
                *page = reg[REG_PAGE_ADDR_START];
                ret = true;
            }
        }
        break;
    case REGVAL_MEM_ADDR_MDOE_VERT:
        if (++*page > reg[REG_PAGE_ADDR_STOP]) {
            *page = reg[REG_PAGE_ADDR_START];
            if (++*col > reg[REG_COL_ADDR_STOP]) {
                *col = reg[REG_COL_ADDR_START];
                ret = true;
            }
        }
        break;
    }
    return ret;
}
