/* ***************************************************************** */
/* File name:        pid.h                                           */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for handling the PID                 */
/* Author name:      julioalvesMS, IagoAF, rBacurau, grupo 18        */
/* Creation date:    21jun2018                                       */
/* Revision date:    18jun2021                                       */
/* ***************************************************************** */

#ifndef SOURCES_CONTROLLER_PID_H_
#define SOURCES_CONTROLLER_PID_H_


typedef struct pid_data_type {
	float fKp, fKi, fKd;         // PID gains
	float fError_previous;       // used in the derivative
	float fError_sum;            // integrator cumulative error
	float fPreviousFOut;
	float fTemperatureSetpoint;
	unsigned char ucPidOn;
} pid_data_type;


/* ************************************************ */
/* Method name:        pid_init                     */
/* Method description: Initialize the PID controller*/
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void pid_init(void);

/* ************************************************** */
/* Method name:        pid_turnOnOff                  */
/* Method description: Turn PID control on/off        */
/* Input params:       ucOnOff: 0 to turn off,        */
/*                              1 to turn on          */
/* Output params:      n/a                            */
/* ************************************************** */
void pid_turnOnOff(unsigned char ucOnOff);

/* ************************************************** */
/* Method name:        pid_isOn                       */
/* Method description: Get status of the PID on/off   */
/* Input params:       n/a                            */
/* Output params:      1 if turned on, 0 if off       */
/* ************************************************** */
unsigned char pid_isOn();

/* ************************************************** */
/* Method name:        pid_setTemperatureSetpoint     */
/* Method description: Set a new value for the PID    */
/*                     temperature setpoint           */
/* Input params:       fTempSetpoint: New value       */
/* Output params:      n/a                            */
/* ************************************************** */
void pid_setTemperatureSetpoint(float fTempSetpoint);

/* ************************************************** */
/* Method name:        pid_getTemperatureSetpoint     */
/* Method description: Get the current value for the  */
/*                     PID temperature setpoint       */
/* Input params:       n/a                            */
/* Output params:      Current value                  */
/* ************************************************** */
float pid_getTemperatureSetpoint();


/* ************************************************** */
/* Method name:        pid_setKp                      */
/* Method description: Set a new value for the PID    */
/*                     proportional constant          */
/* Input params:       fKp: New value                 */
/* Output params:      n/a                            */
/* ************************************************** */
void pid_setKp(float fKp);


/* ************************************************** */
/* Method name:        pid_getKp                      */
/* Method description: Get the value from the PID     */
/*                     proportional constant          */
/* Input params:       n/a                            */
/* Output params:      float: Value                   */
float pid_getKp(void);


/* ************************************************** */
/* Method name:        pid_setKi                      */
/* Method description: Set a new value for the PID    */
/*                     integrative constant           */
/* Input params:       fKi: New value                 */
/* Output params:      n/a                            */
/* ************************************************** */
void pid_setKi(float fKi);


/* ************************************************** */
/* Method name:        pid_getKi                      */
/* Method description: Get the value from the PID     */
/*                     integrative constant           */
/* Input params:       n/a                            */
/* Output params:      float: Value                   */
/* ************************************************** */
float pid_getKi(void);


/* ************************************************** */
/* Method name:        pid_setKd                      */
/* Method description: Set a new value for the PID    */
/*                     derivative constant            */
/* Input params:       fKd: New value                 */
/* Output params:      n/a                            */
/* ************************************************** */
void pid_setKd(float fKd);


/* ************************************************** */
/* Method name:        pid_getKd                      */
/* Method description: Get the value from the PID     */
/*                     derivative constant            */
/* Input params:       n/a                            */
/* Output params:      float: Value                   */
/* ************************************************** */
float pid_getKd(void);


/* ************************************************** */
/* Method name:        pid_updateData                 */
/* Method description: Update the control output      */
/*                     using the reference and sensor */
/*                     value                          */
/* Input params:       fSensorValue: Value read from  */
/*                     the sensor                     */
/* Output params:      float: New Control effort     */
/* ************************************************** */
float pidUpdateData(float fSensorValue);


#endif /* SOURCES_CONTROLLER_PID_H_ */
