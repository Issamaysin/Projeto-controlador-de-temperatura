/* ******************************************************************** */
/* File name:        communicationStateMachine.c                        */
/* File description: Implementation of communication functions between  */
/*                   the user's machine and this embedded system        */
/*                                                                      */
/* Author name:      Grupo 18 - Renato Pepe                             */
/*                              Joao Victor Matoso                      */
/* Creation date:    18may2021                                          */
/* Revision date:    19jun2021                                          */
/* ******************************************************************** */

#include "communicationStateMachine.h"
#include "util.h"
#include "fsl_debug_console.h"
#include "ledSwi.h"
#include "aquecedorECooler.h"
#include "adc.h"
#include "lcd.h"
#include "pid.h"
#include "tacometro.h"
#include "timer.h"

/*states of the UART communication state machine*/
#define IDLE    '0'
#define READY   '1'
#define GET     '2'
#define SET     '3'
#define PARAM   '4'
#define VALUE   '5'

/*Max digits which will be read on the SET state*/
#define MAX_VALUE_LENGTH    7

/*Global variables*/
unsigned char ucUartState = IDLE;
unsigned char ucValueCount;
extern unsigned int uiTimerConfigTimeSeconds;
extern unsigned int uiTimerConfigPIDStatus;

/* ******************************************************************************************************* */
/* Method name:        processByteCommunication                                                            */
/* Method description: Method that handles the UART interruption, works like a state machine               */
/* Input params:       ucByte - byte that was read from the UART                                           */
/* Output params:      n/a                                                                                 */
/* ******************************************************************************************************* */
void processByteCommunication(unsigned char ucByte) {
    static unsigned char ucParam;
    static unsigned char ucValue[MAX_VALUE_LENGTH + 1];

    if ('#' == ucByte) {
        ucUartState = READY;
    } else {
        if (IDLE != ucUartState) {
            switch (ucUartState) {
            case READY:
                switch (ucByte) {
                case 'g':
                    ucUartState = GET;
                    break;
                case 's':
                    ucUartState = SET;
                    break;
                default:
                    ucUartState = IDLE;
                }
                break;

            case GET:
                if ('t' == ucByte || 'c' == ucByte || 'a' == ucByte || 'p' == ucByte || 'i' == ucByte
                		|| 'd' == ucByte || 's' == ucByte || 'g' == ucByte || 'r' == ucByte || 'm' == ucByte) {
                    ucParam = ucByte;
                    ucUartState = PARAM;
                } else
                    ucUartState = IDLE;
                break;

            case SET:
                if ('t' == ucByte || 'i' == ucByte || 'c' == ucByte || 'a' == ucByte || 'p' == ucByte
                		|| 'd' == ucByte || 's' == ucByte || 'b' == ucByte || 'n' == ucByte || 'm' == ucByte || 'k' == ucByte) {
                    ucParam = ucByte;
                    ucValueCount = 0;
                    ucUartState = VALUE;
                } else
                    ucUartState = IDLE;
                break;

            case PARAM:
                if(';' == ucByte)
                    returnParam(ucParam);
                ucUartState = IDLE;
                break;

            case VALUE:
                if(('0' <= ucByte && '9' >= ucByte) || ',' == ucByte){
                    if(ucValueCount < MAX_VALUE_LENGTH)
                        ucValue[ucValueCount++] = ucByte;
                }
                else {
                    if(';' == ucByte){
                        ucValue[ucValueCount] = '\0';
                        setParam(ucParam, ucValue);
                    }
                    ucUartState = IDLE;
                }
                break;
            }
        }
    }
}

/* ******************************************************************************************************* */
/* Method name:        setParam                                                                            */
/* Method description: Set the given parameter to the given value, or do the needed configurations         */
/*                      according to the parameter, and prints acknowledge                                 */
/* Input params:       ucParam   - which parameter will be altered                                         */
/*                     ucValue   - string that contains the value (in ASCII)                               */
/* Output params:      n/a                                                                                 */
/* ******************************************************************************************************* */
void setParam(unsigned char ucParam, unsigned char *ucValue){
    float fValue = convertStringToFloat(ucValue);

    /*
     * debug printf method takes a signed char, this block turns ucValue into a signed char
     *  to avoid any conflict involving the data types
    */
    char cValue[MAX_VALUE_LENGTH + 1];
    unsigned int uiValueCounter = 0;
    while(*ucValue){
    	cValue[uiValueCounter] = *(ucValue++);
    	uiValueCounter++;
    }
    cValue[uiValueCounter] = '\0';

    switch(ucParam){
    /* Interface operation mode */

    case 'k':
      /* Switches keyboard on
       * obs: can't switch it off since keyboard and UART share some common pins on PORT A,
       *      this means that UART can switch it on but after that switch the UART is deactivated
       *      If user try to give UART command while keyboard is activated it may press the button 2
      */
      if(fValue){
    	  /* response */
    	  debug_printf("Keyboard activated (UART disabled) \n \r");
          keyboard kbConfig[4] = {NOTSET, BUTTON, BUTTON, BUTTON};
          initKeyboard(kbConfig);
      }
        break;

    /* Temperature set point */
    case 't':
        pid_setTemperatureSetpoint(fValue);

        /* response */
        debug_printf("Temperature setPoint set to:");
        debug_printf(cValue);
        debug_printf("\n \r");
        break;

    /* Cooler duty cycle */
    case 'c':
        coolerfan_PWMDuty(fValue);

        /* response */
        debug_printf("Cooler DC set to:");
        debug_printf(cValue);
        debug_printf("\n \r");
        break;

    /* Heater duty cycle */
    case 'a':
        /* heater duty cycle is capped at 50% to not damage the diode */
        if(0.5 < fValue){
            fValue = 0.5;
            debug_printf("#aError DC>0,5; \n \r");
            return;
        }
        heater_PWMDuty(fValue);

        /* response */
        debug_printf("Heater DC set to:");
        debug_printf(cValue);
        debug_printf("\n \r");
        break;

    /**** Set PID parameters ****/
    /* Proportional gain */
    case 'p':
        pid_setKp(fValue);

        /* response */
        debug_printf("Kp set to:");
        debug_printf(cValue);
        debug_printf("\n \r");
        break;

    /* Integral gain */
    case 'i':
        pid_setKi(fValue);

        /* response */
        debug_printf("Ki set to:");
        debug_printf(cValue);
        debug_printf("\n \r");
        break;

    /* Derivative gain */
    case 'd':
        pid_setKd(fValue);

        /* response */
        debug_printf("Kd set to:");
        debug_printf(cValue);
        debug_printf("\n \r");
        break;

    /* Switch control on/off */
    case 's':
        if(1 == fValue) {
        	debug_printf("PID is ON");
            pid_turnOnOff(1);
        }
        else {
        	debug_printf("PID is OFF");
            pid_turnOnOff(0);
        }
        debug_printf("\n \r");
        break;

    /* timer setup: turn PID on or off */
    case 'b':
    	if(1 == fValue){
    		debug_printf("Timer will turn PID ON \n \r");
    		uiTimerConfigPIDStatus = 1;
    	}else{
    		debug_printf("Timer will turn PID OFF \n \r");
    		uiTimerConfigPIDStatus = 0;
    	}
    	break;

    /* timer setup: time (in seconds)*/
    case 'n':
    	;
    	unsigned int uiTimerTime = (unsigned int)fValue;
    	//max value is equal to 9999min
    	if(599940 < uiTimerTime){
    		uiTimerTime = 599940;
    	}
    	uiTimerConfigTimeSeconds = uiTimerTime;
    	debug_printf("Timer is going to be set to: ");
    	char cAuxTimerTimeSet[7];
    	unsignedIntToString(cAuxTimerTimeSet, uiTimerConfigTimeSeconds, 6);
    	debug_printf(cAuxTimerTimeSet);
    	debug_printf("seconds \n \r");
    	break;
    /* turn timer on or off */
    case 'm':
    	if(1 == fValue){
    		debug_printf("Timer turned ON \n \r");
    		timer_start(uiTimerConfigTimeSeconds, uiTimerConfigPIDStatus);
    	}else{
    		debug_printf("Timer turned OFF \n \r");
    		timer_abort();
    	}
    	break;
    }
}

/* *********************************************************************************** */
/* Method name:        returnParam                                                     */
/* Method description: Print on the putty terminal the requested parameter value       */
/* Input params:       ucParam   - which parameter will have its value printed         */
/* Output params:      n/a                                                             */
/* *********************************************************************************** */
void returnParam(unsigned char ucParam){
    char cResponseValueString[8];

    switch(ucParam){
    /* Current temperature */
    case 't':
        /* read temperature and convert to string */
        convertFloatToString(adc_getTemperature(), cResponseValueString, 7);

        /* response */
        debug_printf("Current Temperature = ");
        debug_printf(cResponseValueString);
        debug_printf("\n \r");
        break;

    /* Cooler duty cycle */
    case 'c':
        /* read cooler duty cycle and convert to string */
        convertFloatToString(getDutyCycleCooler(), cResponseValueString, 7);

        /* response */
        debug_printf("Current Cooler DC = ");
        debug_printf(cResponseValueString);
        debug_printf("\n \r");
        break;

    /* Heater duty cycle */
    case 'a':
        /* read heater duty cycle and convert to string */
        convertFloatToString(getDutyCycleHeater(), cResponseValueString, 7);

        /* response */
        debug_printf("Current Heater DC = ");
        debug_printf(cResponseValueString);
        debug_printf("\n \r");
        break;

    /**** Get PID parameters ****/
    /* Proportional gain */
    case 'p':
        convertFloatToString(pid_getKp(), cResponseValueString, 7);

        /* response */
        debug_printf("Kp = ");
        debug_printf(cResponseValueString);
        debug_printf("\n \r");
        break;

    /* Integral gain */
    case 'i':
        convertFloatToString(pid_getKi(), cResponseValueString, 7);

        /* response */
        debug_printf("Ki = ");
        debug_printf(cResponseValueString);
        debug_printf("\n \r");
        break;

    /* Derivative gain */
    case 'd':
        convertFloatToString(pid_getKd(), cResponseValueString, 7);

        /* response */
        debug_printf("Kd = ");
        debug_printf(cResponseValueString);
        debug_printf("\n \r");
        break;

    /* check PID status */
    case 's':
    	if(pid_isOn()){
    		debug_printf("PID is on \n \r");
    	}else{
    		debug_printf("PID if off \n \r");
    	}
        break;

     /* Check temperature setPoint */
    case 'g':
    	convertFloatToString(pid_getTemperatureSetpoint(), cResponseValueString, 7);

    	/* response */
        debug_printf("Temp setPoint = ");
        debug_printf(cResponseValueString);
        debug_printf("\n \r");
    	break;

    /* check cooler RPM */
    case 'r':
    	unsignedIntToString(cResponseValueString, tachometer_getSpeed(), 7);

    	/* response */
    	debug_printf("Cooler RPM = ");
    	debug_printf(cResponseValueString);
    	debug_printf("\n \r");
    	break;

    /* check timer status */
    case'm':
    	debug_printf("Timer is: ");

    	if(1 == timer_isOn()){
    		debug_printf("ON, with ");
    		unsignedIntToString(cResponseValueString, timer_getTimeLeft()/1000, 6);
    		debug_printf(cResponseValueString);
    		debug_printf("seconds left \n \r");


    	}else{
    		debug_printf("OFF \n \r");
    	}
    	break;
    }
}
