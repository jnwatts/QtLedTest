#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "font_info.h"

typedef void * GraphicsHandle;

typedef int (*getPixel_t)(GraphicsHandle handle, void *buf, int x, int y, int stride);
typedef void (*setPixel_t)(GraphicsHandle handle, void *buf, int x, int y, int stride, int color);

typedef struct GraphicsObj_s {
    void *gpu_mem;
    int gpu_size;
    int width;
    int height;
    int depth; // Not implemented
    int stride;
    int offset;
    int fillColor;
    int penColor;
    getPixel_t getPixel;
    setPixel_t setPixel;
} GraphicsObj;


GraphicsHandle Graphics_init(GraphicsObj *obj, void *gpu_mem, int gpu_size, int width, int height, int depth);
void Graphics_setRenderOffset(GraphicsHandle handle, int offset);
void Graphics_setFill(GraphicsHandle handle, int color);
void Graphics_setPen(GraphicsHandle handle, int color);
void Graphics_fillRect(GraphicsHandle handle, int x, int y, int w, int h);
void Graphics_drawRect(GraphicsHandle handle, int x, int y, int w, int h);
void Graphics_drawLine(GraphicsHandle handle, int x0, int y0, int x1, int y1);
void Graphics_drawArc(GraphicsHandle handle, int x, int y, int r, int t0, int t1);
void Graphics_drawTab(GraphicsHandle handle, int x, int y, int w, int h, int r, bool bottom, bool flat_edge);
void Graphics_measureString(GraphicsHandle handle, FontInfo *font, const char *str, int *w, int *h);
void Graphics_drawChar(GraphicsHandle handle, FontInfo *font, CharInfo *ci, char c, int x, int y);
void Graphics_drawString(GraphicsHandle handle, FontInfo *font, const char *str, int x, int y);

#endif // GRAPHICS_H
