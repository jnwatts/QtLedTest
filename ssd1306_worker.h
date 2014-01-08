#ifndef SSD1306_WORKER_H
#define SSD1306_WORKER_H

#include <QThread>
#include <QSemaphore>
#include <stdint.h>

class SSD1306;

class SSD1306_Worker : public QThread
{
    Q_OBJECT
public:
    SSD1306_Worker(QObject *parent = NULL);
    ~SSD1306_Worker(void);
    void run();
    void setEnabled(bool value);

public slots:
    void receiveByte(bool D_Cn, uint8_t D0_7);

signals:
    void update_display(int offset);

private:
    bool running;
    bool enabled;
    bool dirty;
    QSemaphore sem;
    SSD1306 *ssd1306;
};

#endif // SSD1306_WORKER_H
