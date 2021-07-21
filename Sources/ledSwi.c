/* ******************************************************************* */
/* File name:        ledSwi.c                                          */
/* File description: Implementation of keyboard methods to initialize, */
/*                   read buttons and set LEDs values for McLab2 kit   */
/*                                                                     */
/* Author name:      Grupo 18 - Renato Pepe                            */
/*                              João Victor Matoso                     */
/* Creation date:    05apr2021                                         */
/* Revision date:    07apr2021                                         */
/* ******************************************************************* */

// includes
#include "ledSwi.h"

// global variables:
/*
 * stores the current configuration of the McLab2 keyboard
 */
keyboard kbMcLab2[4] = {NOTSET, NOTSET, NOTSET, NOTSET};


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
void initKeyboard(keyboard *kbModel){

    /*
     * un-gate port A clock (A is the port used for the connected McLab2 keyboard)
     * SIM: System Integration Module
     * SCGC5: System Clock Gating Control Register 5
    */
    SIM_SCGC5 |= FRDM_PORTA;

    /*
     * set the pins that are going to be used as GPIO (PORTA_PCRx)
     * stores the configuration into the global keyboard kbMcLab2
     * set pins that are going to be used as LEDs as input (GPIOA_PDDR)
     * set pins that are going to be used as buttons as output (GPIOA_PDDR)
    */

    /*pin 1*/
    kbMcLab2[0] = kbModel[0];
    if(LED == kbMcLab2[0]){
		PORTA_PCR1 |= 0x100;
        GPIOA_PDDR |= LEDSWITCH_1_GPIO_PDDR;
    }
    else if(BUTTON == kbMcLab2[0]){
		PORTA_PCR1 |= 0x100;
        GPIOA_PDDR &= ~LEDSWITCH_1_GPIO_PDDR;
    }

    /*pin 2*/
    kbMcLab2[1] = kbModel[1];
    if(LED == kbMcLab2[1]){
		PORTA_PCR2 |= 0x100;
        GPIOA_PDDR |= LEDSWITCH_2_GPIO_PDDR;
    }
    else if(BUTTON == kbMcLab2[1]){
		PORTA_PCR2 |= 0x100;
        GPIOA_PDDR &= ~LEDSWITCH_2_GPIO_PDDR;
    }

    /*pin 3*/
    kbMcLab2[2] = kbModel[2];
    PORTA_PCR4 |= 0x100;
    if(LED == kbMcLab2[2]){
        GPIOA_PDDR |= LEDSWITCH_3_GPIO_PDDR;
    }
    else if(BUTTON == kbMcLab2[2]){
        GPIOA_PDDR &= ~LEDSWITCH_3_GPIO_PDDR;
    }

    /*pin 4*/
    kbMcLab2[3] = kbModel[3];
    PORTA_PCR5 |= 0x100;
    if(LED == kbMcLab2[3]){
        GPIOA_PDDR |= LEDSWITCH_4_GPIO_PDDR;
    }
    else if(BUTTON == kbMcLab2[3]){
        GPIOA_PDDR &= ~LEDSWITCH_4_GPIO_PDDR;
    }
}


/***************************************************************************************/
/* Method name:         readButton                                                     */
/* Method description:  Reads the data of the chosen button                            */
/* Input params:        iButtonNumber                                                  */
/*                          Which of the four buttons should be read                   */
/*                                                                                     */
/* Output params:       int button data                                                */
/*                          * 0 if the button is not pressed                           */
/*                          * 1 if the button is pressed                               */
/*                          * -1 if it was unable to read the desired button           */
/***************************************************************************************/
int readButton(int iButtonNumber){

    /*
     * Checks if the selected button is was previously configured
     * returns -1 if it wasn't configured and unable to read the data
     * or if iButtonNumber was outside of the [1,4] scope
     * else returns 1 if the button is pressed and 0 if it's not pressed
     */
    switch(iButtonNumber){
        case 1:
            if(BUTTON != kbMcLab2[0]){
                return -1;
            }
            return !(GPIOA_PDIR & LEDSWITCH_1_GPIO_PDDR);
            break;
        case 2:
            if(BUTTON != kbMcLab2[1]){
                return -1;
            }
            return !(GPIOA_PDIR & LEDSWITCH_2_GPIO_PDDR);
            break;
        case 3:
            if(BUTTON != kbMcLab2[2]){
                return -1;
            }
            return !(GPIOA_PDIR & LEDSWITCH_3_GPIO_PDDR);
            break;
        case 4:
            if(BUTTON != kbMcLab2[3]){
                return -1;
            }
            return !(GPIOA_PDIR & LEDSWITCH_4_GPIO_PDDR);
            break;
        default:
            break;
    }
    return -1;
}


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
int turnLED(int iLED, int iOnOrOff){
    /*
     * check if the selected LED was previously configured
     * returns -1 if it wasn't configured, returns 0 if chosen LED wasn't inside [1,4] scope
     * else switches the LED on or off according to the iOnOrOff parameter
     * and returns 1 to indicate the operation was a success
     */
    switch(iLED){
        case 1:
            if(LED != kbMcLab2[0]){
                return -1;
            }
            else{
                if(iOnOrOff){
                    GPIOA_PDOR |= LEDSWITCH_1_GPIO_PDDR;
                }
                else{
                    GPIOA_PDOR &= ~LEDSWITCH_1_GPIO_PDDR;
                }
            }
            return 1;
            break;
        case 2:
            if(LED != kbMcLab2[1]){
                return -1;
            }
            else{
                if(iOnOrOff){
                    GPIOA_PDOR |= LEDSWITCH_2_GPIO_PDDR;
                }
                else{
                    GPIOA_PDOR &= ~LEDSWITCH_2_GPIO_PDDR;
                }
            }
            return 1;
            break;
        case 3:
            if(LED != kbMcLab2[2]){
                return -1;
            }
            else{
                if(iOnOrOff){
                    GPIOA_PDOR |= LEDSWITCH_3_GPIO_PDDR;
                }
                else{
                    GPIOA_PDOR &= ~LEDSWITCH_3_GPIO_PDDR;
                }
            }
            return 1;
            break;
        case 4:
            if(LED != kbMcLab2[3]){
                return -1;
            }
            else{
                if(iOnOrOff){
                    GPIOA_PDOR |= LEDSWITCH_4_GPIO_PDDR;
                }
                else{
                    GPIOA_PDOR &= ~LEDSWITCH_4_GPIO_PDDR;
                }
            }
            return 1;
            break;
        default:
            return 0;
            break;
    }
}


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
int setLED(int iLED){
    /*
     * check if the selected LED was previously configured
     * returns -1 if it wasn't configured, returns 0 if chosen LED wasn't inside the [1,4]
     * else switches the LED on
     * and returns 1 to indicate the operation was a success
     */
    switch(iLED){
        case 1:
            if(LED != kbMcLab2[0]){
                return -1;
            }
            else{
                GPIOA_PSOR |= LEDSWITCH_1_GPIO_PDDR;
            }
            return 1;
            break;
        case 2:
            if(LED != kbMcLab2[1]){
                return -1;
            }
            else{
                GPIOA_PSOR |= LEDSWITCH_2_GPIO_PDDR;
            }
            return 1;
            break;
        case 3:
            if(LED != kbMcLab2[2]){
                return -1;
            }
            else{
                GPIOA_PSOR |= LEDSWITCH_3_GPIO_PDDR;
            }
            return 1;
            break;
        case 4:
            if(LED != kbMcLab2[3]){
                return -1;
            }
            else{
                GPIOA_PSOR |= LEDSWITCH_4_GPIO_PDDR;
            }
            return 1;
            break;
        default:
            return 0;
            break;
    }
}


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
int clearLED(int iLED){
    /*
     * check if the selected LED was previously configured
     * returns -1 if it wasn't configured, returns 0 if chosen LED wasn't inside the [1,4]
     * else switches the LED off
     * and returns 1 to indicate the operation was a success
     */
    switch(iLED){
        case 1:
            if(LED != kbMcLab2[0]){
                return -1;
            }
            else{
                GPIOA_PCOR |= LEDSWITCH_1_GPIO_PDDR;
            }
            return 1;
            break;
        case 2:
            if(LED != kbMcLab2[1]){
                return -1;
            }
            else{
                GPIOA_PCOR |= LEDSWITCH_2_GPIO_PDDR;
            }
            return 1;
            break;
        case 3:
            if(LED != kbMcLab2[2]){
                return -1;
            }
            else{
                GPIOA_PCOR |= LEDSWITCH_3_GPIO_PDDR;
            }
            return 1;
            break;
        case 4:
            if(LED != kbMcLab2[3]){
                return -1;
            }
            else{
                GPIOA_PCOR |= LEDSWITCH_4_GPIO_PDDR;
            }
            return 1;
            break;
        default:
            return 0;
            break;
    }
}


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
int toggleLED(int iLED){
    /*
     * check if the selected LED was previously configured
     * returns -1 if it wasn't configured, returns 0 if chosen LED wasn't inside the [1,4]
     * else toggles the LED
     * and returns 1 to indicate the operation was a success
    */
    switch(iLED){
        case 1:
            if(LED != kbMcLab2[0]){
                return -1;
            }
            else{
                GPIOA_PTOR |= LEDSWITCH_1_GPIO_PDDR;
            }
            return 1;
            break;
        case 2:
            if(LED != kbMcLab2[1]){
                return -1;
            }
            else{
                GPIOA_PTOR |= LEDSWITCH_2_GPIO_PDDR;
            }
            return 1;
            break;
        case 3:
            if(LED != kbMcLab2[2]){
                return -1;
            }
            else{
                GPIOA_PTOR |= LEDSWITCH_3_GPIO_PDDR;
            }
            return 1;
            break;
        case 4:
            if(LED != kbMcLab2[3]){
                return -1;
            }
            else{
                GPIOA_PTOR |= LEDSWITCH_4_GPIO_PDDR;
            }
            return 1;
            break;
        default:
            return 0;
            break;
    }
}
