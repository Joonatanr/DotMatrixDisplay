/*
 * font.c
 *
 *  Created on: 12. apr 2019
 *      Author: JRE
 */

#include "font.h"

#define FONT_BEGIN 32
#define FONT_END 90

Private const U8 priv_font_data[][5] =
{
		{ 0x00, 0x00, 0x00, 0x00, 0x00 }, /* Space*/
		{ 0x80, 0x80, 0x80, 0x00, 0x80 }, /* !  33 */
		{ 0xa0, 0xa0, 0x00, 0x00, 0x00 }, /* "  34 */
		{ 0x50, 0xf8, 0x50, 0xf8, 0x50 }, /* #  35 */
		{ 0x70, 0x80, 0x60, 0x10, 0xe0 }, /* $  36 */
		{ 0xa0, 0x20, 0x40, 0x80, 0xa0 }, /* %  37 */
		{ 0xf0, 0xf0, 0xf0, 0xf0, 0xf0 }, /* &  38 */
		{ 0x20, 0x20, 0x00, 0x00, 0x00 }, /* '  39 */
		{ 0x20, 0x40, 0x40, 0x40, 0x20 }, /* (  40 */
		{ 0x40, 0x20, 0x20, 0x20, 0x40 }, /* )  41 */
		{ 0x00, 0x50, 0x20, 0x50, 0x00 }, /* *  42 */
		{ 0x00, 0x20, 0x70, 0x20, 0x00 }, /* +  43 */
		{ 0x00, 0x00, 0x00, 0x40, 0x40 }, /* ,  44 */
		{ 0x00, 0x00, 0x60, 0x00, 0x00 }, /* -  45 */
		{ 0x00, 0x00, 0x00, 0x00, 0x40 }, /* .  46 */
		{ 0x10, 0x20, 0x20, 0x40, 0x80 }, /* /  47 */
		{ 0x60, 0x90, 0x90, 0x90, 0x60 }, /* 0  48 */
		{ 0x20, 0x60, 0x20, 0x20, 0x20 }, /* 1  49 */
		{ 0x60, 0x90, 0x20, 0x40, 0xf0 }, /* 2  50 */
		{ 0xe0, 0x10, 0x60, 0x10, 0xe0 }, /* 3  51 */
		{ 0x90, 0x90, 0x70, 0x10, 0x10 }, /* 4  52 */
		{ 0xf0, 0x80, 0xe0, 0x10, 0xe0 }, /* 5  53 */
		{ 0x60, 0x80, 0xe0, 0x90, 0x60 }, /* 6  54 */
		{ 0xf0, 0x10, 0x20, 0x40, 0x40 }, /* 7  55 */
		{ 0x60, 0x90, 0x60, 0x90, 0x60 }, /* 8  56 */
		{ 0x60, 0x90, 0x70, 0x10, 0x60 }, /* 9  57 */
		{ 0x00, 0x40, 0x00, 0x40, 0x00 }, /*  : 58 */
		{ 0x00, 0x40, 0x00, 0x40, 0x40 }, /*  ; 59 */
		{ 0x20, 0x40, 0x80, 0x40, 0x20 }, /*  < 60 */
		{ 0x00, 0x70, 0x00, 0x70, 0x00 }, /*  = 61 */
		{ 0x80, 0x40, 0x20, 0x40, 0x80 }, /*  > 62 */
		{ 0x60, 0x20, 0x40, 0x00, 0x40 }, /*  ? 63 */
		{ 0x60, 0x90, 0x30, 0xd0, 0x60 }, /*  @ 64 */
		{ 0x60, 0x90, 0xf0, 0x90, 0x90,}, /*  A 65 */
		{ 0xe0, 0x90, 0xe0, 0x90, 0xe0 }, /*  B 66 */
		{ 0x60, 0x90, 0x80, 0x90, 0x60 }, /*  C 67 */
		{ 0xe0, 0x90, 0x90, 0x90, 0xe0 }, /*  D 68 */
		{ 0xf0, 0x80, 0xe0, 0x80, 0xf0 }, /*  E 69 */
		{ 0xf0, 0x80, 0xe0, 0x80, 0x80 }, /*  F 70 */
		{ 0x70, 0x80, 0xb0, 0x90, 0x70 }, /*  G 71 */
		{ 0x90, 0x90, 0xf0, 0x90, 0x90 }, /*  H 72 */
		{ 0xe0, 0x40, 0x40, 0x40, 0xe0 }, /*  I 73 */
		{ 0x70, 0x10, 0x10, 0x90, 0x60 }, /*  J 74 */
		{ 0x90, 0xa0, 0xc0, 0xa0, 0x90 }, /*  K 75 */
		{ 0x80, 0x80, 0x80, 0x80, 0xf0 }, /*  L 76 */
		{ 0x88, 0xd8, 0xa8, 0x88, 0x88 }, /*  M 77 */
		{ 0x90, 0xd0, 0xb0, 0x90, 0x90 }, /*  N 78 */
		{ 0x60, 0x90, 0x90, 0x90, 0x60 }, /*  O 79 */
		{ 0xe0, 0x90, 0xe0, 0x80, 0x80 }, /*  P 80 */
		{ 0x60, 0x90, 0x90, 0x60, 0x30 }, /*  Q 81  */
		{ 0xe0, 0x90, 0xe0, 0x90, 0x90 }, /*  R 82  */
		{ 0x70, 0x80, 0x60, 0x10, 0xe0 }, /*  S 83  */
		{ 0xf8, 0x20, 0x20, 0x20, 0x20 }, /*  T 84  */
		{ 0x90, 0x90, 0x90, 0x90, 0x60 }, /*  U 85  */
		{ 0x90, 0x90, 0x90, 0x60, 0x60 }, /*  V 86  */
		{ 0xa8, 0xa8, 0xa8, 0xa8, 0x58 }, /*  W 87  */
		{ 0x90, 0x90, 0x60, 0x90, 0x90 }, /*  X 88  */
		{ 0x90, 0x90, 0x70, 0x10, 0xe0 }, /*  Y 89  */
		{ 0xf0, 0x10, 0x20, 0x40, 0xf0 }, /*  Z 90  */
};



Public bitmap_T * getCharBmp(char c)
{
	static bitmap_T res;
	U8 ix;


	res.xpos = 0u;
	res.ypos = 0u;

	res.x_len = 5u;
	res.y_len = 5u;


	if ((c >= FONT_BEGIN) && (c <= FONT_END))
	{
		ix = c - 32;
		res.data = priv_font_data[ix];
	}
	else
	{
		res.data = priv_font_data[0];
	}
	return &res;
}

