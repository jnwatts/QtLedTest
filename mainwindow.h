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
    void on_tabFont_currentIndexChanged(int index);
    
private slots:
    void on_pbUpdate_clicked();
    void resize(void);

private:
    void render(void);
    void update(void);
    
    static QSizeF parseSizeF(QString str);
    static QSize parseSize(QString str);

    Ui::MainWindow *ui;
    QSize displayRes;
    QSizeF displayDim;
    QSizeF monitorDPI;
    float zoomFactor;
    FontInfo *font;
    GraphicsObj graphics_obj;
    GraphicsHandle gh;
    uint8_t *gpu_mem;
    int gpu_mem_size;
    int display_offset;
    static const int COLOR_OFF;
    static const int COLOR_ON;
};

#endif // MAINWINDOW_H
