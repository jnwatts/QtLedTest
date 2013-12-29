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

void MainWindow::on_pbUpdate_clicked()
{
    if (!gpu_mem)
        resize();
    render();
    update();
}

void MainWindow::resize()
{
    QStringList list = this->ui->dispRes->text().split('x');
    displayRes = QSize(list.at(0).toInt(), list.at(1).toInt());
    list = this->ui->dispDim->text().split('x');
    displayDim = QSize(list.at(0).toFloat(), list.at(1).toFloat());
    list = this->ui->monitorDPI->text().split('x');
    monitorDPI = QSize(list.at(0).toFloat(), list.at(1).toFloat());
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
