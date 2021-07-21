/* ***************************************************************** */
/* File name:        lcd.c                                           */
/* File description: File dedicated to the hardware abstraction layer*/
/*                   related to the LCD HARDWARE based on the KS006U */
/*                   controller                                      */
/* Author name:      Grupo 18 - Renato Pepe                          */
/*                              João Victor Matoso                   */
/* Creation date:    12apr2021                                       */
/* Revision date:    14apr2021                                       */
/* ***************************************************************** */

#include "lcd.h"
#include "board.h"
#include "util.h"

/* system includes */
#include "fsl_clock_manager.h"
#include "fsl_port_hal.h"
#include "fsl_gpio_hal.h"

/* line and columns */
#define LINE0        0U
#define COLUMN0        0U

#define L0C0_BASE    0x80 /* line 0, column 0 */
#define L1C0_BASE    0xC0 /* line 1, column 0 */
#define MAX_COLUMN  15U


/* global */
/*
 * two global strings that stores the lines 1 and 2 texts
 * (so you don't lose the texts after writing on the LCD)
 */
char cLCDText[2][17];


/* ************************************************ */
/* Method name:        lcd_initLcd                  */
/* Method description: Initialize the LCD function  */
/* Input params:       n/a                          */
/* Output params:       n/a                         */
/* ************************************************ */
void lcd_initLcd(void)
{
    /* pins configured as outputs */

    /* un-gate port clock*/
    SIM_SCGC5 |= 0x1 << 11;

    /* set pin as gpio */
    /* register pin */
    PORTC_PCR8 |= 0x100;

    /* enable pin */
    PORTC_PCR9 |= 0x100;

    /* data/cmd pin */
    PORTC_PCR0 |= 0x100;
    PORTC_PCR1 |= 0x100;
    PORTC_PCR2 |= 0x100;
    PORTC_PCR3 |= 0x100;
    PORTC_PCR4 |= 0x100;
    PORTC_PCR5 |= 0x100;
    PORTC_PCR6 |= 0x100;
    PORTC_PCR7 |= 0x100;

    /* set pin as digital output */
    GPIOC_PDDR |= 0x1 << LCD_RS_PIN;
    GPIOC_PDDR |= 0x1 << LCD_ENABLE_PIN;
    GPIOC_PDDR |= 0x1 << LCD_DATA_DB0_PIN;
    GPIOC_PDDR |= 0x1 << LCD_DATA_DB1_PIN;
    GPIOC_PDDR |= 0x1 << LCD_DATA_DB2_PIN;
    GPIOC_PDDR |= 0x1 << LCD_DATA_DB3_PIN;
    GPIOC_PDDR |= 0x1 << LCD_DATA_DB4_PIN;
    GPIOC_PDDR |= 0x1 << LCD_DATA_DB5_PIN;
    GPIOC_PDDR |= 0x1 << LCD_DATA_DB6_PIN;
    GPIOC_PDDR |= 0x1 << LCD_DATA_DB7_PIN;

    /* turn-on LCD, with no cursor and no blink */
    lcd_sendCommand(CMD_NO_CUR_NO_BLINK);

    /* init LCD */
    lcd_sendCommand(CMD_INIT_LCD);

    /* clear LCD */
    lcd_sendCommand(CMD_CLEAR);

    /* LCD with no cursor */
    lcd_sendCommand(CMD_NO_CURSOR);

    /* cursor shift to right */
    lcd_sendCommand(CMD_CURSOR2R);

    /* init global variable */
    setGlobalString(" ", 0);
    setGlobalString(" ", 1);
}



/* ************************************************* */
/* Method name:        lcd_write2Lcd                 */
/* Method description: Send command or data to LCD   */
/* Input params:       ucBuffer => char to be send   */
/*                     ucDataType=>command LCD_RS_CMD*/
/*                     or data LCD_RS_DATA           */
/* Output params:      n/a                           */
/* ************************************************* */
void lcd_write2Lcd(unsigned char ucBuffer,  unsigned char ucDataType)
{
    /* writing data or command */
    if(LCD_RS_CMD == ucDataType)
        /* will send a command */
        GPIOC_PDOR &= ~(0x1 << LCD_RS_PIN);
    else
        /* will send data */
        GPIOC_PDOR |= 0x1 << LCD_RS_PIN;

    /* write in the LCD bus */
    GPIOC_PDOR = ((GPIOC_PDOR >> 8) << 8) | ucBuffer;

    /* enable, delay, disable LCD */
    /* this generates a pulse in the enable pin */
    GPIOC_PDOR |= 0x1 << LCD_ENABLE_PIN;
    util_genDelay1ms();
    GPIOC_PDOR &= ~(0x1 << LCD_ENABLE_PIN);
    util_genDelay1ms();
    util_genDelay1ms();
}



/* ************************************************ */
/* Method name:        lcd_writeData                */
/* Method description: Write data to be displayed   */
/* Input params:       ucData => char to be written */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_writeData(unsigned char ucData)
{
    /* just a relay to send data */
    lcd_write2Lcd(ucData, LCD_RS_DATA);
}



/* ************************************************ */
/* Method name:        lcd_sendCommand              */
/* Method description: Write command to LCD         */
/* Input params:       ucCmd=>command to be executed*/
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_sendCommand(unsigned char ucCmd)
{
    /* just a relay to send command */
    lcd_write2Lcd(ucCmd, LCD_RS_CMD);
}



/* ************************************************* */
/* Method name:        lcd_setCursor                 */
/* Method description: Set cursor line and column    */
/* Input params:       ucLine = LINE0..LINE1         */
/*                     ucColumn = COLUMN0..MAX_COLUMN*/
/* Output params:       n/a                          */
/* ************************************************* */
void lcd_setCursor(unsigned char ucLine, unsigned char ucColumn)
{
    char cCommand;

    if(LINE0 == ucLine)
        /* line 0 */
        cCommand = L0C0_BASE;
    else
        /* line 1 */
        cCommand = L1C0_BASE;

    /* maximum MAX_COLUMN columns */
    cCommand += (ucColumn & MAX_COLUMN);

    /* send the command to set the cursor */
    lcd_sendCommand(cCommand);
}



/* ************************************************ */
/* Method name:        lcd_writeString              */
/* Method description: Write string to be displayed */
/* Input params:       cBuffer => string to be      */
/*                     written in LCD               */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_writeString(const char *cBuffer)
{
    while(*cBuffer)
    {
        lcd_writeData(*cBuffer++);
    };
}


/* ************************************************ */
/* Method name:        lcd_dummyText                */
/* Method description: Write a dummy hard coded text*/
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_dummyText(void)
{
    /* clear LCD */
    lcd_sendCommand(CMD_CLEAR);

    /* set the cursor line 0, column 1 */
    lcd_setCursor(0,1);

    /* send string */
    lcd_writeString("*** ES670 ***");

    /* set the cursor line 1, column 0 */
    lcd_setCursor(1,0);
    lcd_writeString("Prj Sis Embarcad");
}

/* ********************************************************** */
/* Method name:        lcd_writeText                          */
/* Method description: Writes the given text into             */
/*                      the given line on the LCD             */
/* Input params:       ucLine => which line will be written   */
/*                     cText => text that will be written     */
/* Output params:      n/a                                    */
/* ********************************************************** */
void lcd_writeText(unsigned char ucLine, char *cText){
    /* clear LCD */
    lcd_sendCommand(CMD_CLEAR);

    /* Save string */
    setGlobalString(cText, ucLine);

    /* set the cursor */
    lcd_setCursor(0,0);

    /* Write text */
    lcd_writeString(cLCDText[0]);

    /* set the cursor */
    lcd_setCursor(1,0);

    /* Write text */
    lcd_writeString(cLCDText[1]);

    /*
     * obs: always writes the two lines (stored on the global strings)
     *      so the method can clear the LCD before writing anything,
     *      that way you can write only one line without erasing the other and
     *      don't get any residues from previous texts on the LCD
     *      (example: if you write "abcdefg" and then write "123" on the same line
     *       you'll get "123      " on the screen instead of "123defg" )
    */
}


/* *************************************************************** */
/* Method name:        setGlobalString                             */
/* Method description: Write the input string cBuffer              */
/*                     into the global string cLCDText             */
/* Input params:       cBuffer => string to be written             */
/*                     ucLineNumber => which line is being written */
/* Output params:      n/a                                         */
/* *************************************************************** */
void setGlobalString(const char *cBuffer, unsigned char ucLineNumber)
{
    /*
     * stores the given cBuffer string into the cLCDText global variable
     * so you can clear the screen without losing the information
    */
    int i = 0;
    while(*cBuffer && i < 16){
        cLCDText[ucLineNumber][i] = *(cBuffer++);
        i++;
    }
    cLCDText[ucLineNumber][i] = '\0';
}
