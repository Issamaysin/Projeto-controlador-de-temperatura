/* ******************************************************************************* */
/* File name:        tacometro.h                                                   */
/* File description: Declarations of the tachometer methods and initialization     */
/* Author name:      Grupo 18 - Renato Pepe                                        */
/*                              Jo�o Victor Matoso                                 */
/* Creation date:    04may2021                                                     */
/* Revision date:    05may2021                                                     */
/* ******************************************************************************* */


#ifndef SOURCES_TACOMETRO_H_
#define SOURCES_TACOMETRO_H_

/* **************************************************** */
/* Method name:        tachometer_init                  */
/* Method description: Initialize the Mclab2 tachometer */
/* Input params:       n/a                              */
/* Output params:      n/a                              */
/* **************************************************** */
void tachometer_init(void);


/* *************************************************************************************** */
/* Method name:        tachometer_readSensor                                               */
/* Method description: Reads the data from the tachometer and                              */
/*                     return its value converted to RPMs                                  */
/* Input params:       uiPeriod -> period of the window in ms (to convert pulses into RPM) */
/* Output params:      unsigned int -> return the read value in RPMs                       */
/* *************************************************************************************** */
unsigned int tachometer_readSensor(unsigned int uiPeriod);


/* ************************************************************ */
/* Method name:        tachometer_getSpeed                      */
/* Method description: Return the last computed value for the   */
/*                     tachometer speed in RPM                  */
/* Input params:       n/a                                      */
/* Output params:      unsigned int -> return the value in RPM  */
/* ************************************************************ */
unsigned int tachometer_getSpeed();

#endif /* SOURCES_TACOMETRO_H_ */
