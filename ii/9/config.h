/*H*****************************************************************************
* FILENAME : config.c
*
* DESCRIPTION : Microrontroller PIC32MX370F512L header file for config.c
*               
*
* PUBLIC FUNCTIONS :
*               
*
* NOTES : 
*
* COPYRIGHT : Copyright 2018 Hardi Selg
*
*
* AUTHOR : Hardi Selg     CONTACT : hardi.selg@ati.ttu.ee
*
* START DATE : 06.11.2018
*
* CHANGES :
*
*
*H*/


#ifndef CONFIG_H
#define	CONFIG_H

#define PB_FRQ  40000000

#define macro_enable_interrupts() \
{  unsigned int val = 0;\
    asm volatile("mfc0 %0,$13":"=r"(val));  \
    val |= 0x00800000;  \
    asm volatile("mtc0 %0,$13" : "+r"(val)); \
    INTCONbits.MVEC = 1; \
__builtin_enable_interrupts(); }

#define macro_disable_interrupts __builtin_disable_interrupts()

//#define macro_enable_interrupts INTEnableSystemMultiVectoredInt()

void init();
void LED_ConfigurePins();
void LED_SetGroupValue(unsigned char bVal);

void SWT_ConfigurePins();
unsigned char SWT_GetValue(unsigned char bNo);
unsigned char SWT_GetGroupValue();

void BTN_ConfigurePins();

void SSD_ConfigurePins();
void SSD_Timer1Setup();
void SSD_WriteDigits(unsigned char d3, unsigned char d2, unsigned char d1, unsigned char d0, \
            unsigned char dp3, unsigned char dp2, unsigned char dp1, unsigned char dp0);
void WriteDigits(unsigned char id, unsigned char num, unsigned char point);
unsigned char SSD_GetDigitSegments(unsigned char d);

void DelayAprox10Us( unsigned int tusDelay );
void DelayForAproxmSeconds(int msec);
void DelayForAproxSeconds(float sec);
// void DelayAprox1s(unsigned int sec);

#define cmdLcdFcnInit 	0x3C        // function set command, (8-bit interface, 2 lines, and 5x8 dots)
#define cmdLcdCtlInit 	0x0C        // display control set command
#define cmdLcdEntryMode 0x06        // Entry Mode Set
#define cmdLcdClear		0x01		// clear display command
#define cmdLcdRetHome	0x02		// return home command
#define cmdLcdDisplayShift 0x18		// shift display command
#define cmdLcdCursorShift  0x10		// shift cursor command
#define cmdLcdSetDdramPos	0x80	// set DDRAM position command
#define cmdLcdSetCgramPos	0x40	// set CGRAM position command

#define mskBStatus 0x80             // bit busy 
#define mskShiftRL 0x04             // bit for direction 
#define displaySetOptionDisplayOn	0x4 // Set Display On option
#define	displaySetOptionCursorOn 	0x2 // Set Cursor On option
#define	displaySetBlinkOn 			0x1 // Set Blink On option


#define posCgramChar0 0		// position in CGRAM for character 0
#define posCgramChar1 8		// position in CGRAM for character 1
#define posCgramChar2 16	// position in CGRAM for character 2
#define posCgramChar3 24	// position in CGRAM for character 3
#define posCgramChar4 32	// position in CGRAM for character 4
#define posCgramChar5 40	// position in CGRAM for character 5
#define posCgramChar6 48	// position in CGRAM for character 6
#define posCgramChar7 56	// position in CGRAM for character 7

#define LCD_SetWriteDdramPosition(bAddr) LCD_WriteCommand(cmdLcdSetDdramPos | bAddr);

void LCD_Init();
void LCD_InitSequence(unsigned char bDisplaySetOptions);
void LCD_WriteStringAtPos(char *szLn, unsigned char idxLine, unsigned char bAdr);
void LCD_DisplaySet(unsigned char bDisplaySetOptions);
void LCD_DisplayClear();
void LCD_DisplayShift(unsigned char fRight);
void LCD_CursorShift(unsigned char fRight);
void LCD_ReturnHome();
void LCD_WriteBytesAtPosCgram(unsigned char *pBytes, unsigned char len, unsigned char bAdr);
void LCD_SetCursorPosition(unsigned char idxLine, unsigned char idxPos);

// private
unsigned char LCD_ReadByte();
unsigned char LCD_ReadStatus();
void LCD_WriteByte(unsigned char bData);
void LCD_SetWriteCgramPosition(unsigned char bAdr);
void LCD_WriteCommand(unsigned char bCmd);
void LCD_WriteDataByte(unsigned char bData);
void LCD_ConfigurePins();

void ADC_Init();
unsigned int ADC_AnalogRead();
void AIC_Init();
void AIC_ConfigurePins();

void RGBLED_Init();
void RGBLED_SetValue(unsigned char bValR, unsigned char bValG, unsigned char bValB);
void RGBLED_Close();

//private functions:
void RGBLED_ConfigurePins();
void RGBLED_Timer5Setup();

#define macro_disable_interrupts __builtin_disable_interrupts()
//#define macro_disable_interrupts INTDisableInterrupts()

#define SEGM0 0
#define SEGM1 1
#define SEGM2 2
#define SEGM3 3
#define TRUE 1
#define FALSE 0
#define DOT_ON 1
#define DOT_OFF 0

/*
#ifdef	__cplusplus
extern "C" {
#endif
*/
//LEDS
#define tris_LEDS_GRP   TRISA
#define  lat_LEDS_GRP   LATA
#define latinv_LEDS_GRP LATAINV
#define  BGRP   PORTA
#define  msk_LEDS_GRP   0xFF    
#define  lat_LEDS_GRP_ADDR   0xBF886030

#define  LED0  LATAbits.LATA0
#define  LED1  LATAbits.LATA1
#define  LED2  LATAbits.LATA2
#define  LED3  LATAbits.LATA3
#define  LED4  LATAbits.LATA4
#define  LED5  LATAbits.LATA5
#define  LED6  LATAbits.LATA6
#define  LED7  LATAbits.LATA7

// SWT

#define tris_SWT_SWT0   TRISFbits.TRISF3
#define  SW0		   	PORTFbits.RF3
        
#define tris_SWT_SWT1   TRISFbits.TRISF5
#define  SW1		   	PORTFbits.RF5

#define tris_SWT_SWT2   TRISFbits.TRISF4
#define  SW2		   	PORTFbits.RF4

#define tris_SWT_SWT3   TRISDbits.TRISD15
#define  SW3		   	PORTDbits.RD15

#define tris_SWT_SWT4   TRISDbits.TRISD14
#define  SW4		   	PORTDbits.RD14

#define tris_SWT_SWT5   TRISBbits.TRISB11
#define  SW5		   	PORTBbits.RB11
#define  ansel_SWT_SWT5 ANSELBbits.ANSB11

#define tris_SWT_SWT6   TRISBbits.TRISB10
#define  SW6		   	PORTBbits.RB10
#define  ansel_SWT_SWT6 ANSELBbits.ANSB10

#define tris_SWT_SWT7   TRISBbits.TRISB9
#define  SW7		   	PORTBbits.RB9
#define  ansel_SWT_SWT7 ANSELBbits.ANSB9

 // Buttons
#define tris_BTN_BTNU   TRISBbits.TRISB1
#define  BTNU    PORTBbits.RB1
#define ansel_BTN_BTNU  ANSELBbits.ANSB1

#define tris_BTN_BTNL   TRISBbits.TRISB0
#define  BTNL    PORTBbits.RB0
#define ansel_BTN_BTNL  ANSELBbits.ANSB0

#define tris_BTN_BTNC   TRISFbits.TRISF0
#define  BTNC    PORTFbits.RF0

#define tris_BTN_BTNR   TRISBbits.TRISB8
#define  BTNR    PORTBbits.RB8
#define ansel_BTN_BTNR  ANSELBbits.ANSB8

#define tris_BTN_BTND   TRISAbits.TRISA15
#define  BTND   PORTAbits.RA15

 // SSD - Seven Segment Display

// Cathods
#define tris_SSD_CA     TRISGbits.TRISG12
#define  lat_SSD_CA     LATGbits.LATG12

#define tris_SSD_CB     TRISAbits.TRISA14
#define  lat_SSD_CB     LATAbits.LATA14

#define tris_SSD_CC     TRISDbits.TRISD6
#define  lat_SSD_CC     LATDbits.LATD6

#define tris_SSD_CD    TRISGbits.TRISG13
#define  lat_SSD_CD     LATGbits.LATG13

#define tris_SSD_CE     TRISGbits.TRISG15
#define  lat_SSD_CE     LATGbits.LATG15

#define tris_SSD_CF     TRISDbits.TRISD7
#define  lat_SSD_CF     LATDbits.LATD7

#define tris_SSD_CG     TRISDbits.TRISD13
#define  lat_SSD_CG     LATDbits.LATD13

#define tris_SSD_DP     TRISGbits.TRISG14
#define  lat_SSD_DP     LATGbits.LATG14

// Anods
#define tris_SSD_AN0     TRISBbits.TRISB12
#define lat_SSD_AN0      LATBbits.LATB12
#define msk_SSD_AN0      1<<12
#define ansel_SSD_AN0    ANSELBbits.ANSB12

#define tris_SSD_AN1     TRISBbits.TRISB13
#define lat_SSD_AN1      LATBbits.LATB13
#define msk_SSD_AN1      1<<13
#define ansel_SSD_AN1    ANSELBbits.ANSB13

#define tris_SSD_AN2     TRISAbits.TRISA9
#define lat_SSD_AN2      LATAbits.LATA9
#define msk_SSD_AN2      1<<9


#define tris_SSD_AN3     TRISAbits.TRISA10
#define lat_SSD_AN3      LATAbits.LATA10
#define msk_SSD_AN3      1<<10

#define lat_SSD_AN23     LATA
#define msk_SSD_AN23     (msk_SSD_AN2 | msk_SSD_AN3)
#define BN23     		 PORTA

#define lat_SSD_AN01     LATB
#define msk_SSD_AN01     (msk_SSD_AN0 | msk_SSD_AN1)
#define BN01     		 PORTB
// LCD

#define tris_LCD_DISP_RS    TRISBbits.TRISB15
#define lat_LCD_DISP_RS     LATBbits.LATB15
#define ansel_LCD_DISP_RS   ANSELBbits.ANSB15
#define rp_LCD_DISP_RS      RPB15R


#define tris_LCD_DISP_RW    TRISDbits.TRISD5
#define  lat_LCD_DISP_RW    LATDbits.LATD5
#define rp_LCD_DISP_RW      RPD5R

#define tris_LCD_DISP_EN    TRISDbits.TRISD4
#define  lat_LCD_DISP_EN    LATDbits.LATD4
#define rp_LCD_DISP_EN      RPD4R

#define tris_LCD_DATA       TRISE
#define lat_LCD_DATA        LATE
#define prt_LCD_DATA   		PORTE
#define msk_LCD_DATA        0xFF
#define ansel_LCD_DB2        ANSELEbits.ANSE2
#define ansel_LCD_DB4        ANSELEbits.ANSE4
#define ansel_LCD_DB5        ANSELEbits.ANSE5
#define ansel_LCD_DB6        ANSELEbits.ANSE6
#define ansel_LCD_DB7        ANSELEbits.ANSE7


// RGBLED
#define tris_LED8_R         TRISDbits.TRISD2
#define rp_LED8_R           RPD2R
#define lat_LED8_R          LATDbits.LATD2
#define ansel_LED8_R        ANSELDbits.ANSD2

#define tris_LED8_G         TRISDbits.TRISD12
#define rp_LED8_G           RPD12R
#define lat_LED8_G          LATDbits.LATD12


#define tris_LED8_B         TRISDbits.TRISD3
#define rp_LED8_B           RPD3R
#define lat_LED8_B          LATDbits.LATD3
#define ansel_LED8_B        ANSELDbits.ANSD3

// Analog input AN2
#define tris_ADC_AN2    TRISBbits.TRISB2
#define ansel_ADC_AN2   ANSELBbits.ANSB2

#endif  /* CONFIG_H */