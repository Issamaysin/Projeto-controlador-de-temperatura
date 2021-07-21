/* ***************************************************************** */
/* File name:        util.h                                          */
/* File description: Header file containing the function/methods     */
/*                   prototypes of util.c                            */
/*                   Those delays were tested under the following:   */
/*                   core clock @ 40MHz                              */
/*                   bus clock @ 20MHz                               */
/* Author name:      dloubach, Jo�o Victor Matoso, Renato Pepe       */
/* Creation date:    09jan2015                                       */
/* Revision date:    18jun2021                                       */
/* ***************************************************************** */

#ifndef UTIL_H
#define UTIL_H

/* ************************************************ */
/* Method name:        util_genDelay088us           */
/* Method description: generates ~ 088 micro sec    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay088us(void);


/* ************************************************ */
/* Method name:        util_genDelay250us           */
/* Method description: generates ~   250 micro sec  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay250us(void);


/* ************************************************ */
/* Method name:        util_genDelay1ms             */
/* Method description: generates ~   1 mili sec     */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay1ms(void);


/* ************************************************ */
/* Method name:        util_genDelay10ms            */
/* Method description: generates ~   10 mili sec    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay10ms(void);

/* ************************************************ */
/* Method name:        util_genDelay10ms            */
/* Method description: generates ~   100 mili sec    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay100ms(void);

/* ************************************************ */
/* Method name:        util_genDelay500ms           */
/* Method description: generates ~   500 mili sec   */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay500ms(void);

/* *********************************************************** */
/* Method name:        stringToUnsignedInt                     */
/* Method description: Convert a string with numbers in ASCII  */
/*                     into an unsigned int variable           */
/* Input params:       ucString - string with number in ASCII  */
/* Output params:      number converted                        */
/* *********************************************************** */
unsigned int stringToUnsignedInt(unsigned char *ucString);

/* *********************************************************** */
/* Method name:        unsignedIntToString                     */
/* Method description: Convert an unsigned int variable        */
/*                     into a string                           */
/* Input params:       cString - string with number in ASCII   */
/*                     uiData - data that will be converted    */
/*                     iStringSize - max digits allowed        */
/* Output params:      n/a                                     */
/* *********************************************************** */
void unsignedIntToString(char* cString, unsigned int uiData, int iStringSize);

/* ******************************************************************************************************* */
/* Method name:        convertFloatToString                                                                */
/* Method description: Convert a float number into a string of size uiSize. The algorithm will fit the     */
/*                     integer part, and the remaining free space will be filled up with the decimal part  */
/* Input params:       fNumber - number that will be converted into string                                 */
/*                     cText   - char array where fNumber will be written                                  */
/*                     uiSize  - size of text (obs: string size needs to be (size of text)+1               */
/* Output params:      n/a                                                                                 */
/* ******************************************************************************************************* */
void convertFloatToString(float fNumber, char* cText, unsigned int uiSize);

/* ******************************************************************************************************* */
/* Method name:        convertStringToFloat                                                                */
/* Method description: Convert a string into a float number, ',' marks the decimal point and               */
/*                      '\0' marks the end of the string                                                   */
/*                      (obs: if string has more than one ',' then the second one will work as a '\0')     */
/* Input params:       cText   - start of the string                                                       */
/* Output params:      float   - converted number                                                          */
/* ******************************************************************************************************* */
float convertStringToFloat(unsigned char *cText);

/* ******************************************************************************************************* */
/* Method name:        append_string                                                                       */
/* Method description: This function appends the string cStringRight at the end of the string cStringBase  */
/* Input params:       cStringBase  - char array that will be used as base for the append                  */
/*                     uiSizeBase   - size of cStringBase array                                            */
/*                     cStringRight - char array that will be append on the right of cStringBase           */
/* Output params:                                                                                          */
/* ******************************************************************************************************* */
void append_string(char *cStringBase, unsigned int uiSizeBase, char *cStringRight);

#endif /* UTIL_H */
