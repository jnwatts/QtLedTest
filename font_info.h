#ifndef FONT_INFO_H
#define FONT_INFO_H

#include <stdbool.h>
#include <stdint.h>

/* Ideal FontBuilder settings:
 *
 * Font
 *  Size: Native
 *  Smoothing: Off
 *  DPI: 72
 *  Hinting: Default
 *  
 * Layout
 *  Line engine: Line Layout
 *
 */

typedef struct {
    int width;
    int offset[2];
    int rect[4];
} CharInfo;

typedef struct {
    char first_char;
    char last_char;
    CharInfo *info;
    uint8_t *data;
    int stride;
    int size;
    int height;
} FontInfo;

typedef struct {
    const char *name;
    FontInfo *info;
} FontDescription;

bool Font_isCharValid(FontInfo *info, char c);
CharInfo *Font_getCharInfo(FontInfo *info, char c);

#endif // FONT_INFO_H
