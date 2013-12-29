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
    ui->setupUi(this);
    
    display_offset = 0;
    
    // Screen:
    //  1920 x 1080
    //  344mm x 194mm
    // Display:
    //  128 x 32
    //  30mm x 11.50
    
    float ppmX = 1920.0 / 344.0 * 2.0; // pp/m
    float ppmY = 1080.0 / 194.0 * 2.0; // pp/m
    
    this->ui->oled->setGeometry(this->ui->oled->x(), this->ui->oled->y(), (int)(30.0 * ppmX), (int)(11.5 * ppmY));
    this->ui->oled->setDisplayResolution(128, 32);
    this->ui->oled->setCSn(false);
    this->ui->oled->putByte(false, SSD1306::CMD_SET_DISPLAY_ON_OFF | 0x01);
    this->ui->oled->putByte(false, SSD1306::CMD_SET_MEM_ADDR_MODE);
    this->ui->oled->putByte(false, SSD1306::REGVAL_MEM_ADDR_MODE_HORIZ);
    
    gh = Graphics_init(&graphics_obj, &gpu_mem, sizeof(gpu_mem), 128, 32, 1);
    Graphics_setRenderOffset(gh, 0);
    Graphics_setFill(gh, COLOR_OFF);
    Graphics_setPen(gh, COLOR_ON);
    Graphics_fillRect(gh, 0, 0, 128, 32 * 2);
    
    FontDescription *fd = &fonts[0];
    while (fd->name) {
        this->ui->comboBox->addItem(fd->name);
        fd++;
    }
    this->ui->comboBox->setCurrentIndex(this->ui->comboBox->count()-1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    font = fonts[index].info;
    render();
    update();
}

void MainWindow::render()
{
    if (font) {
        Graphics_setFill(gh, COLOR_OFF);
        Graphics_setPen(gh, COLOR_ON);
        Graphics_fillRect(gh, 0, 0, 128, 32);
        int w, h;
        Graphics_measureString(gh, font, "ABC", &w, &h);
        Graphics_drawTab(gh, 2, 32 - h, w + 3, h, 2, true, false);
        Graphics_drawString(gh, font, "ABC", 4, 32 - h);
    }
}

void MainWindow::update()
{
    this->ui->oled->putByte(false, SSD1306::CMD_SET_PAGE_ADDR);
    this->ui->oled->putByte(false, 0);
    this->ui->oled->putByte(false, 7);
    this->ui->oled->putByte(false, SSD1306::CMD_SET_COL_ADDR);
    this->ui->oled->putByte(false, 0);
    this->ui->oled->putByte(false, 127);
    for (int o = 0; o < SSD1306::NUM_COL * SSD1306::NUM_PAGE; ++o) {
        this->ui->oled->putByte(true, gpu_mem[display_offset + o]);
    }
}
