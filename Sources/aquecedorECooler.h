/* ******************************************************************************* */
/* File name:        aquecedorECooler.h                                            */
/* File description: Declarations of heater and cooler methods and initializations */
/* Author name:      Grupo 18 - Renato Pepe                                        */
/*                              João Victor Matoso                                 */
/* Creation date:    27apr2021                                                     */
/* Revision date:    20may2021                                                     */
/* ******************************************************************************* */

#ifndef SOURCES_AQUECEDORECOOLER_H_
#define SOURCES_AQUECEDORECOOLER_H_

/* ************************************************ */
/* Method name:        PWM_init                     */
/* Method description: Initialize the PWM signal    */
/*                       (module 1, both channels)  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void PWM_init(void);

/* **************************************************** */
/* Method name:        coolerfan_init                   */
/* Method description: Initialize the fan cooler device */
/* Input params:       n/a                              */
/* Output params:      n/a                              */
/* **************************************************** */
void coolerfan_init(void);

/* **************************************************** */
/* Method name:        heater_init                      */
/* Method description: Initialize the heater device     */
/* Input params:       n/a                              */
/* Output params:      n/a                              */
/* **************************************************** */
void heater_init(void);

/* *************************************************************************** */
/* Method name:        coolerfan_PWMDuty                                       */
/* Method description: Change the cooler duty cycle to the inputed value       */
/* Input params:       fCoolerDuty -> Duty cycle that will be applied on the   */
/*                      cooler, range from 0 to 1 where 0 = 0% and 1 = 100%    */
/* Output params:      n/a                                                     */
/* *************************************************************************** */
void coolerfan_PWMDuty(float fCoolerDuty);

/* *************************************************************************** */
/* Method name:        heater_PWMDuty                                          */
/* Method description: Change the heater duty cycle to the inputed value       */
/* Input params:       fHeaterDuty -> Duty cycle that will be applied on the   */
/*                      heater, range from 0 to 1 where 0 = 0% and 1 = 100%    */
/* Output params:      n/a                                                     */
/* *************************************************************************** */
void heater_PWMDuty(float fHeaterDuty);

/* *************************************************************************** */
/* Method name:        getDutyCycleCooler                                      */
/* Method description: Reads the cooler duty cycle from the register           */
/* Input params:       n/a                                                     */
/* Output params:      float -> Duty cycle [0,1]                               */
/* *************************************************************************** */
float getDutyCycleCooler();

/* *************************************************************************** */
/* Method name:        getDutyCycleHeater                                      */
/* Method description: Reads the heater duty cycle from the register           */
/* Input params:       n/a                                                     */
/* Output params:      float -> Duty cycle [0,1]                               */
/* *************************************************************************** */
float getDutyCycleHeater();


#endif /* SOURCES_AQUECEDORECOOLER_H_ */
