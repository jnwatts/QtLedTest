#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "font_info.h"
#include "graphics.h"
#include "ssd1306.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void on_comboBox_currentIndexChanged(int index);
    
private:
    void render(void);
    void update(void);
    
    Ui::MainWindow *ui;
    FontInfo *font;
    GraphicsObj graphics_obj;
    GraphicsHandle gh;
    uint8_t gpu_mem[128*(32*2)/8];
    int display_offset;
    static const int COLOR_OFF;
    static const int COLOR_ON;
};

#endif // MAINWINDOW_H
