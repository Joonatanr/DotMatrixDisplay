/*
 * display_drv.h
 *
 *  Created on: 11. apr 2019
 *      Author: JRE
 */

#ifndef DISPLAY_DRV_H_
#define DISPLAY_DRV_H_

#include "program.h"

typedef uint8_t U8;
typedef uint32_t U32;

typedef struct
{
	U8 xpos;
	U8 ypos;
	U8 x_len;
	U8 y_len;
	const U8 * data;
} bitmap_T;

extern void disp_scan(void);
extern void disp_init(void);


#endif /* DISPLAY_DRV_H_ */
