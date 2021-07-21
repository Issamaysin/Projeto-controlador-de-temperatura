/* ***************************************************************** */
/* File name:        timer.c                                         */
/* File description: Implements methods for a timer to trigger the   */
/*                   PID control on/off                              */
/* Author name:      Grupo 18 - Renato Pepe                          */
/*                              Joao Victor Matoso                   */
/* Creation date:    18jun2021                                       */
/* Revision date:    18jun2021                                       */
/* ***************************************************************** */

#include "timer.h"
#include "pid.h"

timer_t timer;

/* **************************************************************** */
/* Method name:        timer_init                                   */
/* Method description: Initialize timer to trigger the PID on/off   */
/* Input params:       uiPeriodMs: period of the interruption in ms */
/* Output params:      n/a                                          */
/* **************************************************************** */
void timer_init(unsigned int uiPeriodMs) {
    timer.uiPeriodMs = uiPeriodMs;
    timer.uiTriggerTimeMs = 0;
    timer.ucEnabled = 0;
    timer.ucTurnOnOff = 0;
}

/* **************************************************************** */
/* Method name:        timer_start                                  */
/* Method description: Start the timer                              */
/* Input params:       uiTriggerTimeS: time in seconds              */
/*                     ucTurnOnOff: 0 to turn PID off on trigger,   */
/*                                  1 to turn PID on on trigger     */
/* Output params:      n/a                                          */
/* **************************************************************** */
void timer_start(unsigned int uiTriggerTimeS, unsigned char ucTurnOnOff) {
    timer.uiTriggerTimeMs = uiTriggerTimeS * 1000;
    timer.ucTurnOnOff = ucTurnOnOff;
    timer.ucEnabled = 1;
}

/* **************************************************************** */
/* Method name:        timer_getTimeLeft                            */
/* Method description: Return the time left in the timer if enabled */
/* Input params:       n/a                                          */
/* Output params:      Time left in milisseconds                    */
/* **************************************************************** */
unsigned int timer_getTimeLeft() {
    if(timer.ucEnabled)
        return timer.uiTriggerTimeMs;
    else
        return 0;
}

/* **************************************************************** */
/* Method name:        timer_isOn                                   */
/* Method description: Return the timer current status              */
/* Input params:       n/a                                          */
/* Output params:      1 if timer is on, 0 if it is off             */
/* **************************************************************** */
unsigned char timer_isOn() {
    return timer.ucEnabled;
}

/* **************************************************************** */
/* Method name:        timer_abort                                  */
/* Method description: Turn the timer off without triggering it     */
/* Input params:       n/a                                          */
/* Output params:      n/a                                          */
/* **************************************************************** */
void timer_abort() {
    timer.ucEnabled = 0;
}

/* **************************************************************** */
/* Method name:        timer_tick                                   */
/* Method description: To be called in the interruption with period */
/*                     specified at initialization.                 */
/* Input params:       n/a                                          */
/* Output params:      n/a                                          */
/* **************************************************************** */
void timer_tick() {
    /* if timer is enabled, update current time left */
    if(timer.ucEnabled) {
        timer.uiTriggerTimeMs -= timer.uiPeriodMs;
        
        /* trigger action if timer is over */
        if(0 >= timer.uiTriggerTimeMs) {
                /* turn PID on or off */
                /* check if PID is already on before turn it on again. Avoid reseting pid integral sum */
                if(!timer.ucTurnOnOff || !pid_isOn()){
                    pid_turnOnOff(timer.ucTurnOnOff);
                }

                /* reset timer */
                timer.ucEnabled = 0;
        }
    }
}