/* ******************************************************************** */
/* File name:        communicationStateMachine.h                        */
/* File description: Implementation of communication functions between  */
/*                   the user's machine and this embedded system        */
/*                                                                      */
/* Author name:      Grupo 18 - Renato Pepe                             */
/*                              Joao Victor Matoso                      */
/* Creation date:    18may2021                                          */
/* Revision date:    19jun2021                                          */
/* ******************************************************************** */

#ifndef SOURCES_COMMUNICATIONSTATEMACHINE_H_
#define SOURCES_COMMUNICATIONSTATEMACHINE_H_

/* ******************************************************************************************************* */
/* Method name:        processByteCommunication                                                            */
/* Method description: Method that handles the UART interruption, works like a state machine               */
/* Input params:       ucByte - byte that was read from the UART                                           */
/* Output params:      n/a                                                                                 */
/* ******************************************************************************************************* */
void processByteCommunication(unsigned char ucByte);

/* ******************************************************************************************************* */
/* Method name:        setParam                                                                            */
/* Method description: Set the given parameter to the given value, or do the needed configurations         */
/*                      according to the parameter, and prints acknowledge                                 */
/* Input params:       ucParam   - which parameter will be altered                                         */
/*                     ucValue   - string that contains the value (in ASCII)                               */
/* Output params:      n/a                                                                                 */
/* ******************************************************************************************************* */
void setParam(unsigned char ucParam, unsigned char *ucValue);

/* *********************************************************************************** */
/* Method name:        returnParam                                                     */
/* Method description: Print on the putty terminal the requested parameter value       */
/* Input params:       ucParam   - which parameter will have its value printed         */
/* Output params:      n/a                                                             */
/* *********************************************************************************** */
void returnParam(unsigned char ucParam);


#endif /* SOURCES_COMMUNICATIONSTATEMACHINE_H_ */
