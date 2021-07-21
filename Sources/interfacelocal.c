/* *************************************************************** */
/* File name:        interfacelocal.c                              */
/* File description: Local interface, using the keyboard buttons   */
/*                    and the LCD screen, definitions              */
/* Author name:      Grupo 18 - Renato Pepe                        */
/*                              Joao Victor Matoso                 */
/* Creation date:    16jun2021                                     */
/* Revision date:    18jun2021                                     */
/* *************************************************************** */

#include "interfacelocal.h"
#include "timer.h"


/* Menu types for local interface, each one controls a different aspect */
typedef enum {DEFAULT, TEMPSET, COOLTOMAX, PIDSWITCH, KP, KI, KD, COOLERDC, HEATERDC, TIMERSET, TIMERSTATUS, UART} menu;

menu mInterface = UART;
extern unsigned int uiTachometerData;
extern unsigned int fFilteredTemperature;
unsigned int uiTimerConfigTimeSeconds = 0;
unsigned int uiTimerConfigPIDStatus = 1;
unsigned int uiCoolToMaxStatus = 0;

/* ******************************************************************  */
/* Method name:        localInterfaceHandler                           */
/* Method description: Method that will be called by the interruption, */
/*                     reads buttons and display LCD data              */
/* Input params:       n/a                                             */
/* Output params:      n/a                                             */
/* ******************************************************************  */
void localInterfaceHandler(){

    char cLCDLine1[16] = "\0";
    char cLCDLine2[16] = "\0";

    /*
     * Button 4 changes to next interface
     * Button 2 decreases parameters / switch functions off
     * Button 3 increases parameters / switch functions on
    */
    int iButton1 = readButton(2);
    int iButton2 = readButton(3);
    int iButton4 = readButton(4);

    /* Seconds LCD line will always show current Temperature and setPoint Temperature */
    char cAuxLine2[5] = "T=";
    append_string(cLCDLine2, 16, cAuxLine2);
    convertFloatToString(fFilteredTemperature, cAuxLine2, 5);
    append_string(cLCDLine2, 16, cAuxLine2);
    cAuxLine2[0] = 'C';
    cAuxLine2[1] = ' ';
    cAuxLine2[2] = 'S';
    cAuxLine2[3] = '=';
    cAuxLine2[4] = '\0';
    append_string(cLCDLine2, 16, cAuxLine2);
    convertFloatToString(pid_getTemperatureSetpoint(), cAuxLine2, 5);
    append_string(cLCDLine2, 16, cAuxLine2);
    cLCDLine2[14] = 'C';
    cLCDLine2[15] = '\0';

    /* if Button 4 was pressed, change to next interface (unless it's on the UART menu) */
    if(1==iButton4 && UART != mInterface){
        mInterface++;
    }

    switch(mInterface){

    case DEFAULT:
        /* Default screen, will show heater DC and Cooler RPM on line 1 */
        /* [Aq=xx% Co=xxxx] */
        ;
        char cAuxAq[4] = "Aq=";
        append_string(cLCDLine1, 16, cAuxAq);
        char cHeaterDC[3];
        convertFloatToString(100*getDutyCycleHeater(), cHeaterDC, 3);
        append_string(cLCDLine1, 16, cHeaterDC);

        char cLCDCoolerText[10] = "% Co=";
        char cCoolerRPM[6];
        unsignedIntToString(cCoolerRPM, uiTachometerData, 4);
        append_string(cLCDCoolerText, 10, cCoolerRPM);
        append_string(cLCDLine1, 16, cLCDCoolerText);
        break;
    case TEMPSET:
        /* Menu to control the temperature setpoint */
        /* [T SP= xx,x] */

        /* increase or decreases setPoint temp by 0.5ºC according to button pressed */
        if(1==iButton1){
            pid_setTemperatureSetpoint(pid_getTemperatureSetpoint() - 0.5f);
        }else if(1==iButton2){
            pid_setTemperatureSetpoint(pid_getTemperatureSetpoint() + 0.5f);
        }

        /* Print setPoint data on line 1 */
        char cAuxSP[7] = "T SP= ";
        append_string(cLCDLine1, 16, cAuxSP);
        char cSetPoint[5];
        convertFloatToString(pid_getTemperatureSetpoint(), cSetPoint, 5);
        append_string(cLCDLine1, 16, cSetPoint);
        break;

    case COOLTOMAX:
    	/* Cools the system to room temperature, turns PID off, set heater DC to 0, and cooler DC to max */
    	/* [COOLMAX: xxx] */

    	/* if button 2 is pressed turns it off, if button 3 is pressed turns it on */
    	if(1==iButton1 && (1 == uiCoolToMaxStatus)){
    		uiCoolToMaxStatus = 0;
    		coolerfan_PWMDuty(0.0f);
    	}else if(1==iButton2 && 0 == uiCoolToMaxStatus){
    		uiCoolToMaxStatus = 1;
    		pid_turnOnOff(0);
    		heater_PWMDuty(0.0f);
    		coolerfan_PWMDuty(1.0);
    	}

    	/* print status on screen */
    	char cAuxCoolToMax[10] = "COOLMAX: ";
    	append_string(cLCDLine1, 16, cAuxCoolToMax);
    	if(uiCoolToMaxStatus){
    		cAuxCoolToMax[0] = ' ';
    		cAuxCoolToMax[1] = 'O';
    		cAuxCoolToMax[2] = 'N';
    		cAuxCoolToMax[3] = '\0';
    		append_string(cLCDLine1, 16, cAuxCoolToMax);
    	}else{
    		cAuxCoolToMax[0] = 'O';
    		cAuxCoolToMax[1] = 'F';
    		cAuxCoolToMax[2] = 'F';
    		cAuxCoolToMax[3] = '\0';
    		append_string(cLCDLine1, 16, cAuxCoolToMax);
    	}
    	break;
    case PIDSWITCH:
        /* Menu to switch the temperature controller on/off */
        /* [PID is xxx] */

        /* Button 2 turns PID off, Button 3 turns PID on */
        if(1==iButton1){
            pid_turnOnOff(0);
        }else if(1==iButton2){
            pid_turnOnOff(1);
        }

        /* Print PID status */
        char cAuxPID[8] = "PID is ";
        append_string(cLCDLine1, 16, cAuxPID);
        if(pid_isOn()){
            char cPIDon[3] = "ON";
            append_string(cLCDLine1, 16, cPIDon);
        }else{
            char cPIDoff[5] = "OFF";
            append_string(cLCDLine1, 16, cPIDoff);
        }
        break;
    case KP:
        /* Menu to display and change PID Kp parameter */
        /*[Kp = xxx]*/

        /* button 2 decreases Kp by 1 and button 3 increases by 1 */
        if(1==iButton1){
            pid_setKp(pid_getKp() - 1.0f);
        }else if(1==iButton2){
            pid_setKp(pid_getKp() + 1.0f);
        }

        /* print Kp data */
        char cAuxKp[6] = "Kp = ";
        append_string(cLCDLine1, 16, cAuxKp);
        convertFloatToString(pid_getKp(), cAuxKp, 4);
        append_string(cLCDLine1, 16, cAuxKp);
        break;
    case KI:
        /* Menu to display and change PID Ki parameter */
        /*[Ki = x,xx]*/

        /* button 2 decreases Ki by 0.05 and button 3 increases by 0.05 */
        if(1==iButton1){
            pid_setKi(pid_getKi() - 0.05f);
        }else if(1==iButton2){
            pid_setKi(pid_getKi() + 0.05f);
        }

        /* print Ki data */
        char cAuxKi[6] = "Ki = ";
        append_string(cLCDLine1, 16, cAuxKi);
        convertFloatToString(pid_getKi(), cAuxKi, 5);
        append_string(cLCDLine1, 16, cAuxKi);
        break;
    case KD:
        /* Menu to display and change PID Kd parameter */
        /* [Kd = xxx] */

        /* button 2 decreases Kd by 1 and button 3 increases by 1 */
        if(1==iButton1){
            pid_setKd(pid_getKd() - 1.0f);
        }else if(1==iButton2){
            pid_setKd(pid_getKd() + 1.0f);
        }

        /* print Kd data */
        char cAuxKd[6] = "Kd = ";
        append_string(cLCDLine1, 16, cAuxKd);
        convertFloatToString(pid_getKd(), cAuxKd, 4);
        append_string(cLCDLine1, 16, cAuxKd);
        break;
    case COOLERDC:
        /* Menu to display cooler info and change cooler DC */
        /* [C:DC=xx% R=xxxx] */

        /* button 2 decreases cooler DC by 5% and button 3 increases by 5% */
        if(1==iButton1){
            coolerfan_PWMDuty(getDutyCycleCooler() - 0.05f);
        }else if(1==iButton2){
            coolerfan_PWMDuty(getDutyCycleCooler() + 0.05f);
        }

        /* print cooler data */
        char cAuxCDC[6] = "C:DC=";
        append_string(cLCDLine1, 16, cAuxCDC);
        convertFloatToString(getDutyCycleCooler()*100, cAuxCDC, 3);
        append_string(cLCDLine1, 16, cAuxCDC);
        char cAuxCRPM[5] = "% R=";
        append_string(cLCDLine1, 16, cAuxCRPM);
        unsignedIntToString(cAuxCRPM, uiTachometerData, 4);
        append_string(cLCDLine1, 16, cAuxCRPM);
        break;
    case HEATERDC:
        /* menu to change the heater DC */
        /* [Aq:DC=xx%] */

        /* button 2 decreases heater DC by 5% and button 3 increases by 5% */
        if(1==iButton1){
            heater_PWMDuty(getDutyCycleHeater() - 0.05f);
        }else if(1==iButton2){
            heater_PWMDuty(getDutyCycleHeater() + 0.05f);
        }

        /* print heater data */
        char cAuxHDC[7] = "Aq:DC=";
        append_string(cLCDLine1, 16, cAuxHDC);
        convertFloatToString(getDutyCycleHeater()*100, cAuxHDC, 3);
        append_string(cLCDLine1, 16, cAuxHDC);
        cLCDLine1[8] = '%';
        cLCDLine1[9] = '\0';
        break;

    case TIMERSET:
        /* Configure the timer time and if the PID will be turned ON or OFF */
        /* [P:xxx t:xxxxmin] / [P:xxx t:xxxxs] */

        /*
         * if button 2 and 3 are pressed at the same time switch if PID is gonna be turned ON or OFF with timer
         * else changes the set time, button 1 decreases and button 2 increases time
         * set time increase/decrease changes to make user's life easier
         */
        if(1==iButton1 && 1==iButton2){
            if(uiTimerConfigPIDStatus){
                uiTimerConfigPIDStatus = 0;
            }else{
                uiTimerConfigPIDStatus = 1;
            }
        }else{
            if(0 == uiTimerConfigTimeSeconds){
                //if Timer time is at 0 button 1 does nothing and button 2 increases time by 5s
                if(1==iButton2){
                    uiTimerConfigTimeSeconds += 5;
                }
            }else if(0 < uiTimerConfigTimeSeconds && 300 > uiTimerConfigTimeSeconds){
                //if Timer time is bwetween 0s and 5min, button 1 and button 2 deacreses/increases time by 5s
                if(1==iButton1){
                    uiTimerConfigTimeSeconds -= 5;
                }else if(1==iButton2){
                    uiTimerConfigTimeSeconds += 5;
                }
            }else if(300 <= uiTimerConfigTimeSeconds && 3600 > uiTimerConfigTimeSeconds){
                //if Timer is between 5min and 1h, button 1 and 2 decreases/increases time by 1min
                if(1==iButton1){
                    uiTimerConfigTimeSeconds -= 60;
                }else if(1==iButton2){
                    uiTimerConfigTimeSeconds += 60;
                }
            }else if(3600 <= uiTimerConfigTimeSeconds && 599940 > uiTimerConfigTimeSeconds){
                //if Timer is between 1h and max(9999min), button 1 and 2 decreases/increases time by 5min
                if(1==iButton1){
                    uiTimerConfigTimeSeconds -= 300;
                }else if(1==iButton2){
                    uiTimerConfigTimeSeconds += 300;
                }
            }else if(599940 <= uiTimerConfigTimeSeconds){
                //if timer is at max button 2 does nothing and button 1 decreases time by 5min
                if(1==iButton1){
                    uiTimerConfigTimeSeconds -= 300;
                }
            }
        }

        /* print timer PID status (that timer will switch PID to) and time */
        char cAuxTimer[7] = "P:";
        append_string(cLCDLine1, 16, cAuxTimer);
        if(uiTimerConfigPIDStatus){
        	char cAuxPIDSwitchON[5] = "ON  ";
        	append_string(cLCDLine1, 16, cAuxPIDSwitchON);
        }else{
         	char cAuxPIDSwitchOFF[5] = "OFF ";
            append_string(cLCDLine1, 16, cAuxPIDSwitchOFF);
        }
        cAuxTimer[0] = 't';
        cAuxTimer[1] = ':';
        cAuxTimer[2] = '\0';
        append_string(cLCDLine1, 16, cAuxTimer);

        //if config time is less than 5 minutes display in seconds, else display in minutes.
        if(300 > uiTimerConfigTimeSeconds){
        	unsignedIntToString(cAuxTimer, uiTimerConfigTimeSeconds, 4);
        	append_string(cLCDLine1, 16, cAuxTimer);
        	cAuxTimer[0] = 's';
        	cAuxTimer[1] = '\0';
        	append_string(cLCDLine1, 16, cAuxTimer);
        }else{
        	unsignedIntToString(cAuxTimer, uiTimerConfigTimeSeconds/60, 4);
        	append_string(cLCDLine1, 16, cAuxTimer);
        	cAuxTimer[0] = 'm';
        	cAuxTimer[1] = 'i';
        	cAuxTimer[2] = 'n';
        	cAuxTimer[3] = '\0';
        	append_string(cLCDLine1, 16, cAuxTimer);
        }
        break;
    case TIMERSTATUS:
        /* Show if timer is on and how much time is left */
    	/* [isXXX t:xxxxmin] / [isxxx t:XminXXs] */

    	/* button 2 will deactivate timer, button 3 will turn it on with previosly set config  */
    	if(1==iButton1){
    		timer_abort();
    	}else if(1==iButton2){
    		timer_start(uiTimerConfigTimeSeconds, uiTimerConfigPIDStatus);
    	}

    	/* print if timer is on or off and time left */
    	char cAuxTimerStatus[8] = "is";
    	append_string(cLCDLine1, 16, cAuxTimerStatus);
    	if(timer_isOn()){
    		char cAuxTON[7] = "ON  t:";
    		append_string(cLCDLine1, 16, cAuxTON);
    	}else{
    		char cAuxTOFF[7] = "OFF t:";
    		append_string(cLCDLine1, 16, cAuxTOFF);
    	}

    	/* display only minutes if time left is greater than 10min, else show minutes and seconds */
    	unsigned int uiTimeLeft = timer_getTimeLeft();
    	if(10*60*1000 <= uiTimeLeft){
    		unsignedIntToString(cAuxTimerStatus, uiTimeLeft/(1000*60), 4);
    		append_string(cLCDLine1, 16, cAuxTimerStatus);
    		cAuxTimerStatus[0] = 'm';
    		cAuxTimerStatus[1] = 'i';
    		cAuxTimerStatus[2] = 'n';
    		cAuxTimerStatus[3] = '\0';
    		append_string(cLCDLine1, 16, cAuxTimerStatus);
    	}else{
    		unsignedIntToString(cAuxTimerStatus, uiTimeLeft/(1000*60), 1);
    		append_string(cLCDLine1, 16, cAuxTimerStatus);
    		cAuxTimerStatus[0] = 'm';
    		cAuxTimerStatus[1] = 'i';
    		cAuxTimerStatus[2] = 'n';
    		cAuxTimerStatus[3] = '\0';
    		append_string(cLCDLine1, 16, cAuxTimerStatus);
    		unsignedIntToString(cAuxTimerStatus, (uiTimeLeft/(1000))%60, 2);
    		append_string(cLCDLine1, 16, cAuxTimerStatus);
    		cAuxTimerStatus[0] = 's';
    		cAuxTimerStatus[1] = '\0';
    		append_string(cLCDLine1, 16, cAuxTimerStatus);
    	}
        break;
    case UART:
        /*
         * If the keyboard b2 and b3 are OFF then button4 will reactivate them
         * If the keyboard b2 and b3 are ON then button4 will switch to next menu
         * obs: turning the buttons 2 and 3 ON will deactivate UART
        */
        if(1==iButton4){
            if(-1 == iButton1){
                keyboard kbTurnButtonsOn[4] = {NOTSET, BUTTON, BUTTON, BUTTON};
                initKeyboard(kbTurnButtonsOn);
            }else{
                mInterface = DEFAULT;
            }
        }
        /* pressing button2 will switch button 2 and 3 off and activate UART */
        else if(1==iButton1){
            keyboard kbTurnButtonsOff[4] = {NOTSET, NOTSET, NOTSET, BUTTON};
            initKeyboard(kbTurnButtonsOff);
            /* Configure the UART module */
            UART0_init();
            /* Enable UART interruptions */
            UART0_enableIRQ();
        }

        /* print UART status */
        char cUARTAux[9] = "UART is ";
        append_string(cLCDLine1, 16, cUARTAux);
        if(-1 == iButton1){
            char cUARTOn[3] = "ON";
            append_string(cLCDLine1, 16, cUARTOn);
        }else{
            char cUARTOff[4] = "OFF";
            append_string(cLCDLine1, 16, cUARTOff);
        }
        break;
    }

    /* Updates LCD text */
    lcd_writeText(0, cLCDLine1);
    lcd_writeText(1, cLCDLine2);
}



