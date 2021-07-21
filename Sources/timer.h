/* ***************************************************************** */
/* File name:        timer.c                                         */
/* File description: Implements methods for a timer trigger          */
/* Author name:      Grupo 18 - Renato Pepe                          */
/*                              Joao Victor Matoso                   */
/* Creation date:    18jun2021                                       */
/* Revision date:    18jun2021                                       */
/* ***************************************************************** */

#ifndef _SOURCE_TIMER_H_
#define _SOURCE_TIMER_H_

typedef struct {
    unsigned int uiTriggerTimeMs;
	unsigned int uiPeriodMs;
    unsigned char ucEnabled;
    unsigned char ucTurnOnOff;
} timer_t;

/* **************************************************************** */
/* Method name:        timer_init                                   */
/* Method description: Initialize timer to trigger the PID on/off   */
/* Input params:       uiPeriodMs: period of the interruption in ms */
/* Output params:      n/a                                          */
/* **************************************************************** */
void timer_init(unsigned int uiPeriodMs);

/* **************************************************************** */
/* Method name:        timer_start                                  */
/* Method description: Start the timer                              */
/* Input params:       uiTriggerTimeS: time in seconds              */
/*                     ucTurnOnOff: 0 to turn PID off on trigger,   */
/*                                  1 to turn PID on on trigger     */
/* Output params:      n/a                                          */
void timer_start(unsigned int uiTriggerTimeS, unsigned char ucTurnOnOff);

/* **************************************************************** */
/* Method name:        timer_getTimeLeft                            */
/* Method description: Return the time left in the timer if enabled */
/* Input params:       n/a                                          */
/* Output params:      Time left in milisseconds                    */
/* **************************************************************** */
unsigned int timer_getTimeLeft();

/* **************************************************************** */
/* Method name:        timer_isOn                                   */
/* Method description: Return the timer current status              */
/* Input params:       n/a                                          */
/* Output params:      1 if timer is on, 0 if it is off             */
/* **************************************************************** */
unsigned char timer_isOn();

/* **************************************************************** */
/* Method name:        timer_abort                                  */
/* Method description: Turn the timer off without triggering it     */
/* Input params:       n/a                                          */
/* Output params:      n/a                                          */
/* **************************************************************** */
void timer_abort();

/* **************************************************************** */
/* Method name:        timer_tick                                   */
/* Method description: To be called in the interruption with period */
/*                     specified at initialization.                 */
/* Input params:       n/a                                          */
/* Output params:      n/a                                          */
/* **************************************************************** */
void timer_tick();


#endif
