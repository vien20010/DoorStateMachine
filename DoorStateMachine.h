/*
 * DoorStateMachine.h
 *
 *  Created on: Jun 9, 2020
 *      Author: Lam Vien
 */

#ifndef DOORSTATEMACHINE_H_
#define DOORSTATEMACHINE_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "switches.h"
#include "led.h"
#include "uartstdio.h"
#include "debug.h"


void motionStateMachineUpdate(void);
void doorStateMachineUpdate(void);
void ledStateMachineUpdate(void);
void SystickIntHandler(void);
#endif /* DOORSTATEMACHINE_H_ */
