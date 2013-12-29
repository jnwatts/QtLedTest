#include "font_info.h"

bool Font_isCharValid(FontInfo *info, char c)
{
    return (c >= info->first_char && c <= info->last_char);
}

CharInfo *Font_getCharInfo(FontInfo *info, char c)
{
    if (Font_isCharValid(info, c)) {
        return &info->info[c - info->first_char];
    } else {
        return 0;
    }
}
