/* ***************************************************************** */
/* File name:        util.c                                          */
/* File description: This file has a couple of useful functions to   */
/*                   make programming more productive                */
/*                                                                   */
/*                   Remarks: The soft delays consider               */
/*                   core clock @ 40MHz                              */
/*                   bus clock @ 20MHz                               */
/*                                                                   */
/* Author name:      dloubach, Jo�o Victor Matoso, Renato Pepe       */
/* Creation date:    09jan2015                                       */
/* Revision date:    18jun2021                                       */
/* ***************************************************************** */

#include "util.h"

/* ************************************************ */
/* Method name:        util_genDelay088us           */
/* Method description: generates ~ 088 micro sec    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay088us(void)
{
    char i;
    for(i=0; i<120; i++)
    {
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
    }
}



/* ************************************************ */
/* Method name:        util_genDelay250us           */
/* Method description: generates ~   250 micro sec  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay250us(void)
{
    char i;
    for(i=0; i<120; i++)
    {
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
    }
    util_genDelay088us();
    util_genDelay088us();
}



/* ************************************************ */
/* Method name:        util_genDelay1ms             */
/* Method description: generates ~   1 mili sec     */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay1ms(void)
{
    util_genDelay250us();
    util_genDelay250us();
    util_genDelay250us();
    util_genDelay250us();
}


/* ************************************************ */
/* Method name:        util_genDelay10ms            */
/* Method description: generates ~   10 mili sec    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay10ms(void)
{
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
}



/* ************************************************ */
/* Method name:        util_genDelay100ms           */
/* Method description: generates ~   100 mili sec   */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay100ms(void)
{
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
}


/* ************************************************ */
/* Method name:        util_genDelay500ms           */
/* Method description: generates ~   500 mili sec   */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay500ms(void)
{
    util_genDelay100ms();
    util_genDelay100ms();
    util_genDelay100ms();
    util_genDelay100ms();
    util_genDelay100ms();
}

/* *********************************************************** */
/* Method name:        stringToUnsignedInt                     */
/* Method description: Convert a string with numbers in ASCII  */
/*                     into an unsigned int variable           */
/* Input params:       ucString - string with number in ASCII  */
/* Output params:      number converted                        */
/* *********************************************************** */
unsigned int stringToUnsignedInt(unsigned char *ucString){
    int i = 0;
    unsigned int d = 1;
    unsigned int number = 0;

    /* go to the end of the string '\0' */
    while(ucString[i]){
        i++;
    }

    /* go to the first digit on the right */
    i--;

    /* loop the string from right to left, converting the number */
    while(i >= 0) {
        if(ucString[i] >= '0' && ucString[i] <= '9'){
            number += d * (ucString[i]-'0');
            d *= 10;
            i--;
        }
        else
            return 0;
    }

    return number;
}

/* ******************************************************************************************************* */
/* Method name:        convertFloatToString                                                                */
/* Method description: Convert a float number into a string of size uiSize. The algorithm will fit the     */
/*                     integer part, and the remaining free space will be filled up with the decimal part  */
/* Input params:       fNumber - number that will be converted into string                                 */
/*                     cText   - char array where fNumber will be written                                  */
/*                     uiSize  - size of cText array                                                       */
/* Output params:      n/a                                                                                 */
/* ******************************************************************************************************* */
void convertFloatToString(float fNumber, char* cText, unsigned int uiSize) {
    int iPos;
    int iDigits = 1;

    /* counts how many digits are in the integer part */
    while(fNumber >= 10){
        fNumber /= 10;
        iDigits++;
    }

    /* if the number doesn't fit inside the string, return string of '9's */
    if (iDigits >= uiSize) {
        for(iPos = 0; iPos < uiSize-1; iPos++){
            cText[iPos] = '9';
        }
        cText[iPos] = '\0';
        return;
    }

    /* obs: at this point, fNumber is always x.xxxxx */
    for(iPos = 0; iPos < uiSize-1; iPos++){
        /* if the loop reaches the comma position */
        if(0 == iDigits){
            cText[iPos] = ',';
        }

        /* everywhere else, extracts the most left digit and save it in the string */
        else {
            int iIntPart = (int) fNumber;
            fNumber -= iIntPart;
            cText[iPos] = iIntPart + '0';
            fNumber *= 10;
        }

        /* decrement integer digits counter */
        iDigits--;
    }

    /* remove the ',' in some cases where it would appear X, */
    if (',' == cText[iPos - 1]) {
           cText[iPos - 1] = ' ';
       }

    /* end of string */
    cText[iPos] = '\0';
}


/* ******************************************************************************************************* */
/* Method name:        convertStringToFloat                                                                */
/* Method description: Convert a string into a float number, ',' marks the decimal point and               */
/*                      '\0' marks the end of the string                                                   */
/*                      (obs: if string has more than one ',' then the second one will work as a '\0')     */
/* Input params:       cText   - start of the string                                                       */
/* Output params:      float   - converted number                                                          */
/* ******************************************************************************************************* */
float convertStringToFloat(unsigned char *ucText) {
    float fValue = 0;
    int iCount = 0;

    /* convert integer part */
    while (',' != ucText[iCount] && '\0' != ucText[iCount]) {
        fValue *= 10;
        fValue += ucText[iCount++] - '0';
    }

    /* convert decimal part */
    if (',' == ucText[iCount]) {
        int d = 10;
        iCount++;
        while ('\0' != ucText[iCount] && '0' <= ucText[iCount] && '9' >= ucText[iCount]) {
            float fAux = ucText[iCount++] - '0';
            fValue += fAux / d;
            d *= 10;
        }
    }

    return fValue;
}

/* ******************************************************************************************************* */
/* Method name:        append_string                                                                       */
/* Method description: This function appends the string cStringRight at the end of the string cStringBase  */
/* Input params:       cStringBase  - char array that will be used as base for the append                  */
/*                     uiSizeBase   - size of cStringBase array                                            */
/*                     cStringRight - char array that will be append on the right of cStringBase           */
/* Output params:                                                                                          */
/* ******************************************************************************************************* */
void append_string(char *cStringBase, unsigned int uiSizeBase, char *cStringRight){
    int iPos = 0;

    /* go to the end of the first string */
    while('\0' != cStringBase[iPos]){
        iPos++;
    }

    /* copy char by char from cStringRight to the end of cStringBase */
    while(iPos < uiSizeBase-1 && '\0' != *cStringRight){
        cStringBase[iPos] = *cStringRight;
        cStringRight++;
        iPos++;
    }

    /* end of the string */
    cStringBase[iPos] = '\0';
}




/* *********************************************************** */
/* Method name:        unsignedIntToString                     */
/* Method description: Convert an unsigned int variable        */
/*                     into a string                           */
/* Input params:       cString - string with number in ASCII   */
/*                     uiData - data that will be converted    */
/*                     iStringSize - max digits allowed        */
/* Output params:      n/a                                     */
/* *********************************************************** */
void unsignedIntToString(char* cString, unsigned int uiData, int iStringSize) {

    int iMaxSize = 1;
    for (int j = 0; j < iStringSize; j++) {
        iMaxSize *= 10;
    }

    if (iMaxSize < uiData) {
        cString[0] = 'X';
        cString[1] = 'X';
        cString[2] = 'X';
        cString[3] = '\0';
        return;
    }

    /*
     * cString array must have a size of at least 12 chars
     * the number will be written from right to left, from position 10 to 0 due to camera visibility
     */
    int i = iStringSize;

    /* insert '\0' at the end of string */
    cString[i] = '\0';
    i--;

    /* if the number to be written is zero, print just one zero */
    if (0 == uiData) {
        cString[i] = '0';
        i--;
    }

    /* isolate last digit and save it from right to left */
    while (0 < uiData && 0 <= i) {
        cString[i] = (char)(uiData % 10 + '0');
        uiData /= 10;
        i--;
    }
    /* complete with spaces */
    while (0 <= i) {
        cString[i] = '0';
        i--;
    }
}




