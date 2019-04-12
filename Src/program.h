/*
 * program.h
 *
 *  Created on: 11. apr 2019
 *      Author: JRE
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "main.h"

#define Public
#define Private static

extern void mainLoop(void);
extern void program_init(void);
extern void timer_callback_10ms(void);


#endif /* PROGRAM_H_ */
