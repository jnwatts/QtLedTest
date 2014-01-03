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

#include <QApplication>
#include "mainwindow.h"
#include "graphics.h"
#include "ssd1306.h"
#include "font_data/pf_arma_five_regular_8.h"

//GraphicsObj graphics_obj;
//GraphicsHandle gh;
//SSD1306 *oled;
//uint8_t gpu_mem[128*(32*2)/8];
//int display_offset = 0;
//const int COLOR_OFF = 0;
//const int COLOR_ON = 1;

//void update_display(void);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
//    oled = new SSD1306();
//    oled->setDisplayResolution(128,32);
//    oled->show();
//    a.processEvents();

//    oled->setCSn(false);
//    oled->putByte(false, SSD1306::CMD_SET_DISPLAY_ON_OFF | 0x01);
//    oled->putByte(false, SSD1306::CMD_SET_MEM_ADDR_MODE);
//    oled->putByte(false, SSD1306::REGVAL_MEM_ADDR_MODE_HORIZ);

//    gh = Graphics_init(&graphics_obj, &gpu_mem, sizeof(gpu_mem), 128, 32, 1);
//    Graphics_setRenderOffset(gh, 0);
//    Graphics_setFill(gh, COLOR_OFF);
//    Graphics_setPen(gh, COLOR_ON);
//    Graphics_fillRect(gh, 0, 0, 128, 32 * 2);
    
//    int tabHeight = 8;
//    Graphics_drawTab(gh, 0, 32 - tabHeight, 20, tabHeight, 2, true, false);
//    tabHeight += 2;
//    Graphics_drawTab(gh, 22, 32 - tabHeight, 42, tabHeight, 4, true, false);

//    Graphics_drawString(gh, &font_pf_arma_five_regular_8, "Hello,\nWorld!", 5, 5);
    
//    update_display();
    
    return a.exec();
}

//void update_display(void) {
//    oled->putByte(false, SSD1306::CMD_SET_PAGE_ADDR);
//    oled->putByte(false, 0);
//    oled->putByte(false, 7);
//    oled->putByte(false, SSD1306::CMD_SET_COL_ADDR);
//    oled->putByte(false, 0);
//    oled->putByte(false, 127);
//    for (int o = 0; o < SSD1306::NUM_COL * SSD1306::NUM_PAGE; ++o) {
//        oled->putByte(true, gpu_mem[display_offset + o]);
//    }
//}
