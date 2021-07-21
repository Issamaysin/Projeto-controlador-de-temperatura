/* ****************************************************************************** */
/* File name:        tacometro.c                                                  */
/* File description: Definitions of the tachometer methods and initialization     */
/* Author name:      Grupo 18 - Renato Pepe                                       */
/*                              Jo�o Victor Matoso                                */
/* Creation date:    04may2021                                                    */
/* Revision date:    05may2021                                                    */
/* ****************************************************************************** */

#include "tacometro.h"
#include "board.h"
#include "util.h"

/* global variables */
/* stores the current RPM data from the tachometer */
unsigned int uiTachometerData = 0;

/* **************************************************** */
/* Method name:        tachometer_init                  */
/* Method description: Initialize the Mclab2 tachometer */
/* Input params:       n/a                              */
/* Output params:      n/a                              */
/* **************************************************** */
void tachometer_init(void){
    /* release clock to TPM0 */
    SIM_SCGC6 |= 1<<24;

    /* set clock division factor to 1 */
    TPM0_SC &= ~(1<<0);
    TPM0_SC &= ~(1<<1);
    TPM0_SC &= ~(1<<2);

    /* release PORT E clock */
    SIM_SCGC5 |= 1<<13;

    /* set the PTE29 MUX to FTM_CLKIN0 (alt4 = 100) */
    PORTE_PCR29 &= ~(1<<8);
    PORTE_PCR29 &= ~(1<<9);
    PORTE_PCR29 |= 1<<10;

    /* select which external pin should be used as input (TPM0 - TPM_CLKIN0) */
    SIM_SOPT4 &= ~(1<<24);

    /* set count mode to up-counting */
    TPM0_SC &= ~(1<<5);

    /* set CMOD to external counter */
    TPM0_SC |= 1<<4;
    TPM0_SC &= ~(1<<3);
}

/* *************************************************************************************** */
/* Method name:        tachometer_readSensor                                               */
/* Method description: Reads the data from the tachometer and                              */
/*                     return its value converted to RPMs                                  */
/* Input params:       uiPeriod -> period of the window in ms (to convert pulses into RPM) */
/* Output params:      unsigned int -> return the read value in RPMs                       */
/* *************************************************************************************** */
unsigned int tachometer_readSensor(unsigned int uiPeriod){

    /* Access counter data */
    unsigned int uiCounterAux = TPM0_CNT;

    /* Compute rotational speed in RPM to the given period */
    unsigned int uiRPMValue = (uiCounterAux*1000*60)/(7*uiPeriod);

    /* reset TPM0 counter */
    TPM0_CNT = 0x0;

    /* update value in the global variable */
    uiTachometerData = uiRPMValue;

    return uiRPMValue;
}

/* ************************************************************ */
/* Method name:        tachometer_getSpeed                      */
/* Method description: Return the last computed value for the   */
/*                     tachometer speed in RPM                  */
/* Input params:       n/a                                      */
/* Output params:      unsigned int -> return the value in RPM  */
/* ************************************************************ */
unsigned int tachometer_getSpeed() {
    return uiTachometerData;
}

