/* ***************************************************************** */
/* File name:        main.c                                          */
/* File description: Main file for the final project of temperature  */
/*                   controller on the target processor MKL25Z128VLK4*/
/*                                                                   */
/* Author name:      Grupo 18 - Renato Pepe                          */
/*                              Joao Victor Matoso                   */
/* Creation date:    10jun2021                                       */
/* Revision date:    19may2021                                       */
/* ***************************************************************** */

/* our includes */
#include "util.h"
#include "mcg.h"
#include "ledrgb.h"
#include "UART.h"
#include "aquecedorECooler.h"
#include "ledSwi.h"
#include "adc.h"
#include "lcd.h"
#include "pid.h"
#include "lptmr.h"
#include "fsl_debug_console.h"
#include "communicationStateMachine.h"
#include "filter.h"
#include "tacometro.h"
#include "interfacelocal.h"
#include "timer.h"

/* global variables */
// counter to divide the frequency of the interruption to make tachometer to read its sensor every 300ms
unsigned int uiTachometerTimer = 0;
// counter to divide the frequency of the interruption to make local interface update every 500ms
unsigned int uiInterfaceTimer = 0;
// current measured temperature after the filter is applied
unsigned int fFilteredTemperature;

/* ************************************************ */
/* Method name:        boardInit                    */
/* Method description: main board all needed        */
/*                     initializations              */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void boardInit(void)
{
    /* clock configuration and initialization */
    mcg_clockInit();

    /* initialize the PWM signal to control the heater and cooler */
    PWM_init();

    /* initialize the cooler */
    coolerfan_init();

    /* initialize the heater */
    heater_init();

    /* initialize the adc converter */
    adc_initADCModule();

    /* start RGB LED */
    ledrgb_init();
    ledrgb_write(0);

    /* init keyboard with buttons 2, 3 and 4 */
	keyboard kbKeyboardOn[4] = {NOTSET, NOTSET, NOTSET, BUTTON};
	initKeyboard(kbKeyboardOn);

	/* Configure the UART module */
	UART0_init();
	
	/* Enable UART interruptions */
	UART0_enableIRQ();

    /* initialize the lcd display */
    lcd_initLcd();

    /* initialize the tachometer */
    tachometer_init();

    /* initialize PID */
    pid_init();
    
    /* initialize filter with current temperature */
    filter_init(adc_getTemperature());

    /* initialize timer module with period of 100 ms*/
    timer_init(100);
}

/* ************************************************* */
/* Method name:        periodic_temperatureControl   */
/* Method description: periodic task for temperature */
/*                     control                       */
/* Input params:       n/a                           */
/* Output params:      n/a                           */
/* ************************************************* */
void periodic_temperatureControl(void){
    /* Read temperature of the resistor */
    float fCurrentTemperature = adc_getTemperature();
    
    /* Filters data using a Exponential Moving Average filter */
    fFilteredTemperature = filter_dema(fCurrentTemperature);

    /* Compute heater duty cycle with PID control and update it if PID is on */
    if(pid_isOn()){
    	heater_PWMDuty(pidUpdateData(fFilteredTemperature)/100);
    }

    /* print temp and heater DC on the UART constantly for PID tuning */
    // char tempAtual[10];
    // convertFloatToString(fCurrentTemperature, tempAtual, 7);
    // debug_printf("T= ");
    // debug_printf(tempAtual);
    // debug_printf(" ");

    // char tempFilt[10];
    // convertFloatToString(fFilteredTemperature, tempAtual, 7);
    // debug_printf("Tf= ");
    // debug_printf(tempFilt);
    // debug_printf(" ");
    // returnParam('a');
}


/* ************************************************** */
/* Method name:        periodic_tachometerReadData    */
/* Method description: periodic task for updating the */
/*                     tachometer speed data          */
/* Input params:       n/a                            */
/* Output params:      n/a                            */
/* ************************************************** */
void periodic_tachometerReadData(void){
    /* updates the tachometer data each 1000 miliseconds */
    if(9 == uiTachometerTimer++){
        tachometer_readSensor(1000);
        uiTachometerTimer = 0;
    }
}

/* ************************************************** */
/* Method name:        periodic_localInterface        */
/* Method description: periodic task for handling the */
/*                     local interface                */
/* Input params:       n/a                            */
/* Output params:      n/a                            */
/* ************************************************** */
void periodic_localInterface(){
	/* read the buttons and update the LCD each 500ms */
	if(4 == uiInterfaceTimer++){
		localInterfaceHandler();

		/* changes LED color according to temperature */
		if(pid_isOn()){
			float fTempDifference = pid_getTemperatureSetpoint() - fFilteredTemperature;
			if(1.5f < fTempDifference){
				ledrgb_write(4);
			}else if(-1.5f > fTempDifference){
				ledrgb_write(1);
			}else{
				ledrgb_write(2);
			}
		}else{
			ledrgb_write(0);
		}

		uiInterfaceTimer = 0;
	}
}

/* **************************************************** */
/* Method name:        periodic_interruption            */
/* Method description: periodic task called every 100ms */
/* Input params:       n/a                              */
/* Output params:      n/a                              */
/* **************************************************** */
void periodic_interruption(void){
    /* Routine to update the tachometer data */
    periodic_tachometerReadData();

    /* Routine for temperature control */
    periodic_temperatureControl();

    /* Routine to update local interface information */
    periodic_localInterface();

    /* ticks the timer every 100 ms */
    timer_tick();
}

/* ************************************************ */
/* Method name:        main                         */
/* Method description: system entry point           */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
int main(void)
{
    /* board initializations */
    boardInit();

    /* set timer to 100ms and it triggers the periodic methods */
    tc_installLptmr0(100000, periodic_interruption);

    /* do nothing while the interruption handles everything*/
    while (1){

    }
}
