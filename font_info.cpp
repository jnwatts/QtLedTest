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
