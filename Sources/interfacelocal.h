/* *************************************************************** */
/* File name:        interfacelocal.h                              */
/* File description: Local interface, using the keyboard buttons   */
/* 					  and the LCD screen, declarations             */
/* Author name:      Grupo 18 - Renato Pepe                        */
/*                              Joao Victor Matoso                 */
/* Creation date:    16jun2021                                     */
/* Revision date:    16jun2021                                     */
/* *************************************************************** */
#ifndef SOURCES_INTERFACELOCAL_H_
#define SOURCES_INTERFACELOCAL_H_

#include "lcd.h"
#include "aquecedorECooler.h"
#include "ledSwi.h"
#include "pid.h"
#include "util.h"
#include "UART.h"

/* ******************************************************************  */
/* Method name:        localInterfaceHandler                           */
/* Method description: Method that will be called by the interruption, */
/*                     reads buttons and display LCD data              */
/* Input params:       n/a                                             */
/* Output params:      n/a                                             */
/* ******************************************************************  */
void localInterfaceHandler();

#endif /* SOURCES_INTERFACELOCAL_H_ */
