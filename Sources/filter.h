/* ***************************************************************** */
/* File name:        filter.h                                        */
/* File description:                                                 */
/* Author name:      João Victor Matoso, Renato Pepe                 */
/* Creation date:    15jun2021                                       */
/* Revision date:    15jun2021                                       */
/* ***************************************************************** */

#ifndef SOURCES_FILTER_H_
#define SOURCES_FILTER_H_

/* Exponential Moving Average coeficient */
#define BETA 0.1

/* ***************************************************************** */
/* Method name:        filter_init                                   */
/* Method description: Initialize both Exponential Moving Average    */
/*                     and Double Exponential Moving Average filters */
/*                     with the initial value                        */
/* Input params:       fInitValue: the initial value of the signal   */
/*                                 to be filtered                    */
/* Output params:      n/a                                           */
/* ***************************************************************** */
void filter_init(float fInitValue);

/* ***************************************************************** */
/* Method name:        filter_mainEma                                */
/* Method description: Computes the basic formula of the EMA filter  */
/*                     -->  y[k] = beta*x[k] + (1-beta)*y[k-1]       */
/* Input params:       fInput:  x[k]                                 */
/*                     fBeta:   beta                                 */
/*                     fStored: y[k-1]                               */
/* Output params:      y[k]: the filtered signal. It needs to be     */
/*                           stored in a global variable             */
/* ***************************************************************** */
float filter_mainEma(float fInput, float fStored);

/* ***************************************************************** */
/* Method name:        filter_ema                                    */
/* Method description: Applies the Exponential Moving Average filter */
/*                     on the input signal.                          */
/* Input params:       fInput: signal to be filtered                 */
/* Output params:      the filtered signal                           */
/* ***************************************************************** */
float filter_ema(float fInput);

/* ***************************************************************** */
/* Method name:        filter_dema                                   */
/* Method description: Applies the Double Exponential Moving Average */
/*                     filter on the input signal.                   */
/*                     The formula is:                               */
/*                     y[k] = 2*EMA(x[k]) - EMA(EMA(x[k]))           */
/* Input params:       fInput: signal to be filtered                 */
/* Output params:      the filtered signal                           */
/* ***************************************************************** */
float filter_dema(float fInput);

#endif /* SOURCES_FILTER_H_ */
