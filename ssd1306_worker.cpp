#include "ssd1306_worker.h"
#include "ssd1306.h"

SSD1306_Worker::SSD1306_Worker(QObject *parent) :
    QThread(parent),
    running(false),
    enabled(false),
    dirty(true)
{
    ssd1306 = (SSD1306*)parent;
}

SSD1306_Worker::~SSD1306_Worker(void)
{
    if (running && isRunning()) {
        running = false;
        sem.release(1);
        this->wait();
    }
}

void SSD1306_Worker::run(void) {
    if (!ssd1306)
        return;

    running = true;

    enum {
        STATE_DISABLED,
        STATE_IDLE,
        STATE_SYNC,
        STATE_RENDER
    } state = STATE_DISABLED;

    while (running) {
        unsigned long delay = 0;
        switch (state) {
        case STATE_DISABLED:
            if (enabled)
                state = STATE_IDLE;
            break;
        case STATE_IDLE:
            if (!enabled) {
                state = STATE_DISABLED;
            } else if (dirty) {
                state = STATE_SYNC;
                ssd1306->_emit_FR(true);
                delay = 1000.0 * 1000.0 * ssd1306->_framePeriod() / ssd1306->numPages();
            }
            break;
        case STATE_SYNC:
            ssd1306->_emit_FR(false);
            state = STATE_RENDER;
            // Fall through
        case STATE_RENDER:
        {
            int offset = ssd1306->_getOffset(ssd1306->disp_ptr_page, ssd1306->disp_ptr_col);
            if (ssd1306->_increment(&ssd1306->disp_ptr_page, &ssd1306->disp_ptr_col, SSD1306::REGVAL_MEM_ADDR_MODE_HORIZ)) {
                dirty = false;
                state = STATE_IDLE;
            }
            delay = 1000.0 * 1000.0 * ssd1306->_displayPeriod();
            emit update_display(offset);
        }
            break;
        default:
            state = STATE_DISABLED;
        }
        if (delay > 0) {
            usleep(delay);
        } else {
            sem.tryAcquire(1, 1000);
        }
    }
}

void SSD1306_Worker::setEnabled(bool value)
{
    enabled = value;
}

void SSD1306_Worker::receiveByte(bool D_Cn, uint8_t D0_7)
{
    if (ssd1306->_processByte(D_Cn, D0_7)) {
        sem.release(1);
        dirty = true;
    }
}
