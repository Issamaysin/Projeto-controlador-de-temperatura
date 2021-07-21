/* ***************************************************************** */
/* File name:        lcd.h                                           */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for handling the LCD hardware from   */
/*                   the hardware kit                                */
/* Author name:      Grupo 18 - Renato Pepe                          */
/*                              João Victor Matoso                   */
/* Creation date:    12apr2021                                       */
/* Revision date:    14apr2021                                       */
/* ***************************************************************** */

#ifndef SOURCES_LCD_H_
#define SOURCES_LCD_H_

/* lcd basic commands list */
#define CMD_INIT_LCD        0x0F
#define CMD_CLEAR           0x01
#define CMD_NO_CURSOR       0x0C
#define CMD_CURSOR2R        0x06 /* cursor to right */
#define CMD_NO_CUR_NO_BLINK 0x38 /* no cursor, no blink */


/* ************************************************ */
/* Method name:        lcd_initLcd                  */
/* Method description: Initialize the LCD function  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_initLcd(void);

/* ************************************************* */
/* Method name:        lcd_write2Lcd                 */
/* Method description: Send command or data to LCD   */
/* Input params:       ucBuffer => char to be send   */
/*                     ucDataType=>command LCD_RS_CMD*/
/*                     or data LCD_RS_DATA           */
/* Output params:      n/a                           */
/* ************************************************* */
void lcd_write2Lcd(unsigned char ucBuffer,  unsigned char ucDataType);


/* ************************************************ */
/* Method name:        lcd_writeData                */
/* Method description: Write data to be displayed   */
/* Input params:       ucData => char to be written */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_writeData(unsigned char ucData);


/* ************************************************ */
/* Method name:        lcd_sendCommand              */
/* Method description: Write command to LCD         */
/* Input params:       ucCmd=>command to be executed*/
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_sendCommand(unsigned char ucCmd);

/* ************************************************* */
/* Method name:        lcd_setCursor                 */
/* Method description: Set cursor line and column    */
/* Input params:       ucLine = LINE0..LINE1         */
/*                     ucColumn = COLUMN0..MAX_COLUMN*/
/* Output params:      n/a                           */
/* ************************************************* */
void lcd_setCursor(unsigned char ucLine, unsigned char ucColumn);

/* ************************************************ */
/* Method name:        lcd_WriteString              */
/* Method description: Write string to be displayed */
/* Input params:       cBuffer => string to be      */
/*                     written in LCD               */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_writeString(const char *cBuffer);


/* ************************************************ */
/* Method name:        lcd_dummyText                */
/* Method description: Write a dummy hard coded text*/
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_dummyText(void);

/* ********************************************************** */
/* Method name:        lcd_writeText                          */
/* Method description: Writes the given text into             */
/*                      the given line on the LCD             */
/* Input params:       ucLine => which line will be written   */
/*                     cText => text that will be written     */
/* Output params:      n/a                                    */
/* ********************************************************** */
void lcd_writeText(unsigned char ucLine, char *cText);


/* *************************************************************** */
/* Method name:        setGlobalString                             */
/* Method description: Write the input string cBuffer              */
/*                     into the global string cLCDText             */
/* Input params:       cBuffer => string to be written             */
/*                     ucLineNumber => which line is being written */
/* Output params:      n/a                                         */
/* *************************************************************** */
void setGlobalString(const char *cBuffer, unsigned char ucLineNumber);


#endif /* SOURCES_LCD_H_ */
