/* ********************************************************************* */
/* File name:        ledSwi.h                                            */
/* File description: McLab2 keyboard methods- initialization of elements */
/*                   and I/O methods for the LEDs/buttons                */
/*                                                                       */
/* Author name:      Grupo 18 - Renato Pepe                              */
/*                              João Victor Matoso                       */
/* Creation date:    05apr2021                                           */
/* Revision date:    07apr2021                                           */
/* ********************************************************************* */

#ifndef SOURCES_LEDSWI_H_
#define SOURCES_LEDSWI_H_

//includes:
#include "board.h"


//definitions:
/*
 * defines a keyboard variable that will store if the keyboard is set to LED, button,
 * or not configured
*/
typedef enum {NOTSET, LED, BUTTON} keyboard;


//global variables:
/*
 * stores the current configuration of the McLab2 keyboard
 */
extern keyboard kbMcLab2[4];


//methods:

/* *********************************************************************************** */
/* Method name:        initKeyboard                                                    */
/* Method description: Initialize the Mclab2 keyboard                                  */
/*                      with the given configuration                                   */
/* Input params:       kbModel:                                                        */
/*                         (keyboard[4]) The desired keyboard configuration for        */
/*                         switch/LEDs 1 to 4                                          */
/*                                                                                     */
/* Output params:      n/a                                                             */
/* *********************************************************************************** */
void initKeyboard(keyboard *kbModel);


/***************************************************************************************/
/* Method name:         readButton                                                     */
/* Method description:  Reads the data of the chosen button                            */
/* Input params:        iButtonNumber                                                  */
/*                          Which of the four buttons should be read                   */
/*                                                                                     */
/* Output params:       int button data                                                */
/*                          * 0 if the button is not pressed                           */
/*                          * 1 if the button is pressed                               */
/*                          * -1 if the keyboard slot was not set to BUTTON            */
/***************************************************************************************/
int readButton(int iButtonNumber);

/***************************************************************************************/
/* Method name:         turnLED                                                        */
/* Method description:  Turns the chosen LED on or off according to the given input    */
/* Input params:        iLED                                                           */
/*                          Specifies the LED to be turned (1~4)                       */
/*                      iOnOrOff                                                       */
/*                          * 1 turns the LED on                                       */
/*                          * 0 turns it off                                           */
/* Output params:       int read error                                                 */
/*                          * -1 if the chosen LED was not properly configured         */
/*                          *  0 if the chosen LED was out of the [1,4] scope          */
/*                          *  1 if it was possible to turn the LED on/off             */
/***************************************************************************************/
int turnLED(int iLED, int iOnOrOff);

/***************************************************************************************/
/* Method name:         setLED                                                         */
/* Method description:  Turns the chosen LED on                                        */
/* Input params:        iLED                                                           */
/*                          Specifies the LED to be set (1~4)                          */
/* Output params:       int read error                                                 */
/*                          * -1 if the chosen LED was not properly configured         */
/*                          *  0 if the chosen LED was out of the [1,4] scope          */
/*                          *  1 if it was possible to turn the LED on/off             */
/***************************************************************************************/
int setLED(int iLED);

/***************************************************************************************/
/* Method name:         clearLED                                                       */
/* Method description:  Turns the chosen LED off                                       */
/* Input params:        iLED                                                           */
/*                          Specifies the LED to be cleared (1~4)                      */
/* Output params:       int read error                                                 */
/*                          * -1 if the chosen LED was not properly configured         */
/*                          *  0 if the chosen LED was out of the [1,4] scope          */
/*                          *  1 if it was possible to turn the LED on/off             */
/***************************************************************************************/
int clearLED(int iLED);

/***************************************************************************************/
/* Method name:         toggleLED                                                      */
/* Method description:  Toggles the chosen LED, if it's off turns it on and vice-versa */
/* Input params:        iLED                                                           */
/*                          Specifies the LED to be toggled (1~4)                      */
/* Output params:       int read error                                                 */
/*                          * -1 if the chosen LED was not properly configured         */
/*                          *  0 if the chosen LED was out of the [1,4] scope          */
/*                          *  1 if it was possible to turn the LED on/off             */
/***************************************************************************************/
int toggleLED(int iLED);

#endif /* SOURCES_LEDSWI_H_ */
