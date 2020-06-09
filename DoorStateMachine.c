/*
 * DoorStateMachine.c
 *
 *  Created on: Jun 9, 2020
 *      Author: Lam Vien
 */
#include "DoorStateMachine.h"

typedef enum {S_NOMOTION,S_NOMOTION_WAIT,S_MOTION,S_MOTION_WAIT} motionState_t;
typedef enum {S_CLOSE,S_OPEN,S_OPENWAIT} doorState_t;
typedef enum {S_LEDOFF,S_LEDON} ledState_t;
typedef enum {D_MOTION,D_NOMOTION} motionDetector_t;

static motionDetector_t mnt;
static motionState_t motionState;
static unsigned int motionTimerCount;
static doorState_t doorState;
static unsigned int doorTimerCount;
static ledState_t ledState;
static unsigned int ledTimerCount;

//Motion Detect Function
void motionStateMachineUpdate(void)
{
    switch (motionState)
    {
        case S_NOMOTION:
            if (switchState(1)==PRESSED)
            {
                motionState=S_NOMOTION_WAIT;
                motionTimerCount=50; //set timer systick 50ms
                DBG("state changed from S_NOMOTION to S_NOMOTION_WAIT");
            }
            break;
        case S_NOMOTION_WAIT:
            if (switchState(1)==RELEASED)
            {
                motionState=S_NOMOTION;
                DBG("state changed from S_NOMOTION_WAIT to NOMOTION");
            }
            else if (motionTimerCount==0)
            {
                motionState=S_MOTION;
                DBG("state changed from S_NOMOTION_WAIT to S_MOTION");
            }
            break;
        case S_MOTION:
            if (switchState(1)==PRESSED)
            {
                motionState=S_MOTION_WAIT;
                motionTimerCount=50;
                DBG("state changed from S_MOTION to S_MOTION_WAIT");
            }
            break;
        case S_MOTION_WAIT:
            if (switchState(1)==RELEASED)
            {
                motionState=S_MOTION;
                DBG("state changed from S_MOTION_WAIT to S_MOTION");
            }
            else if(motionTimerCount==0)
            {
                motionState=S_NOMOTION;
                DBG("state changed from S_MOTION_WAIT to S_NOMOTION");
            }
            break;
    }
    switch (motionState)
    {
        case S_NOMOTION:
        case S_NOMOTION_WAIT:
            mnt=D_NOMOTION;
            break;
        case S_MOTION:
        case S_MOTION_WAIT:
            mnt=D_MOTION;
            break;
    }
}

//Function Control Open and Close Door

void doorStateMachineUpdate(void)
{
    switch (doorState)
    {
        case S_CLOSE:
            if (mnt==D_MOTION)
            {
                doorState=S_OPEN;
            }
            break;
        case S_OPEN:
            if (mnt==D_NOMOTION)
            {
                doorState=S_OPENWAIT;
                doorTimerCount=10000;//Set timer Systick 10s=1ms*10000
            }
        case S_OPENWAIT:
            if (mnt==D_MOTION)
            {
                doorState=S_OPEN;
            }
            else if (doorTimerCount==0)
            {
                doorState=S_CLOSE;
            }
    }
    switch (doorState)
    {
        case S_OPEN:
        case S_OPENWAIT:
            ledControl(LEDGREEN,ON);
            break;
        case S_CLOSE:
            ledControl(LEDGREEN,OFF);
            break;
    }
}

//Function Control Led Red announce Motion

void ledStateMachineUpdate(void)
{
    switch (ledState)
    {
        case S_LEDOFF:
            if ((mnt==D_MOTION)&&(ledTimerCount==0))
            {
                ledState=S_LEDON;
                ledTimerCount=500;
            }
            break;
        case S_LEDON:
            if (ledTimerCount==0)
            {
                ledState=S_LEDOFF;
                ledTimerCount=500;
            }
            break;
    }
    switch (ledState)
    {
        case S_LEDOFF:
            ledControl(LEDRED,OFF);
            break;
        case S_LEDON:
            ledControl(LEDRED, ON);
            break;
    }
}
void SystickIntHandler()
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
