/* ****************************************************************************** */
/* File name:        aquecedorECooler.c                                           */
/* File description: Definitions of heater and cooler methods and initializations */
/* Author name:      Grupo 18 - Renato Pepe                                       */
/*                              Jo�o Victor Matoso                                */
/* Creation date:    27apr2021                                                    */
/* Revision date:    20may2021                                                    */
/* ****************************************************************************** */


#include "board.h"
#include "aquecedorECooler.h"
#include "util.h"


/* ************************************************ */
/* Method name:        PWM_init                     */
/* Method description: Initialize the PWM signal    */
/*                       (module 1, both channels)  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void PWM_init(void){
    /* release clock to TPM1 */
    SIM_SCGC6 |= 1<<25;

    /* set clock division factor to 32 */
    TPM1_SC |= 1<<2;
    TPM1_SC &= ~(1<<1);
    TPM1_SC |= 1<<0;

    /* set the clock source to MCGFLLCLK (40MHz) */
    SIM_SOPT2 &= ~(1<<25);
    SIM_SOPT2 |= 1<<24;

    /* set count mode to up-counting */
    TPM1_SC &= ~(1<<5);

    /* set clock mode selection to increment with each clock pulse */
    TPM1_SC &= ~(1<<4);
    TPM1_SC |= 1<<3;

    /* set modulo value to 0xFFFE */
    TPM1_MOD = 0xFFFE;

    /*
     * Set level select and Channel mode to 10 (Edge-aligned PWM and High-true pulses)
     *
     * -obs: bit by bit operations were not working, only the first operation
     *      was being executed for each register, therefore we opted to store the values
     *      in a variable so only one register operation needed to be done for each register.
    */
    unsigned int uiTPM1_C0SC_aux = TPM1_C0SC;
    uiTPM1_C0SC_aux |= ((1<<3) | (1<<5));
    uiTPM1_C0SC_aux &= ~((1<<2) | (1<<4));
    TPM1_C0SC = uiTPM1_C0SC_aux;

    unsigned int uiTPM1_C1SC_aux = TPM1_C1SC;
    uiTPM1_C1SC_aux |= ((1<<3) | (1<<5));
    uiTPM1_C1SC_aux &= ~((1<<2) | (1<<4));
    TPM1_C1SC = uiTPM1_C1SC_aux;

    /*
     * Initializes both duty cycles to 0%
     * -obs: delay needed to ensure code will work if any changes to the duty cycle
     *       are made shortly after this method is called
    */
    TPM1_C0V = 0x0000;
    TPM1_C1V = 0x0000;
    util_genDelay100ms();
}

/* **************************************************** */
/* Method name:        coolerfan_init                   */
/* Method description: Initialize the fan cooler device */
/* Input params:       n/a                              */
/* Output params:      n/a                              */
/* **************************************************** */
void coolerfan_init(void){
    /* release PORT A clock */
    SIM_SCGC5 |= SIM_CLOCK_PORTA;

    /* set the MUX pin to PWM (011) */
    PORTA_PCR13 |= 0x300;
    PORTA_PCR13 &= ~(0x400);
}

/* **************************************************** */
/* Method name:        heater_init                      */
/* Method description: Initialize the heater device     */
/* Input params:       n/a                              */
/* Output params:      n/a                              */
/* **************************************************** */
void heater_init(void){
    /* release PORT A clock */
    SIM_SCGC5 |= SIM_CLOCK_PORTA;

    /* set the MUX pin to PWM (011) */
    PORTA_PCR12 |= 0x300;
    PORTA_PCR12 &= ~(0x400);
}

/* *************************************************************************** */
/* Method name:        coolerfan_PWMDuty                                       */
/* Method description: Change the cooler duty cycle to the inputed value       */
/* Input params:       fCoolerDuty -> Duty cycle that will be applied on the   */
/*                      cooler, range from 0 to 1 where 0 = 0% and 1 = 100%    */
/* Output params:      n/a                                                     */
/* *************************************************************************** */
void coolerfan_PWMDuty(float fCoolerDuty){

    /* If DC value is in the 0~1 range then execute method, otherwise do nothing */
    if(0 <= fCoolerDuty && 1 >= fCoolerDuty){

        /* Sets a float variable that multiply the max count value with the duty cycle */
        float fDC = 0xFFFF;
        fDC = fDC*fCoolerDuty;

        /* convert value to int and pass it to the duty cycle register, setting the new DC  */
        TPM1_C1V = (unsigned int)fDC;
    }
}

/* *************************************************************************** */
/* Method name:        heater_PWMDuty                                          */
/* Method description: Change the heater duty cycle to the inputed value       */
/* Input params:       fHeaterDuty -> Duty cycle that will be applied on the   */
/*                      heater, range from 0 to 1 where 0 = 0% and 1 = 100%    */
/* Output params:      n/a                                                     */
/* *************************************************************************** */
void heater_PWMDuty(float fHeaterDuty){

    /* If DC value is in the 0~1 range then execute method, otherwise do nothing */
    if(0 <= fHeaterDuty && 1 >= fHeaterDuty){

        /* Sets a float variable that multiply the max count value with the duty cycle */
        float fDC = 0xFFFF;
        fDC = fDC*fHeaterDuty;

        /* convert value to int and pass it to the duty cycle register, setting the new DC  */
        TPM1_C0V = (unsigned int)fDC;
    }
}

/* *************************************************************************** */
/* Method name:        getDutyCycleCooler                                      */
/* Method description: Reads the cooler duty cycle from the register           */
/* Input params:       n/a                                                     */
/* Output params:      float -> Duty cycle [0,1]                               */
/* *************************************************************************** */
float getDutyCycleCooler(){
    unsigned int uiCounter = TPM1_C1V;
    float fDC = (float)(uiCounter) / (float)(0xFFFF);
    return fDC;
}

/* *************************************************************************** */
/* Method name:        getDutyCycleHeater                                      */
/* Method description: Reads the heater duty cycle from the register           */
/* Input params:       n/a                                                     */
/* Output params:      float -> Duty cycle [0,1]                               */
/* *************************************************************************** */
float getDutyCycleHeater(){
    unsigned int uiCounter = TPM1_C0V;
    float fDC = (float)(uiCounter) / (float)(0xFFFF);
    return fDC;
}
