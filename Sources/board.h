/* ***************************************************************** */
/* File name:        board.h                                         */
/* File description: Header file containing the peripherals mapping  */
/*                     of the peripheral board for the ES670 hardware*/
/*                                                                   */
/* Author name:     Grupo 18 - Renato Pepe                           */
/*                              João Victor Matoso                   */
/* Creation date:    26fev2020                                       */
/* Revision date:    20may2020                                       */
/* ***************************************************************** */

#ifndef SOURCES_BOARD_H_
#define SOURCES_BOARD_H_

/* system includes */
#include <MKL25Z4.h>

/* FDRMKL25Z RGB LED pins defintions */
#define RED_LED_PORT_BASE_PNT    PORTB /* peripheral port base pointer */
#define RED_LED_GPIO_BASE_PNT    PTB   /* peripheral gpio base pointer */
#define RED_LED_PIN              (uint32_t) 18u
#define GREEN_LED_PORT_BASE_PNT  PORTB /* peripheral port base pointer */
#define GREEN_LED_GPIO_BASE_PNT  PTB   /* peripheral gpio base pointer */
#define GREEN_LED_PIN            (uint32_t) 19u
#define BLUE_LED_PORT_BASE_PNT   PORTD /* peripheral port base pointer */
#define BLUE_LED_GPIO_BASE_PNT   PTD   /* peripheral gpio base pointer */
#define BLUE_LED_PIN             (uint32_t) 1u


/********** McLab2 pin definitions **********/
/* Port definitions */
#define FRDM_PORTA    0X200

/* GPIO Port Data Register bits */
#define LEDSWITCH_1_GPIO_PDDR    0X02
#define LEDSWITCH_2_GPIO_PDDR    0X04
#define LEDSWITCH_3_GPIO_PDDR    0X10
#define LEDSWITCH_4_GPIO_PDDR    0X20


/* McLab2 clock ports */
#define SIM_CLOCK_PORTA 0x200
#define SIM_CLOCK_PORTE 0x2000


/*                 TEMPERATURE SENSOR DIODE DEFINITIONS           */
#define  THERMOMETER_PORT_BASE_PNT  PORTE                         /* peripheral port base pointer */
#define  THERMOMETER_GPIO_BASE_PNT  PTE                           /* peripheral gpio base pointer */
#define  THERMOMETER_PIN            21U                           /* thermometer pin */
#define  THERMOMETER_DIR            (GPIO_INPUT << TERMOMETER_PIN)
#define  THERMOMETER_ALT            0x00u
/*                 END OF TEMPERATURE SENSOR DIODE DEFINITIONS    */


/*                 General uC definitions                 */

/* Clock gate control */
#define  CGC_CLOCK_DISABLED         0x00u
#define  CGC_CLOCK_ENABLED          0x01u

/* GPIO input / output */
#define GPIO_INPUT                  0x00u
#define GPIO_OUTPUT                 0x01u


/*                 LCD definitions                 */

/* LCD Register Selector
 * Used as register selector input
 * When (LCD_RS = LCD_RS_HIGH) => DATA register is selected
 * When (LCD_RS = LCD_RS_LOW)  => INSTRUCTION register is selected
*/
#define LCD_PORT_BASE_PNT           PORTC                                   /* peripheral port base pointer */
#define LCD_GPIO_BASE_PNT           PTC                                     /* peripheral gpio base pointer */

#define LCD_RS_PIN                  8u                                      /* register selector */
#define LCD_RS_DIR                  kGpioDigitalOutput
#define LCD_RS_ALT                  kPortMuxAsGpio

#define LCD_ENABLE_PIN              9u                                      /* enable pin */
#define LCD_ENABLE_DIR              kGpioDigitalOutput
#define LCD_ENABLE_ALT              kPortMuxAsGpio

#define LCD_RS_HIGH                 1u
#define LCD_RS_DATA                 LCD_RS_HIGH

#define LCD_RS_LOW                  0u
#define LCD_RS_CMD                  LCD_RS_LOW

#define LCD_ENABLED                 1u
#define LCD_DISABLED                0u

#define LCD_DATA_DIR                kGpioDigitalOutput                      /* LCD data pins */
#define LCD_DATA_ALT                kPortMuxAsGpio

#define LCD_DATA_DB0_PIN            0u
#define LCD_DATA_DB1_PIN            1u
#define LCD_DATA_DB2_PIN            2u
#define LCD_DATA_DB3_PIN            3u
#define LCD_DATA_DB4_PIN            4u
#define LCD_DATA_DB5_PIN            5u
#define LCD_DATA_DB6_PIN            6u
#define LCD_DATA_DB7_PIN            7u

#define LCD_DATA_DB0_DIR            (GPIO_OUTPUT << LCD_DATA_DB0_PIN)
#define LCD_DATA_DB1_DIR            (GPIO_OUTPUT << LCD_DATA_DB1_PIN)
#define LCD_DATA_DB2_DIR            (GPIO_OUTPUT << LCD_DATA_DB2_PIN)
#define LCD_DATA_DB3_DIR            (GPIO_OUTPUT << LCD_DATA_DB3_PIN)
#define LCD_DATA_DB4_DIR            (GPIO_OUTPUT << LCD_DATA_DB4_PIN)
#define LCD_DATA_DB5_DIR            (GPIO_OUTPUT << LCD_DATA_DB5_PIN)
#define LCD_DATA_DB6_DIR            (GPIO_OUTPUT << LCD_DATA_DB6_PIN)
#define LCD_DATA_DB7_DIR            (GPIO_OUTPUT << LCD_DATA_DB7_PIN)
/*                 END OF LCD definitions                 */




#endif /* SOURCES_BOARD_H_ */
