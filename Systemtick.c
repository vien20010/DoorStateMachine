/*
 * Systemtick.c
 *
 *  Created on: Jun 4, 2020
 *      Author: Lam Vien
 */

#include "Systemtick.h"

void Systick_Init()
{
    SysTickDisable();
    SysTickPeriodSet(SysCtlClockGet()/1000);//Interrupt after 1ms
    SysTickIntEnable();
    SysTickEnable();
}
/*void SystickIntHandler()
{
    if (motionTimerCount)
    {
        motionTimerCount--;
    }
    if (doorTimerCount)
    {
        doorTimerCount--;
    }
    if (ledTimerCount)
    {
        ledTimerCount--;
    }
}
*/
