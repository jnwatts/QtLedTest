#include "graphics.h"
#include <math.h>
#include <stdint.h>

#define toHandle(obj) ((GraphicsHandle)obj)
#define toObject(handle) ((GraphicsObj*)handle)


#include <QApplication>
void update_display(void);

static int _getPixel_1bpp(GraphicsHandle handle, void *buf, int x, int y, int stride)
{
    GraphicsObj *obj = toObject(handle);
    uint8_t *mem = (uint8_t*)buf;
    mem += (y / 8) * stride;
    mem += x;
    int shift = y % 8;
    return ((*mem) >> shift) & 0x01;
}

static void _setPixel_1bpp(GraphicsHandle handle, void *buf, int x, int y, int stride, int color)
{
    GraphicsObj *obj = toObject(handle);
    uint8_t *mem = (uint8_t*)buf;
    int page = (y / 8);
    int col = x;
    mem += page * stride;
    mem += col;
    //TODO: Check bounds
    int shift = y % 8;
    uint8_t m = *mem;
    m &= ~(1 << shift);
    m |= (color << shift) & (1 << shift);
    *mem = m;
}

GraphicsHandle Graphics_init(GraphicsObj *obj, void *gpu_mem, int gpu_size, int width, int height, int depth)
{
    obj->gpu_mem = gpu_mem;
    obj->gpu_size = gpu_size;
    obj->width = width;
    obj->height = height;
    obj->depth = depth = 1;
    obj->stride = width;
    obj->offset = 0;
    obj->fillColor = 1;
    obj->penColor = 1;
    switch (depth) {
    case 1:
        obj->getPixel = _getPixel_1bpp;
        obj->setPixel = _setPixel_1bpp;
        break;
    default:
        obj->getPixel = 0;
        obj->setPixel = 0;
        break;
    }

    return toHandle(obj);
}

void Graphics_setRenderOffset(GraphicsHandle handle, int offset)
{
    GraphicsObj *obj = toObject(handle);
    obj->offset = offset;
}

void Graphics_setFill(GraphicsHandle handle, int color)
{
    GraphicsObj *obj = toObject(handle);
    obj->fillColor = color;
}

void Graphics_setPen(GraphicsHandle handle, int color)
{
    GraphicsObj *obj = toObject(handle);
    obj->penColor = color;
}

void Graphics_fillRect(GraphicsHandle handle, int x, int y, int w, int h)
{
    GraphicsObj *obj = toObject(handle);
    uint8_t *dst = (uint8_t*)obj->gpu_mem + obj->offset;
    for (int dy = 0; dy < h; ++dy) {
        for (int dx = 0; dx < w; ++dx) {
            obj->setPixel(handle, dst, x + dx, y + dy, obj->stride, obj->fillColor);
        }
    }
}

void Graphics_drawRect(GraphicsHandle handle, int x, int y, int w, int h)
{
    w--;
    h--;
    Graphics_drawLine(handle, x, y, x + w, y);
    Graphics_drawLine(handle, x + w, y, x + w, y + h);
    Graphics_drawLine(handle, x, y + h, x + w, y + h);
    Graphics_drawLine(handle, x, y, x, y + h);
}

void Graphics_drawLine(GraphicsHandle handle, int x0, int y0, int x1, int y1)
{
    GraphicsObj *obj = toObject(handle);
    uint8_t *dst = (uint8_t*)obj->gpu_mem + obj->offset;
    int rise = (y1 - y0);
    int run = (x1 - x0);
    if (run != 0) {
        // Horizontal or sloped line
        float m = (float)rise / (float)run;
        int xf = x0 + run;
        int dx = (run > 0) ? 1 : -1;
        for (int x = x0; x != xf + dx; x += dx) {
            int y = (int)(m * (float)x) + y0;
            obj->setPixel(handle, dst, x, y, obj->stride, obj->penColor);
        }
    } else if (rise != 0) {
        // Vertical line
        int yf = y0 + rise;
        int dy = (rise > 0) ? 1 : -1;
        for (int y = y0; y != yf + dy; y += dy) {
            obj->setPixel(handle, dst, x0, y, obj->stride, obj->penColor);
        }
            
    } else {
        obj->setPixel(handle, dst, x0, y0, obj->stride, obj->penColor);
    }
}

void Graphics_drawArc(GraphicsHandle handle, int x, int y, int r, int t0, int t1)
{
    GraphicsObj *obj = toObject(handle);
    uint8_t *dst = (uint8_t*)obj->gpu_mem + obj->offset;
    int dt = (t0 < t1) ? 1 : -1;
    float fr = (float)r;
    for (int t = t0; t != t1 + dt; t += dt) {
        float rad = (float)t / 360.0 * (2.0f*3.14f);
        float fx = (float)x + fr*cos(rad);
        float fy = (float)y + fr*sin(rad);
        if (r < 4) {
            int xfrac = (int)(fx * 10) % 10;
            int yfrac = (int)(fy * 10) % 10;
            if (xfrac > 2 && xfrac < 8)
                continue;
            if (yfrac > 2 && yfrac < 8)
                continue;
        }
        int _x = round(fx);
        int _y = round(fy);
        
        obj->setPixel(handle, dst, _x, _y, obj->stride, obj->penColor);
    }
}

void Graphics_drawTab(GraphicsHandle handle, int x, int y, int w, int h, int r, bool bottom, bool flat_edge)
{
    w--;
    h--;
    h -= r;
    if (bottom) {
        y += r;
        Graphics_drawLine(handle, x + w, y, x + w, y + h);
        Graphics_drawLine(handle, x, y, x, y + h);
        if (flat_edge) {
            Graphics_drawLine(handle, x, y + h, x + w, y + h);
        }
        Graphics_drawArc(handle, x + r, y, r, -180, -90);
        Graphics_drawArc(handle, x + w - r, y, r, 0, -90);
        Graphics_drawLine(handle, x + r, y - r, x + w - r, y - r);
    } else {
        h -= r;
        Graphics_drawLine(handle, x + w, y, x + w, y + h);
        Graphics_drawLine(handle, x, y, x + w, y);
        if (flat_edge) {
            Graphics_drawLine(handle, x, y + h, x + w, y + h);
        }
    }
}

void Graphics_measureString(GraphicsHandle handle, FontInfo *font, const char *str, int *w, int *h)
{
    (void)handle;
    const char *s = str;
    char c = 0;
//    int orig_x = x;
//    int orig_y = y;
//    y -= font->height - font->size;
    *w = 0;
    *h = font->height;
    while ((c = *s++) != '\0') {
        if (c == '\n') {
//            x = orig_x;
//            y += font->size;
            *h += font->height;
        } else if (c == '\r') {
//            x = orig_x;
        } else {
            CharInfo *ci = Font_getCharInfo(font, c);
            if (ci) {
//                Graphics_drawChar(handle, font, ci, c, x, y);
//                x += ci->width;
                *w += ci->width;
            } else {
//                Graphics_drawRect(handle, x + 1, y + 1, font->size, font->size);
//                x += font->size + 2;
                *w += font->size + 2;
            }
        }
    }
}

void Graphics_drawChar(GraphicsHandle handle, FontInfo *font, CharInfo *ci, char c, int x, int y)
{
    GraphicsObj *obj = toObject(handle);
    if (!ci) {
        ci = Font_getCharInfo(font, c);
    }
    if (ci) {
        uint8_t *dst = (uint8_t*)obj->gpu_mem + obj->offset;
        int src_x = ci->rect[0];
        int src_y = ci->rect[1];
        int src_w = ci->rect[2];
        int src_h = ci->rect[3];
        int dst_x = x + ci->offset[0];
        int dst_y = y + ci->offset[1];
        // Advance is ci->width
        qDebug("drawChar: '%c' at %d,%d. WxH: %dx%d", c, x, y, src_w, src_h);
        for (int dy = 0; dy < src_h; ++dy) {
            for (int dx = 0; dx < src_w; ++dx) {
                if (obj->getPixel(handle, font->data, src_x + dx, src_y + dy, font->stride) != obj->fillColor)
                    obj->setPixel(handle, dst, dst_x + dx, dst_y + dy, obj->stride, obj->penColor);
            }
        }
    }
}

void Graphics_drawString(GraphicsHandle handle, FontInfo *font, const char *str, int x, int y)
{
    const char *s = str;
    char c = 0;
    int orig_x = x;
    int orig_y = y;
//    y -= font->height - font->size;
//    int h = font->height;
    while ((c = *s++) != '\0') {
        if (c == '\n') {
            x = orig_x;
            y += font->size;
//            *h += font->height;
        } else if (c == '\r') {
            x = orig_x;
        } else {
            CharInfo *ci = Font_getCharInfo(font, c);
            if (ci) {
                Graphics_drawChar(handle, font, ci, c, x, y);
                x += ci->width;
//                w += ci->width;
            } else {
                Graphics_drawRect(handle, x + 1, y + 1, font->size, font->size);
                x += font->size + 2;
//                w += font->size + 2;
            }
        }
    }
}
