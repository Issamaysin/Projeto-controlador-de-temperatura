/* ***************************************************************** */
/* File name:        pid.c                                           */
/* File description: This file has a couple of useful functions to   */
/*                   control the implemented PID controller          */
/* Author name:      julioalvesMS, IagoAF, rBacurau, grupo 18        */
/* Creation date:    21jun2018                                       */
/* Revision date:    18jun2021                                       */
/* ***************************************************************** */

#include "pid.h"
#include "aquecedorECooler.h"

pid_data_type pidConfig;

/* ************************************************ */
/* Method name:        pid_init                     */
/* Method description: Initialize the PID controller*/
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void pid_init(void)
{
	/* PID tuning made on PC-3 */
	pidConfig.fKp = 10.0;
	pidConfig.fKi = 0.1;
	pidConfig.fKd = 20.0;
	pidConfig.fError_previous = 0;
	pidConfig.fError_sum = 0.0;
	pidConfig.fPreviousFOut = 0.0;
	pidConfig.fTemperatureSetpoint = 0.0;
	pidConfig.ucPidOn = 0;
}

/* ************************************************** */
/* Method name:        pid_turnOnOff                  */
/* Method description: Turn PID control on/off        */
/* Input params:       ucOnOff: 0 to turn off,        */
/*                              1 to turn on          */
/* Output params:      n/a                            */
/* ************************************************** */
void pid_turnOnOff(unsigned char ucOnOff) {
	/* Turn PID on */
	if(0 < ucOnOff){
		pidConfig.fError_previous = 0.0;
		pidConfig.fError_sum = 0.0;
		pidConfig.fPreviousFOut = 0.0;
		pidConfig.ucPidOn = 1;
	}
	/* Turn PID off */
	else {
		heater_PWMDuty(0);
		pidConfig.ucPidOn = 0;
	}
}

/* ************************************************** */
/* Method name:        pid_isOn                       */
/* Method description: Get status of the PID on/off   */
/* Input params:       n/a                            */
/* Output params:      1 if turned on, 0 if off       */
/* ************************************************** */
unsigned char pid_isOn() {
	return pidConfig.ucPidOn;
}

/* ************************************************** */
/* Method name:        pid_setTemperatureSetpoint     */
/* Method description: Set a new value for the PID    */
/*                     temperature setpoint           */
/* Input params:       fTempSetpoint: New value       */
/* Output params:      n/a                            */
/* ************************************************** */
void pid_setTemperatureSetpoint(float fTempSetpoint) {
	/* setPoint range is limited by 23ºC and 74ºC */
	if(74.0f >= fTempSetpoint && 23.0f <= fTempSetpoint){
		pidConfig.fError_sum = 0.0;
		pidConfig.fTemperatureSetpoint = fTempSetpoint;
	}
}

/* ************************************************** */
/* Method name:        pid_getTemperatureSetpoint     */
/* Method description: Get the current value for the  */
/*                     PID temperature setpoint       */
/* Input params:       n/a                            */
/* Output params:      Current value                  */
/* ************************************************** */
float pid_getTemperatureSetpoint() {
	return pidConfig.fTemperatureSetpoint;
}

/* ************************************************** */
/* Method name:        pid_setKp                      */
/* Method description: Set a new value for the PID    */
/*                     proportional constant          */
/* Input params:       fKp: New value                 */
/* Output params:      n/a                            */
/* ************************************************** */
void pid_setKp(float fKp)
{
	pidConfig.fKp = fKp;
}


/* ************************************************** */
/* Method name:        pid_getKp                      */
/* Method description: Get the value from the PID     */
/*                     proportional constant          */
/* Input params:       n/a                            */
/* Output params:      float: Value                   */
/* ************************************************** */
float pid_getKp(void)
{
	return pidConfig.fKp;
}


/* ************************************************** */
/* Method name:        pid_setKi                      */
/* Method description: Set a new value for the PID    */
/*                     integrative constant           */
/* Input params:       fKi: New value                 */
/* Output params:      n/a                            */
/* ************************************************** */
void pid_setKi(float fKi)
{
	pidConfig.fKi = fKi;
}


/* ************************************************** */
/* Method name:        pid_getKi                      */
/* Method description: Get the value from the PID     */
/*                     integrative constant           */
/* Input params:       n/a                            */
/* Output params:      float: Value                   */
/* ************************************************** */
float pid_getKi(void)
{
	return pidConfig.fKi;
}


/* ************************************************** */
/* Method name:        pid_setKd                      */
/* Method description: Set a new value for the PID    */
/*                     derivative constant            */
/* Input params:       fKd: New value                 */
/* Output params:      n/a                            */
/* ************************************************** */
void pid_setKd(float fKd)
{
	pidConfig.fKd = fKd;
}


/* ************************************************** */
/* Method name:        pid_getKd                      */
/* Method description: Get the value from the PID     */
/*                     derivative constant            */
/* Input params:       n/a                            */
/* Output params:      float: Value                   */
/* ************************************************** */
float pid_getKd(void)
{
	return pidConfig.fKd;
}


/* ************************************************** */
/* Method name:        pid_updateData                 */
/* Method description: Update the control output      */
/*                     using the reference and sensor */
/*                     value                          */
/* Input params:       fSensorValue: Value read from  */
/*                     the sensor                     */
/*                     fReferenceValue: Value used as */
/*                     control reference              */
/* Output params:      float: New Control effort     */
/* ************************************************** */
float pidUpdateData(float fSensorValue)
{
	float fError, fDifference, fOut;

	/* Check if PID is on */
	if(0 == pidConfig.ucPidOn){
		return 0.0f;
	}

	fError = pidConfig.fTemperatureSetpoint - fSensorValue;

	/* Anti-windup */
	if(100 > pidConfig.fPreviousFOut && 0 <= pidConfig.fPreviousFOut){
		pidConfig.fError_sum += fError;
	}

	fDifference = fError - pidConfig.fError_previous;

	fOut = pidConfig.fKp*fError
		 + pidConfig.fKi*pidConfig.fError_sum
		 + pidConfig.fKd*fDifference;

	pidConfig.fError_previous = fError;
	pidConfig.fPreviousFOut = fOut;

	if (fOut>100.0)
		fOut = 100.0;

	else if (fOut<0.0)
		fOut = 0.0;

	return fOut;
}
