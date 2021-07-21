/* ***************************************************************** */
/* File name:        filter.c                                        */
/* File description:                                                 */
/* Author name:      João Victor Matoso, Renato Pepe                 */
/* Creation date:    15jun2021                                       */
/* Revision date:    15jun2021                                       */
/* ***************************************************************** */

#include "filter.h"

/* global variables for EMA */
float fStoredEma;

/* global variables for DEMA */
float fStoredDema;
float fStoredDemaEma;

/* ***************************************************************** */
/* Method name:        filter_init                                   */
/* Method description: Initialize both Exponential Moving Average    */
/*                     and Double Exponential Moving Average filters */
/*                     with the initial value                        */
/* Input params:       fInitValue: the initial value of the signal   */
/*                                 to be filtered                    */
/* Output params:      n/a                                           */
/* ***************************************************************** */
void filter_init(float fInitValue){
    fStoredEma = fInitValue;
    fStoredDema = fInitValue;
    fStoredDemaEma = fInitValue;
}

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
float filter_mainEma(float fInput, float fStored) {
    return fInput*BETA + (1-BETA)*fStored;
}

/* ***************************************************************** */
/* Method name:        filter_ema                                    */
/* Method description: Applies the Exponential Moving Average filter */
/*                     on the input signal.                          */
/* Input params:       fInput: signal to be filtered                 */
/*                     fBeta: algorithm coeficient                   */
/* Output params:      the filtered signal                           */
/* ***************************************************************** */
float filter_ema(float fInput) {
    fStoredEma = filter_mainEma(fInput, fStoredEma);
    return fStoredEma;
}

/* ***************************************************************** */
/* Method name:        filter_ema                                    */
/* Method description: Applies the Double Exponential Moving Average */
/*                     filter on the input signal.                   */
/*                     The formula is:                               */
/*                     y[k] = 2*EMA(x[k]) - EMA(EMA(x[k]))           */
/* Input params:       fInput: signal to be filtered                 */
/*                     fBeta: algorithm coeficient                   */
/* Output params:      the filtered signal                           */
/* ***************************************************************** */
float filter_dema(float fInput) {
    fStoredDema = filter_mainEma(fInput, fStoredDema);
    fStoredDemaEma = filter_mainEma(fStoredDema, fStoredDemaEma);
    return 2*fStoredDema - fStoredDemaEma;
}
