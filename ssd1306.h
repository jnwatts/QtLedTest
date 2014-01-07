#ifndef SSD1306_H
#define SSD1306_H

#include <QMainWindow>
#include <qledmatrix.h>
#include <QRgb>
#include <QVector>
#include <QMap>
#include <stdint.h>
#include <stdbool.h>

class SSD1306_Worker;

namespace Ui {
class SSD1306;
}

class SSD1306 : public QWidget
{
    Q_OBJECT
    friend class SSD1306_Worker;

public:
    explicit SSD1306(QWidget *parent = 0);
    ~SSD1306();
    
    typedef enum {
        CMD_SET_ENTIRE_DISPLAY_ON = 0xA4, // Arg is X[0], mask with 0xFE
        CMD_SET_NORMAL_INVERSE = 0xA6, // Arg is X[0], mask with 0xFE
        CMD_SET_DISPLAY_ON_OFF = 0xAE, // Arg is X[0], mask with 0xFE
        CMD_SET_LOW_COL_START = 0x00, // Arg is X[0:3], mask with 0xF0
        CMD_SET_HIGH_COL_START = 0x10, // Arg is X[0:3], mask with 0xF0
        CMD_SET_MEM_ADDR_MODE = 0x20, // 1 argument, A[0:1]
        CMD_SET_COL_ADDR = 0x21, // 2 arguments, A[0:6], B[0:6]
        CMD_SET_PAGE_ADDR = 0x22, // 2 arguments, A[0:6], B[0:6]
        CMD_SET_PAGE_START_ADDR = 0xB0, // Arg is X[0:2], mask with 0xF8
        CMD_SET_NOP = 0xE3
    } Commands; 

    typedef enum {
        REGVAL_MEM_ADDR_MODE_PAGE = 2,
        REGVAL_MEM_ADDR_MODE_HORIZ = 0,
        REGVAL_MEM_ADDR_MDOE_VERT = 1
    } RegisterValues;
    
    void setPixelOnColor(QRgb color);
    void setPixelOffColor(QRgb color);
    void setDisplayResolution(int columns, int rows);
    void setRealistic(bool async);

    void setRSTn(bool RSTn);
    void setCSn(bool CSn);
    void putByte(bool D_Cn, uint8_t D0_7);
    
    void setPixel(int x, int y, int value);
    
    int numColumns();
    int numPages();
    int maxOffset();

signals:
    void FR(bool active);
    void submitByte(bool D_Cn, uint8_t D0_7);

private slots:
    void _update_display(int offset);

private:
    void _reset(void);
    void _setEnabled(bool value);
    void _update(void);
    void _processByte(bool D_Cn, uint8_t D0_7);
    void _processDataByte(uint8_t d);
    void _processCommandByte(uint8_t d);
    void _resetCommandState(void);
    void _emit_FR(bool active);
    float _framePeriod(void);
    float _displayPeriod(void);
    int _getFosc(void);
    int _getOffset(int page, int col);
    bool _increment(int *page, int *col, int mode);
    
    typedef enum {
        CS_IDLE,
        CS_ONE_ARG,
        CS_TWO_ARG
    } CommandState;
    
    typedef enum {
        REG_CONTRAST_CONTROL,
        REG_ENTIRE_DISPLAY_ON,
        REG_NORMAL_INVERSE,
        REG_DISPLAY_ON_OFF,
        REG_MEM_ADDR_MODE,
        REG_COL_ADDR_START,
        REG_COL_ADDR_STOP,
        REG_PAGE_ADDR_START,
        REG_PAGE_ADDR_STOP,
        REG_PAGE_START_ADDR,
        REG_MULTIPLEX_RATIO,
        REG_DISPLAY_CLOCK_DIVIDE_RATIO
    } Registers;
    
    Ui::SSD1306 *ui;
    QRgb onColor;
    QRgb offColor;
    
    bool _realistic;
    bool _CSn;
    bool _RSTn;
    bool _enabled;
    CommandState _command_state;
    uint8_t _cur_cmd;
    uint8_t _cur_args[2];
    int mem_ptr_page;
    int mem_ptr_col;
    int disp_ptr_page;
    int disp_ptr_col;
    QMap<uint8_t, int> reg;
    QVector<uint8_t> ram;

    SSD1306_Worker *_work;
};

#endif // SSD1306_H
