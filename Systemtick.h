/*
 * Systemtick.h
 *
 *  Created on: Jun 4, 2020
 *      Author: Lam Vien
 */

#ifndef SYSTEMTICK_H_
#define SYSTEMTICK_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"

/*extern unsigned int motionTimerCount;
extern unsigned int doorTimerCount;
extern unsigned int ledTimerCount;*/

void Systick_Init(void);
//void SystickIntHandler(void);

#endif /* SYSTEMTICK_H_ */
