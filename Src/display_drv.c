/*
 * display_drv.c
 *
 *  Created on: 11. apr 2019
 *      Author: JRE
 */
#include "display_drv.h"
#include "font.h"
#include "string.h"


const U8 test_data[]= { 0x0Au, 0xffu,
					    0xffu, 0xffu };

bitmap_T test_bmp =
{
		.xpos = 1u,
		.ypos = 1u,
		.x_len = 8u,
		.y_len = 2u,
		.data = test_data,
};

const U8 test_character[] =
{
		0x20u,
		0x50u,
		0x70u,
		0x50u
};


bitmap_T test_letter =
{
		.xpos = 1u,
		.ypos = 1u,
		.x_len = 6u,
		.y_len = 4u,
		.data = test_character
};



uint32_t video_memory[8];

Private void pixel_set(int x, int y, int val);
Private void set_latch(int state);
Private void set_enable(int state);
Private void drawBitmap(bitmap_T * bmp);
Private void drawChar(char c, int x, int y);
Private void drawString(char * str, int x, int y);

/********* Public functions  *********/
Public void disp_init(void)
{
	//TODO : This should be set elsewhere...
	set_enable(0);

#if 0
	video_memory[0] = 0xAAAAAAAAu;
	video_memory[1] = 0xFFFFFFFFu;
	video_memory[2] = 0x0F0F0F0Fu;
	video_memory[3] = 0xF0F0F0F0u;
#endif

	//pixel_set(0, 0, 1);
	//pixel_set(1, 1, 1);
	//pixel_set(8, 0, 1);
	//pixel_set(10,1, 1);

	//drawBitmap(&test_bmp);
	//drawBitmap(&test_letter);
	//drawBitmap(getCharBmp('0'));
	//drawChar('1', 0, 0);

	//drawString("1234", 0, 0);
	drawString("ENGINAATOR", 0, 1);
}

//Called with 800Hz rate -> Framerate is 100Hz.
Public void disp_scan(void)
{
	static uint8_t cycle = 0u;
	uint8_t test_pattern[5] = { 0xffu, 0xffu, 0xffu, 0xffu, 0xffu };

	set_latch(1);
	set_latch(0);

	cycle++;
	if (cycle >= 8u)
	{
		cycle = 0u;
	}

	//test_pattern[0] = 1 << cycle;
	test_pattern[0] = 0x80 >> cycle;

	test_pattern[1] = video_memory[cycle] & 0x000000ffu;
	test_pattern[2] = (video_memory[cycle] >> 8) & 0x000000ffu;
	test_pattern[3] = (video_memory[cycle] >> 16) & 0x000000ffu;
	test_pattern[4] = (video_memory[cycle] >> 24) & 0x000000ffu;

#if 0
	if (cycle & 0x01u)
	{
		test_pattern[1] = 0xAAu;
		test_pattern[2] = 0xAAu;
		test_pattern[3] = 0xAAu;
		test_pattern[4] = 0xAAu;
	}
#endif

	HAL_SPI_Transmit(&hspi1, test_pattern, 5u, ~0);
}



/************** Private functions ************/
Private void pixel_set(int x, int y, int val)
{
	if (x < 0 || x > 32  || y < 0 || y >= 8 || val < 0)
	{
		//Value out of range
		return;
	}

	video_memory[y] &= ~(1u << x);
	video_memory[y] |= (val << x);
}

Private void drawString(char * str, int x, int y)
{
	U8 ix;
	U8 len = strlen(str);
	U8 xpos = x;

	for (ix = 0u; ix < len; ix++)
	{
		drawChar(str[ix],xpos, y);
		xpos += 5u;
	}
}

Private void drawChar(char c, int x, int y)
{
	bitmap_T * bmp = getCharBmp(c);
	if (bmp != NULL)
	{
		bmp->xpos = x;
		bmp->ypos = y;

		drawBitmap(bmp);
	}
}

Private void drawBitmap(bitmap_T * bmp)
{
	U8 row;
	U8 column;
	U8 last_column;
	U8 last_row;

	U32 mask;
	const U8 * data_ptr = bmp->data;

	row = bmp->ypos;
	column = bmp->xpos;
	last_row = (bmp->ypos + bmp->y_len) - 1;
	last_column = (bmp->xpos + bmp->x_len) - 1;

	mask = 0xffffffffu;

	mask = mask << (column);
	mask = mask >> (column);

	if (last_column > 31)
	{
		last_column = 31;
	}

	mask = mask >> (31 - last_column);
	mask = mask << (31 - last_column);

	for (; row <= last_row; row++)
	{
		U32 image_data = 0u;
		U8 ix;

		for(ix = 0u; ix < bmp->x_len; ix += 8)
		{
			image_data |= (U32)(*data_ptr) << (24u - ix);
			data_ptr++;
		}

		//First clear the data
		video_memory[row] &= ~mask;
		image_data = image_data >> (column );
		image_data = image_data & mask;
		video_memory[row] |= image_data;
	}
}



Private void set_latch(int state)
{
	HAL_GPIO_WritePin(SPI_Latch_GPIO_Port, SPI_Latch_Pin, state);
}

Private void set_enable(int state)
{
	HAL_GPIO_WritePin(SPI_Enable_GPIO_Port, SPI_Enable_Pin, state);
}
