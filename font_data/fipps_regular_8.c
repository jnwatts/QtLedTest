#include "fipps_regular_8.h"

static CharInfo _fipps_regular_8_char_info[] = {
	{4, {0, 14}, {0, 11, 0, 0}}, // ' '
	{4, {0, 4}, {0, 1, 4, 10}}, // '!'
	{6, {0, 4}, {4, 1, 6, 5}}, // '"'
	{8, {0, 6}, {10, 3, 8, 8}}, // '#'
	{8, {0, 3}, {18, 0, 8, 12}}, // '$'
	{8, {0, 14}, {26, 11, 0, 0}}, // '%'
	{8, {0, 4}, {26, 1, 8, 10}}, // '&'
	{4, {0, 4}, {34, 1, 4, 5}}, // '''
	{5, {0, 4}, {38, 1, 5, 10}}, // '('
	{5, {0, 4}, {43, 1, 5, 10}}, // ')'
	{8, {0, 6}, {48, 3, 8, 8}}, // '*'
	{6, {0, 6}, {56, 3, 6, 6}}, // '+'
	{4, {-1, 10}, {62, 7, 5, 6}}, // ','
	{6, {0, 7}, {67, 4, 6, 4}}, // '-'
	{4, {0, 10}, {73, 7, 4, 4}}, // '.'
	{7, {0, 3}, {77, 0, 7, 11}}, // '/'
	{8, {0, 4}, {84, 1, 8, 10}}, // '0'
	{5, {0, 4}, {92, 1, 5, 10}}, // '1'
	{8, {0, 4}, {0, 13, 8, 10}}, // '2'
	{8, {0, 4}, {8, 13, 8, 10}}, // '3'
	{8, {0, 4}, {16, 13, 8, 10}}, // '4'
	{8, {0, 4}, {24, 13, 8, 10}}, // '5'
	{8, {0, 4}, {32, 13, 8, 10}}, // '6'
	{7, {-1, 4}, {40, 13, 8, 10}}, // '7'
	{8, {0, 4}, {48, 13, 8, 10}}, // '8'
	{8, {0, 4}, {56, 13, 8, 10}}, // '9'
	{4, {0, 7}, {64, 16, 4, 6}}, // ':'
	{4, {-1, 8}, {68, 17, 5, 8}}, // ';'
	{6, {0, 6}, {73, 15, 6, 8}}, // '<'
	{6, {0, 6}, {79, 15, 6, 6}}, // '='
	{6, {0, 6}, {85, 15, 6, 8}}, // '>'
	{9, {0, 4}, {0, 25, 9, 10}}, // '?'
	{10, {0, 5}, {9, 26, 10, 10}}, // '@'
	{8, {0, 4}, {19, 25, 8, 10}}, // 'A'
	{8, {0, 4}, {27, 25, 8, 10}}, // 'B'
	{8, {0, 4}, {35, 25, 8, 10}}, // 'C'
	{8, {0, 4}, {43, 25, 8, 10}}, // 'D'
	{7, {0, 4}, {51, 25, 7, 10}}, // 'E'
	{7, {0, 4}, {58, 25, 7, 10}}, // 'F'
	{8, {0, 4}, {65, 25, 8, 10}}, // 'G'
	{8, {0, 4}, {73, 25, 8, 10}}, // 'H'
	{4, {0, 4}, {81, 25, 4, 10}}, // 'I'
	{8, {0, 4}, {85, 25, 8, 10}}, // 'J'
	{8, {0, 4}, {0, 36, 8, 10}}, // 'K'
	{7, {0, 4}, {8, 36, 7, 10}}, // 'L'
	{10, {0, 4}, {15, 36, 10, 10}}, // 'M'
	{8, {0, 4}, {25, 36, 8, 10}}, // 'N'
	{8, {0, 4}, {33, 36, 8, 10}}, // 'O'
	{8, {0, 4}, {41, 36, 8, 10}}, // 'P'
	{8, {0, 4}, {49, 36, 8, 11}}, // 'Q'
	{8, {0, 4}, {57, 36, 8, 10}}, // 'R'
	{8, {0, 4}, {65, 36, 8, 10}}, // 'S'
	{8, {0, 4}, {73, 36, 8, 10}}, // 'T'
	{8, {0, 4}, {81, 36, 8, 10}}, // 'U'
	{9, {0, 4}, {89, 36, 9, 10}}, // 'V'
	{10, {0, 4}, {0, 48, 10, 10}}, // 'W'
	{9, {0, 4}, {10, 48, 9, 10}}, // 'X'
	{10, {0, 4}, {19, 48, 10, 10}}, // 'Y'
	{8, {0, 4}, {29, 48, 8, 10}}, // 'Z'
	{5, {0, 4}, {37, 48, 5, 10}}, // '['
	{7, {0, 3}, {42, 47, 7, 11}}, // '\'
	{5, {0, 4}, {49, 48, 5, 10}}, // ']'
	{6, {0, 4}, {54, 48, 6, 5}}, // '^'
	{7, {0, 10}, {60, 54, 7, 4}}, // '_'
	{5, {0, 4}, {67, 48, 5, 5}}, // '`'
	{8, {0, 6}, {72, 50, 8, 8}}, // 'a'
	{8, {0, 4}, {80, 48, 8, 10}}, // 'b'
	{7, {0, 6}, {88, 50, 7, 8}}, // 'c'
	{8, {0, 4}, {0, 58, 8, 10}}, // 'd'
	{8, {0, 6}, {8, 60, 8, 8}}, // 'e'
	{7, {0, 4}, {16, 58, 7, 10}}, // 'f'
	{8, {0, 6}, {23, 60, 8, 11}}, // 'g'
	{8, {0, 4}, {31, 58, 8, 10}}, // 'h'
	{4, {0, 4}, {39, 58, 4, 10}}, // 'i'
	{4, {-1, 4}, {43, 58, 5, 13}}, // 'j'
	{8, {0, 4}, {48, 58, 8, 10}}, // 'k'
	{4, {0, 4}, {56, 58, 4, 10}}, // 'l'
	{10, {0, 6}, {60, 60, 10, 8}}, // 'm'
	{8, {0, 6}, {70, 60, 8, 8}}, // 'n'
	{8, {0, 6}, {78, 60, 8, 8}}, // 'o'
	{8, {0, 6}, {86, 60, 8, 11}}, // 'p'
	{8, {0, 6}, {0, 74, 8, 11}}, // 'q'
	{6, {0, 6}, {8, 74, 6, 8}}, // 'r'
	{8, {0, 6}, {14, 74, 8, 8}}, // 's'
	{6, {0, 4}, {22, 72, 6, 10}}, // 't'
	{8, {0, 6}, {28, 74, 8, 8}}, // 'u'
	{8, {0, 6}, {36, 74, 8, 8}}, // 'v'
	{10, {0, 6}, {44, 74, 10, 8}}, // 'w'
	{8, {0, 6}, {54, 74, 8, 8}}, // 'x'
	{8, {0, 6}, {62, 74, 8, 11}}, // 'y'
	{8, {0, 6}, {70, 74, 8, 8}}, // 'z'
	{6, {0, 4}, {78, 72, 6, 10}}, // '{'
	{4, {0, 3}, {84, 71, 4, 11}}, // '|'
	{6, {0, 4}, {88, 72, 6, 10}}, // '}'
};

static uint8_t _fipps_regular_8_char_data[] = {
	0xfc,0x82,0xfe,0xfc,0x1c,0x32,0x3e,0x32,0x3e,0x3c,0xe0,0x50,0x08,0x58,0x08,0x58,0xf0,0xe0,0x78,0xcc,0xba,0x01,0xfb,0x3a,0xfe,0xbc,0xf8,0x24,0xda,0xda,0x0e,0xdc,0xf0,0x60,0x1c,0x32,0x3e,0x3c,0xf8,0x0c,0xfa,0xfe,0x1c,0x0c,0xfa,0x06,0xfc,0xf8,0xe0,0x50,0xb0,0x08,0xb8,0x50,0xf0,0xe0,0x60,0xd0,0x88,0xd8,0xf0,0x60,0x00,0x00,0x80,0x80,0x00,0x60,0xd0,0xd0,0xd0,0xf0,0xe0,0x00,0x80,0x80,0x00,0x80,0x40,0xb8,0xce,0xfb,0x7f,0x1e,0xf8,0x0c,0xfa,0xfa,0xfa,0x0e,0xfc,0xf8,0x18,0xfc,0x02,0xfe,0xfc,0x00,
	0xc3,0xa6,0xa7,0xa7,0xa0,0x60,0xc0,0x80,0xc0,0xa0,0xa1,0xa3,0xa6,0x67,0xc6,0x87,0xc3,0x21,0xe3,0xc6,0xc6,0x2c,0xee,0xc7,0xe7,0x23,0xa1,0xa3,0xa6,0xa6,0xe7,0xc6,0x87,0x47,0xa0,0xa0,0xa0,0xe0,0xc1,0x03,0xc6,0xa7,0xa7,0xa3,0xa6,0x27,0xe3,0xc1,0x81,0xc3,0xa3,0xa6,0xa7,0xe7,0xc3,0x81,0x80,0xc0,0xa1,0xa1,0xa0,0xe0,0xcc,0x9b,0x1c,0x0f,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x06,0x07,0x87,0x83,0x06,0x07,0x87,0x80,0x80,0x80,0x01,0x03,0x86,0x86,0x06,0x07,0x07,0x03,0x00,0x03,0x06,0x07,0x07,0x00,
	0x38,0x64,0x6b,0x6b,0x6d,0x6e,0x7b,0x71,0x30,0x69,0x6f,0x6d,0x6d,0x72,0x3f,0x1d,0x07,0x0c,0x0d,0x0d,0x3d,0x60,0x7f,0x7f,0x37,0x6c,0x6d,0x6d,0x6d,0x73,0x3e,0x1c,0x1f,0x30,0x6d,0x6d,0x6d,0x72,0x3e,0x1c,0x00,0x38,0x66,0x79,0x7e,0x0f,0x03,0x01,0x1f,0x32,0x6d,0x6d,0x6d,0x72,0x3f,0x1d,0x03,0x36,0x6d,0x6d,0x6d,0x70,0x3f,0x1f,0x1e,0x35,0x3f,0x3e,0xc0,0xbc,0xca,0xfe,0x7c,0x0c,0x1a,0x35,0x6e,0x7f,0x73,0x0f,0x1a,0x1a,0x1a,0x1f,0x1f,0x33,0x6e,0x75,0x3b,0x1e,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x18,0x3c,0x3a,0xfa,0xba,0xda,0xee,0x7c,0x38,0xe0,0x10,0xe8,0xf4,0xb4,0x54,0x54,0x0c,0xf8,0xf0,0xf8,0x0c,0xfa,0xfa,0xfa,0x0e,0xfc,0xf8,0xfc,0x02,0xda,0xda,0xda,0x2e,0xfc,0xf8,0xf8,0x0c,0xfa,0xfa,0xfa,0xba,0xbe,0x3c,0xfc,0x02,0xfa,0xfa,0xfa,0x0e,0xfc,0xf8,0xfc,0x02,0xda,0xda,0xda,0xfe,0x6c,0xfc,0x02,0xda,0xda,0xda,0xfe,0xec,0xf8,0x0c,0xfa,0xfa,0xfb,0x3b,0xfe,0xfc,0xfc,0x02,0xde,0xdc,0xdc,0x02,0xfe,0xfc,0xfc,0x02,0xfe,0xfc,0xc0,0x20,0xe0,0xc0,0xfc,0x02,0xfe,0xfc,0x00,0x00,0x00,0x00,0x00,
	0xe0,0x10,0xf0,0xe3,0xe6,0x17,0xf7,0xe0,0xe0,0x11,0xf3,0xe6,0x0d,0x0d,0x0d,0xed,0x1d,0xbf,0x6f,0xc3,0x46,0xa7,0x17,0xf3,0xe6,0xe7,0x17,0xb3,0x66,0xe6,0x16,0xf6,0xe7,0xc7,0x63,0xd1,0xd3,0xd6,0x76,0xe6,0xc6,0xe7,0x17,0xd3,0xd6,0xd6,0x76,0xe6,0xc7,0xc7,0x63,0xd3,0xd6,0xd6,0x76,0xe6,0xc7,0xe7,0x13,0xd6,0xd7,0xd7,0x30,0xe0,0xc0,0xc1,0x63,0xd6,0xd6,0xd6,0xd7,0xf7,0xe3,0x63,0xd6,0xd7,0x17,0xd3,0xd6,0xf7,0xe7,0xe3,0x16,0xf7,0xe7,0xe1,0x13,0xf6,0xe6,0xe6,0x17,0xf7,0xe3,0x80,0xe0,0x10,0xf0,0xe0,
	0x1f,0x30,0x3e,0x3e,0x1e,0x31,0x3f,0x3f,0x1f,0x30,0x37,0x37,0x34,0x3c,0x38,0x1f,0x30,0x3f,0x3f,0x06,0x07,0x1f,0x30,0x3f,0x3f,0x1f,0x30,0x3f,0x3f,0x1e,0x30,0x3f,0x3f,0x0f,0x18,0x37,0x37,0x37,0x38,0x3f,0x1f,0x1f,0x30,0xbe,0xbe,0x06,0x07,0x03,0x01,0x0f,0x18,0x37,0x37,0x37,0x68,0x7f,0x77,0x1f,0x30,0x3e,0x3e,0x1e,0x31,0x3f,0x3e,0x19,0x37,0x36,0x36,0x36,0x39,0x3f,0x1e,0x00,0x00,0x1f,0x30,0x3f,0x3f,0x00,0x00,0x0f,0x18,0x37,0x37,0x37,0x38,0x3f,0x1f,0x01,0x0f,0x18,0x37,0x37,0x38,0x1f,0x0f,0x01,
	0xfe,0x81,0x7f,0xbe,0xd0,0xb0,0x7e,0x81,0xff,0xfe,0xce,0x39,0xd7,0xee,0xec,0xd6,0x39,0xff,0xce,0x0e,0x19,0x37,0xee,0x0c,0xe8,0xf6,0x39,0x1f,0x0e,0xc6,0x25,0x5d,0x6d,0x75,0x79,0xdf,0x8e,0xff,0x01,0x7d,0xff,0x86,0x07,0x1d,0x73,0xcf,0x3c,0xf0,0xc0,0x86,0x7d,0x01,0xff,0xfe,0x0c,0x1e,0x1d,0x1f,0x1e,0x1c,0x80,0x40,0x40,0x40,0x40,0xc0,0x80,0x06,0x0d,0x1b,0x1e,0x1c,0xc0,0xa8,0x54,0x54,0x54,0x0c,0xfc,0xf8,0xfe,0x01,0x77,0x76,0x76,0x8c,0xf8,0xf0,0xf0,0x88,0x74,0x74,0x74,0xdc,0x98,0x00,0x00,0x00,
	0xc0,0x21,0xd3,0xd3,0xdb,0x05,0xff,0xfb,0xc3,0x21,0x51,0x53,0x53,0x31,0xe0,0xc1,0x63,0xd3,0x0b,0xd4,0xd4,0xfc,0xf9,0xc3,0x23,0xd3,0xd0,0xd0,0x10,0xf1,0xe3,0xfb,0x07,0xdf,0xdb,0xd3,0x33,0xe1,0xc3,0xfb,0x17,0xff,0xf8,0x00,0xf8,0x15,0xff,0xfb,0xfb,0x05,0xbf,0xbb,0x53,0xeb,0xf8,0x30,0xf8,0x04,0xfc,0xf8,0xe1,0x13,0xd3,0xd3,0x33,0xd3,0xd3,0x30,0xe0,0xc0,0xe0,0x10,0xd0,0xd1,0xd3,0x33,0xe3,0xc3,0xc3,0x23,0xd1,0xd3,0xd3,0x33,0xe3,0xc3,0xe1,0x10,0xd0,0xd1,0xd3,0x33,0xe3,0xc3,0x03,0x00,0x00,0x00,
	0x03,0x06,0x0d,0x0d,0x0d,0x0c,0x0f,0x0f,0x03,0x06,0x0d,0x0d,0x0d,0x0d,0x0f,0x0f,0x00,0x07,0x0c,0x0f,0x0f,0x00,0x00,0x3b,0x6e,0x6d,0x6d,0x6d,0x78,0x3f,0x1f,0x07,0x0c,0x0f,0x07,0x07,0x0c,0x0f,0x0f,0x07,0x0c,0x0f,0x0f,0x38,0x6f,0x78,0x3f,0x1f,0x07,0x0c,0x0f,0x07,0x07,0x0c,0x0f,0x0f,0x07,0x0c,0x0f,0x0f,0x07,0x0c,0x0f,0x07,0x0c,0x0f,0x07,0x0c,0x0f,0x0f,0x07,0x0c,0x0f,0x07,0x07,0x0c,0x0f,0x0f,0x03,0x06,0x0d,0x0d,0x0d,0x0e,0x07,0x83,0xbf,0x60,0x7d,0x7d,0x0d,0x06,0x07,0x03,0x00,0x00,0x00,0x00,
	0xf0,0x88,0x74,0x74,0x74,0x04,0xfc,0xf8,0xf0,0x08,0xf4,0xf4,0x1c,0x18,0xb0,0x68,0x54,0x54,0x54,0xb4,0xfc,0xd8,0x18,0xf6,0x81,0x77,0xfe,0x98,0xf8,0x84,0x7c,0x78,0x78,0x84,0xfc,0xf8,0x78,0xc4,0xbc,0x78,0xb8,0xc4,0xfc,0x78,0xf8,0x84,0x7c,0xb8,0xc8,0xb8,0x78,0x84,0xfc,0xf8,0x98,0x74,0xac,0xd8,0xa8,0x74,0xfc,0x98,0xf8,0x84,0x7c,0x78,0x78,0x04,0xfc,0xf8,0xd8,0x34,0x54,0x54,0x54,0x64,0xfc,0x98,0x30,0xec,0x96,0x7d,0xff,0x8e,0xff,0x01,0xff,0xff,0x86,0x7d,0x93,0xee,0xfc,0x30,0x00,0x00,0x00,0x00,
	0x80,0xc1,0xa3,0x63,0xaf,0xf8,0xdf,0x1f,0x01,0x03,0x03,0x03,0x00,0x00,0x01,0x03,0x03,0x03,0x03,0x03,0x01,0x00,0x00,0x00,0x01,0x03,0x03,0x03,0x00,0x01,0x03,0x03,0x03,0x03,0x03,0x01,0x00,0x00,0x01,0x03,0x03,0x01,0x00,0x00,0x00,0x01,0x03,0x03,0x01,0x01,0x03,0x03,0x01,0x00,0x01,0x03,0x03,0x01,0x01,0x03,0x03,0x01,0x00,0x0f,0x1b,0x1b,0x1b,0x1e,0x0f,0x07,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x01,0x03,0x03,0x03,0x01,0x03,0x03,0x03,0x01,0x03,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
	0x01,0x03,0x03,0x03,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

FontInfo font_fipps_regular_8 = {
	' ',
	'~',
	_fipps_regular_8_char_info,
	_fipps_regular_8_char_data,
	98,
	8,
	20
};
