/*
 * dio_cfg.h
 *
 *  Created on: Nov 10, 2012
 *      Author: armin
 */

#ifndef DIO_CFG_H_
#define DIO_CFG_H_

/* Hardware stuff */
#define BCM2708_PERI_BASE        (0x20000000U)
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000U)   /* GPIO controller */

/* GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y) */
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)    // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10)   // clears bits which are 1 ignores bits which are 0

#endif /* DIO_CFG_H_ */
