#include "mainwindow.h"
#include "graphics.h"
#include "ssd1306.h"
#include "ui_mainwindow.h"
#include "font_data/font_list.h"

const int MainWindow::COLOR_OFF = 0;
const int MainWindow::COLOR_ON = 1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    font(&font_pixel_unicode_regular_12)
{
    gpu_mem = NULL;
    ui->setupUi(this);
    resize();
    this->ui->oled->setPixelOnColor(QColor(Qt::cyan).rgb());
    
    display_offset = 0;

    FontDescription *fd = &fonts[0];
    while (fd->name) {
        this->ui->tabFont->addItem(fd->name);
        fd++;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabFont_currentIndexChanged(int index)
{
    font = fonts[index].info;
}

void MainWindow::render()
{
    this->ui->oled->setDisplayResolution(displayRes.width(), displayRes.height());
    this->ui->oled->setCSn(false);
    this->ui->oled->putByte(false, SSD1306::CMD_SET_DISPLAY_ON_OFF | 0x01);
    this->ui->oled->putByte(false, SSD1306::CMD_SET_MEM_ADDR_MODE);
    this->ui->oled->putByte(false, SSD1306::REGVAL_MEM_ADDR_MODE_HORIZ);

    if (font) {
        Graphics_setFill(gh, COLOR_OFF);
        Graphics_setPen(gh, COLOR_ON);
        Graphics_fillRect(gh, 0, 0, displayRes.width(), displayRes.height());
        int w, h;
        int x, y;
        x = 2;
        Graphics_measureString(gh, font, "ABC", &w, &h);
        y = displayRes.height() - h;
        Graphics_drawTab(gh, x, y, w + 2, h, 2, true, false);
        Graphics_drawString(gh, font, "ABC", x + 1, y);
        x += w + 4;
        Graphics_measureString(gh, font, "DEF", &w, &h);
        Graphics_drawTab(gh, x, y, w + 2, h, 2, true, false);
        Graphics_drawString(gh, font, "DEF", x + 1, y);
    }
}

void MainWindow::update()
{
    this->ui->oled->putByte(false, SSD1306::CMD_SET_PAGE_ADDR);
    this->ui->oled->putByte(false, 0);
    this->ui->oled->putByte(false, this->ui->oled->numPages() - 1);
    this->ui->oled->putByte(false, SSD1306::CMD_SET_COL_ADDR);
    this->ui->oled->putByte(false, 0);
    this->ui->oled->putByte(false, this->ui->oled->numColumns() - 1);
    for (int o = 0; o < this->ui->oled->numColumns() * this->ui->oled->numPages(); ++o) {
        this->ui->oled->putByte(true, gpu_mem[display_offset + o]);
    }
}

QSizeF MainWindow::parseSizeF(QString str)
{
    str = str.toLower();
    if (str.contains('x')) {
        QStringList list = str.split('x');
        QSizeF result(list.at(0).toFloat(), list.at(1).toFloat());
        return result;
    } else {
        return QSizeF();
    }
}

QSize MainWindow::parseSize(QString str)
{
    str = str.toLower();
    if (str.contains('x')) {
        QStringList list = str.split('x');
        QSize result(list.at(0).toInt(), list.at(1).toInt());
        return result;
    } else {
        return QSize();
    }
}

void MainWindow::on_pbUpdate_clicked()
{
    if (!gpu_mem)
        resize();
    render();
    update();
}

void MainWindow::resize()
{
    displayRes = parseSize(this->ui->dispRes->text());
    displayDim = parseSizeF(this->ui->dispDim->text());
    monitorDPI = parseSizeF(this->ui->monitorDPI->text());
    this->zoomFactor = (float)this->ui->dispZoom->value() / 100.0;
    QSize oledSize((int)(displayDim.width() * monitorDPI.width() * zoomFactor), (int)(displayDim.height() * monitorDPI.height() * zoomFactor));
    this->ui->oled->setDisplayResolution(displayRes.width(), displayRes.height());
    this->ui->oled->setMinimumSize(oledSize);
    this->ui->oled->setMaximumSize(oledSize);
    if (gpu_mem)
        free(gpu_mem);
    gpu_mem_size = displayRes.width() * displayRes.height() / 8;
    gpu_mem = (uint8_t*)malloc(gpu_mem_size);
    gh = Graphics_init(&graphics_obj, gpu_mem, gpu_mem_size, displayRes.width(), displayRes.height(), 1);
    Graphics_setRenderOffset(gh, 0);
}

void MainWindow::on_monDim_textChanged(const QString &arg1)
{
    QSizeF dim = parseSizeF(arg1);
    QSizeF res = parseSizeF(this->ui->monRes->text());
    if (dim.isEmpty() || res.isEmpty())
        return;
    QSizeF dpi(res.width() / dim.width(), res.height() / dim.height());
    this->ui->monitorDPI->setText(QString::number(dpi.width()) + "x" + QString::number(dpi.height()));
}

void MainWindow::on_monRes_textChanged(const QString &arg1)
{
    QSizeF dim = parseSizeF(this->ui->monDim->text());
    QSizeF res = parseSizeF(arg1);
    if (dim.isEmpty() || res.isEmpty())
        return;
    QSizeF dpi(res.width() / dim.width(), res.height() / dim.height());
    this->ui->monitorDPI->setText(QString::number(dpi.width()) + "x" + QString::number(dpi.height()));
}
