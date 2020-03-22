/*
 * common.h
 *
 *  Created on: 2020/03/21
 *      Author: Akinori
 */

#ifndef COMMON_H_
#define COMMON_H_

typedef unsigned char bool;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;

#define true	(1)
#define false	(0)

#define STATIC_ASSERT(expr) { char static_assertion_failed[(expr) ? 1 : 0]; }

//todo:暫定
#define _delay_ms(x)

#endif /* COMMON_H_ */
