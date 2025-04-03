/*H*****************************************************************************
* FILENAME : config.c
*
* DESCRIPTION : Microrontroller PIC32MX370F512L configuration file for
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

#include <xc.h>
#include <sys/attribs.h>
#include <string.h>
#include "config.h"


//Global variables

#pragma config JTAGEN = OFF     
#pragma config FWDTEN = OFF      


/* ------------------------------------------------------------ */
/*                      Configuration Bits                      */
/* ------------------------------------------------------------ */


// Device Config Bits in  DEVCFG1:  
#pragma config FNOSC =  FRCPLL
#pragma config FSOSCEN =    OFF
#pragma config POSCMOD =    XT
#pragma config OSCIOFNC =   ON
#pragma config FPBDIV =     DIV_2

// Device Config Bits in  DEVCFG2:  
#pragma config FPLLIDIV =   DIV_2
#pragma config FPLLMUL =    MUL_20
#pragma config FPLLODIV =   DIV_1

const unsigned char digitSegments[]= {
    0b1000000, // 0
    0b1111111, // 1
    0b0100100, // 2
    0b0110000, // 3
    0b0011001, // 4
    0b0010010, // 5
    0b1111111, // 6
    0b1111000, // 7
    0b0000000, // 8
    0b0010000, // 9
    0b0001000, // A
    0b0000011, // b
    0b1111111, // C
    0b0100001, // d
    0b0000110, // E
    0b0001110,  // F
    0b1111111,   // ALL OFF
    0b0111111,  // -
    0b0000000,  // ALL ON
    0b0001001,  // H
    0b1000111,  // L
    0b0001100,  // P
    0b1001111,  // I
    0b1100011,  // U
    0b0101011   // N

    //  -0-
    // 5   1
    //  -6-       
    // 4   2
    //  -3-
    //6543210
    //
    //
};

volatile unsigned char bColR, bColG, bColB;


#define NO_DIGITS sizeof(digitSegments)/sizeof(digitSegments[0])
unsigned char digits[4];
#define TMR_TIME    0.003 // 3000 us for each tick

void init()
{
    LED_ConfigurePins();
    SWT_ConfigurePins();
    SSD_ConfigurePins();
    SSD_Timer1Setup();
    BTN_ConfigurePins();
    LCD_Init();
    AIC_Init();
    RGBLED_Init();
}

void LED_ConfigurePins()
{
    // Configure LEDs as digital outputs.
    tris_LEDS_GRP &= ~msk_LEDS_GRP;
}

void LED_SetGroupValue(unsigned char bVal)
{
    unsigned char *pLedData = (unsigned char *)lat_LEDS_GRP_ADDR;
    *pLedData = bVal;    
}

unsigned char SWT_GetValue(unsigned char bNo)
{
    unsigned bResult = 0xFF;

    switch (bNo)
    {
        case 0: 
            bResult = SW0;
            break;
        case 1: 
            bResult = SW1;
            break;
        case 2: 
            bResult = SW2;
            break;
        case 3: 
            bResult = SW3;
            break;
        case 4: 
            bResult = SW4;
            break;
        case 5: 
            bResult = SW5;
            break;
        case 6: 
            bResult = SW6;
            break;
        case 7: 
            bResult = SW7;
            break;
    }

    return bResult;
}

void SWT_ConfigurePins()
{
    // Configure SWTs as digital inputs.
    tris_SWT_SWT0 = 1;
    tris_SWT_SWT1 = 1;
    tris_SWT_SWT2 = 1;
    tris_SWT_SWT3 = 1;
    tris_SWT_SWT4 = 1;
    tris_SWT_SWT5 = 1;
    tris_SWT_SWT6 = 1;
    tris_SWT_SWT7 = 1;

    // disable analog (set pins as digital))
    ansel_SWT_SWT5 = 0;
    ansel_SWT_SWT6 = 0;
    ansel_SWT_SWT7 = 0;    
}

unsigned char SWT_GetGroupValue()
{
    int i;
    unsigned char bResult = 0;
    for(i = 0; i < 8; i++)
    {
        if(SWT_GetValue(i))
        {
            bResult |= (1 << i);
        }
    }
    return bResult;
}

void __ISR(_TIMER_1_VECTOR, IPL7AUTO) Timer1ISR(void) 
{  
    static unsigned char idxCurrDigit = 0;
    unsigned char currDigit, idx;

    idx = (idxCurrDigit++) & 3;
    currDigit = digits[idx];
//     1. deactivate all digits (anodes)
    lat_SSD_AN1 = 1; // deactivate digit 1;
    lat_SSD_AN2 = 1; // deactivate digit 2;    
    lat_SSD_AN3 = 1; // deactivate digit 3;   
    lat_SSD_AN0 = 1; // deactivate digit 0;
    
    // 2. drive all the segments (cathodes)
    lat_SSD_CA = currDigit & 0x01;
    lat_SSD_CB = (currDigit & 0x02) >> 1;
    lat_SSD_CC = (currDigit & 0x04) >> 2;
    lat_SSD_CD = (currDigit & 0x08) >> 3;    
    lat_SSD_CE = (currDigit & 0x10) >> 4;
    lat_SSD_CF = (currDigit & 0x20) >> 5;
    lat_SSD_CG = (currDigit & 0x40) >> 6;
    lat_SSD_DP = (currDigit & 0x80) >> 7;     
    
    // 3. activate the current digit (anodes)
    
    switch(idx)
    {
        case 0:
            lat_SSD_AN0 = 0; // activate digit 0;        
            break;
        case 1:
           lat_SSD_AN1 = 0; // activate digit 1;
            break;
        case 2:
           lat_SSD_AN2 = 0; // activate digit 2;
            break;    
        case 3:
            lat_SSD_AN3 = 0; // activate digit 3;   
            break; 
    }    
    IFS0bits.T1IF = 0;       // clear interrupt flag
}

void BTN_ConfigurePins()
{
    // Configure BTNs as digital inputs.
    tris_BTN_BTNU = 1;
    tris_BTN_BTNL = 1;
    tris_BTN_BTNC = 1;
    tris_BTN_BTNR = 1;
    tris_BTN_BTND = 1;

    // disable analog (set pins as digital))
    ansel_BTN_BTNU = 0;
    ansel_BTN_BTNL = 0;
    ansel_BTN_BTNR = 0;
}

void SSD_Timer1Setup()
{
  PR1 = (int)(((float)(TMR_TIME * PB_FRQ) / 256) + 0.5); //set period register, generates one interrupt every 3 ms
  TMR1 = 0;                           //    initialize count to 0
  T1CONbits.TCKPS = 2;                //    1:64 prescale value
  T1CONbits.TGATE = 0;                //    not gated input (the default)
  T1CONbits.TCS = 0;                  //    PCBLK input (the default)
  T1CONbits.ON = 1;                   //    turn on Timer1
  IPC1bits.T1IP = 7;                  //    priority
  IPC1bits.T1IS = 3;                  //    subpriority
  IFS0bits.T1IF = 0;                  //    clear interrupt flag
  IEC0bits.T1IE = 1;                  //    enable interrupt
  macro_enable_interrupts();          //    enable interrupts at CPU
}

void SSD_ConfigurePins()
{
    // set pins as digital outputs.
    tris_SSD_CA = 0;
    tris_SSD_CB = 0;
    tris_SSD_CC = 0;
    tris_SSD_CD = 0;  
    tris_SSD_CE = 0;
    tris_SSD_CF = 0;
    tris_SSD_CG = 0;
    tris_SSD_DP = 0;  
    
    tris_SSD_AN0 = 0;
    tris_SSD_AN1 = 0;
    tris_SSD_AN2 = 0;
    tris_SSD_AN3 = 0;    
    
    // disable analog (set pins as digital))    
    ansel_SSD_AN0 = 0;
    ansel_SSD_AN1 = 0;
    
    PMCONbits.ON = 0;   // turn PM off
}

unsigned char SSD_GetDigitSegments(unsigned char d)
{
    unsigned char bResult = -1;
    if(d < NO_DIGITS)
    {
        bResult = digitSegments[d];
    }
    return bResult;
}


void SSD_WriteDigits(unsigned char d3, unsigned char d2, unsigned char d1, unsigned char d0, \
            unsigned char dp3, unsigned char dp2, unsigned char dp1, unsigned char dp0)
{
      T1CONbits.ON = 0;                   // turn off Timer1
    digits[0] = SSD_GetDigitSegments(d0);
    digits[1] = SSD_GetDigitSegments(d1);
    digits[2] = SSD_GetDigitSegments(d2);
    digits[3] = SSD_GetDigitSegments(d3);
    
    if(!dp3)
    {
        digits[3] |= 0x80;
    }
    if(!dp2)
    {
        digits[2] |= 0x80;
    }
    if(!dp1)
    {
        digits[1] |= 0x80;
    }
    if(!dp0)
    {
        digits[0] |= 0x80;
    }    
    T1CONbits.ON = 1;                   //  turn on Timer1
}

void SSD_Close()
{
    // stop the timer
    T1CONbits.ON = 0;// turn off Timer1
    // turn off digits
    lat_SSD_AN1 = 1; // deactivate digit 1;
    lat_SSD_AN2 = 1; // deactivate digit 2;    
    lat_SSD_AN3 = 1; // deactivate digit 3;   
    lat_SSD_AN0 = 1; // deactivate digit 0;
}

void DelayAprox10Us( unsigned int  t100usDelay )
{
    int j;
    while ( 0 < t100usDelay )
    {
        t100usDelay--;
        j = 13;
        while ( 0 < j )
        {
            j--;
        }   // end while 
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
         
    }   // end while
}


// void DelayAprox1s(unsigned int sec)
// {
    // int i;
    // while(0 < sec)
    // {
        // sec--;
        // i=100;
        // while ( 0 < i)
        // {
            // DelayAprox10Us(i--);
        // }   // end while 
    // }
// }

void DelayForAproxSeconds(float n)
{
    DelayForAproxmSeconds((int)(n *1000));
}

void DelayForAproxmSeconds(int n)
{
    unsigned int i;
    i = n;
    while(0 < i)
    {
        i--;
        DelayAprox10Us(100);
    }
}


//WriteDigits(segmentID, number, point)
void WriteDigits(unsigned char id, unsigned char num, unsigned char point)
{
      T1CONbits.ON = 0;                   // turn off Timer1
    digits[id] = SSD_GetDigitSegments(num);

    if(!point)
    {
        digits[id] |= 0x80;
    }
  T1CONbits.ON = 1;                   //  turn on Timer1
}

void LCD_Init()
{
    LCD_ConfigurePins();
    LCD_InitSequence(displaySetOptionDisplayOn);
}

void LCD_ConfigurePins()
{
    // set control pins as digital outputs.
    tris_LCD_DISP_RS = 0;
    tris_LCD_DISP_RW = 0;
    tris_LCD_DISP_EN = 0;
    
    // disable analog (set pins as digital))
    ansel_LCD_DISP_RS = 0;
    
    // default (IO) function for remapable pins
    rp_LCD_DISP_RS = 0;
    rp_LCD_DISP_RW = 0;
    rp_LCD_DISP_EN = 0;
    
    // make data pins digital (disable analog)
    ansel_LCD_DB2 = 0;
    ansel_LCD_DB4 = 0;
    ansel_LCD_DB5 = 0;
    ansel_LCD_DB6 = 0;
    ansel_LCD_DB7 = 0;
}

void LCD_WriteByte(unsigned char bData)
{
    DelayAprox10Us(5);  
    // Configure IO Port data pins as output.
   tris_LCD_DATA &= ~msk_LCD_DATA;
    DelayAprox10Us(5);  
    // clear RW
    lat_LCD_DISP_RW = 0;

    // access data as contiguous 8 bits, using pointer to the LSB byte of LATE register
    unsigned char *pLCDData = (unsigned char *)(0xBF886430);
    *pLCDData = bData;

    DelayAprox10Us(10);   

    // Set En
    lat_LCD_DISP_EN = 1;    

    DelayAprox10Us(5);
    // Clear En
    lat_LCD_DISP_EN = 0;

    DelayAprox10Us(5);
    // Set RW
    lat_LCD_DISP_RW = 1;
}

unsigned char LCD_ReadByte()
{
    unsigned char bData;
    // Configure IO Port data pins as input.
    tris_LCD_DATA |= msk_LCD_DATA;
    // Set RW
    lat_LCD_DISP_RW = 1;

    // set RW
    lat_LCD_DISP_RW = 1;    
    
    // Set En
    lat_LCD_DISP_EN = 1;

    DelayAprox10Us(50);   

    // Clear En
    lat_LCD_DISP_EN = 0;
    bData = (unsigned char)(prt_LCD_DATA & (unsigned int)msk_LCD_DATA);
    return bData;
}

unsigned char LCD_ReadStatus()
{
    // Clear RS
    lat_LCD_DISP_RS = 0;
    
    unsigned char bStatus = LCD_ReadByte();
    return bStatus;
}

void LCD_WriteCommand(unsigned char bCmd)
{ 
    // Clear RS
    lat_LCD_DISP_RS = 0;

    // Write command byte
    LCD_WriteByte(bCmd);
}

void LCD_WriteDataByte(unsigned char bData)
{
    // Set RS 
    lat_LCD_DISP_RS = 1;

    // Write data byte
    LCD_WriteByte(bData);
}

void LCD_InitSequence(unsigned char bDisplaySetOptions)
{
    //  wait 40 ms

    DelayAprox10Us(40000);
    // Function Set
    LCD_WriteCommand(cmdLcdFcnInit);
    // Wait ~100 us
    DelayAprox10Us(10);
    // Function Set
    LCD_WriteCommand(cmdLcdFcnInit);
    // Wait ~100 us
    DelayAprox10Us(10); // Display Set
    LCD_DisplaySet(bDisplaySetOptions);
    // Wait ~100 us
    DelayAprox10Us(10);
    // Display Clear
    LCD_DisplayClear();
    // Wait 1.52 ms
    DelayAprox10Us(160);
    // Entry mode set
    LCD_WriteCommand(cmdLcdEntryMode);
        // Wait 1.52 ms
    DelayAprox10Us(160);
}

void LCD_DisplaySet(unsigned char bDisplaySetOptions)
{
    LCD_WriteCommand(cmdLcdCtlInit | bDisplaySetOptions);
}

void LCD_DisplayClear()
{
    LCD_WriteCommand(cmdLcdClear);
}

void LCD_ReturnHome()
{
    LCD_WriteCommand(cmdLcdRetHome);
}

void LCD_DisplayShift(unsigned char fRight)
{
    unsigned char bCmd = cmdLcdDisplayShift | (fRight ? mskShiftRL: 0);
    LCD_WriteCommand(bCmd);
}

void LCD_CursorShift(unsigned char fRight)
{
    unsigned char bCmd = cmdLcdCursorShift | (fRight ? mskShiftRL: 0);
    LCD_WriteCommand(bCmd);
}

void LCD_WriteStringAtPos(char *szLn, unsigned char idxLine, unsigned char idxPos)
{
    // crop string to 0x27 chars
    int len = strlen(szLn);
    if(len > 0x27)
    {
        szLn[0x27] = 0; // trim the string so it contains 40 characters 
        len = 0x27;
    }

    // Set write position
    unsigned char bAddrOffset = (idxLine == 0 ? 0: 0x40) + idxPos;
    LCD_SetWriteDdramPosition(bAddrOffset);

    unsigned char bIdx = 0;
    while(bIdx < len)
    {
        LCD_WriteDataByte(szLn[bIdx]);
        bIdx++;
    }
}

void LCD_SetCursorPosition(unsigned char idxLine, unsigned char idxPos){
    LCD_SetWriteDdramPosition((idxLine == 0 ? 0: 0x40) + idxPos);
}

void LCD_SetWriteCgramPosition(unsigned char bAdr)
{
    unsigned char bCmd = cmdLcdSetCgramPos | bAdr;
    LCD_WriteCommand(bCmd);
}

void LCD_WriteBytesAtPosCgram(unsigned char *pBytes, unsigned char len, unsigned char bAdr)
{
    // Set write position
    LCD_SetWriteCgramPosition(bAdr);

    // Write the string of bytes that define the character to CGRAM
    unsigned char idx = 0;
    while(idx < len)
    {
        LCD_WriteDataByte(pBytes[idx]);
        idx++;
    }
}

void AIC_Init()
{
    AIC_ConfigurePins();
    ADC_Init();
}

void AIC_ConfigurePins()
{
    // Configure AIC signal as analog input
    tris_ADC_AN2 = 1;     // set AN2 (RB2) as analog input pin 
    ansel_ADC_AN2 = 1;   // enable analog (set pins as analog)
}


void ADC_Init()
{

    AD1CON1 =   0; 
    AD1CON1bits.SSRC = 7;   // Internal counter ends sampling and starts conversion (auto convert)
    AD1CON1bits.FORM = 0;   // Integer 16-bit
    // Setup for manual sampling
    AD1CSSL =   0;
    AD1CON3 =   0x0002;     // ADC Conversion Clock Select bits: TAD = 6 TPB
    AD1CON2 =   0;
    AD1CON2bits.VCFG = 0;   // Voltage Reference Configuration bits: VREFH = AVDD and VREFL = AVSS
    // Turn on ADC
    AD1CON1bits.ON = 1;
} 

unsigned int ADC_AnalogRead()
{
    int adc_val = 0;
    unsigned char analogPIN = 2;
    
    IEC0bits.T2IE = 0;
    AD1CHS = analogPIN << 16;       // AD1CHS<16:19> controls which analog pin goes to the ADC
 
    AD1CON1bits.SAMP = 1;           // Begin sampling
    while( AD1CON1bits.SAMP );      // wait until acquisition is done
    while( ! AD1CON1bits.DONE );    // wait until conversion is done
 
    adc_val = ADC1BUF0;
    IEC0bits.T2IE = 1;
    return adc_val/4;
}

void __ISR(_TIMER_5_VECTOR, ipl2) Timer5ISR(void) 
{  
   static unsigned short sAccR = 0, sAccG = 0, sAccB = 0;
    
    // add 8 bit color values over the accumulators
    sAccR += bColR;
    sAccG += bColG;
    sAccB += bColB;

    // take the 9'th bit (addition carry) as the PDM
    lat_LED8_R = (sAccR & 0x100) ? 1: 0;    
    lat_LED8_G = (sAccG & 0x100) ? 1: 0;
    lat_LED8_B = (sAccB & 0x100) ? 1: 0;
    
    // filter only 8 bits in the accumulator
    sAccR &= 0xFF;
    sAccG &= 0xFF;
    sAccB &= 0xFF;
    
    IFS0bits.T5IF = 0;     // clear interrupt flag
}

void RGBLED_Timer5Setup()
{
   PR5 = (int)(((float)(TMR_TIME * PB_FRQ) / 256) + 0.5);   //set period register, generates one interrupt every 300 us                     //             set period register, generates one interrupt every 300 us
  TMR5 = 0;                           //    initialize count to 0
  T5CONbits.TCKPS = 3;                //    1:256 prescaler value
  T5CONbits.TGATE = 0;                //    not gated input (the default)
  T5CONbits.TCS = 0;                  //    PCBLK input (the default)
  IPC5bits.T5IP = 2;                  //    INT step 4: priority
  IPC5bits.T5IS = 0;                  //    subpriority
  IFS0bits.T5IF = 0;                  //    clear interrupt flag
  IEC0bits.T5IE = 1;                  //    enable interrupt
  T5CONbits.ON = 1;                   //    turn on Timer5
  macro_enable_interrupts();          //    enable interrupts at CPU
}

void RGBLED_Init()
{
    RGBLED_ConfigurePins();
    RGBLED_Timer5Setup();
    lat_LED8_R = 0;
    lat_LED8_G = 0;
    lat_LED8_B = 0;
}

void RGBLED_ConfigurePins()
{
    // Configure RGBLEDs as digital outputs.

//    rp_LED8_R = 0x0B; // LED8_R RPD2 is OC3 - for PWM usage
    rp_LED8_R = 0;      // no remapable
    tris_LED8_R = 0;    // output
  
    //RPD12R 1011 = OC5
//   rp_LED8_G = 0x0B; // LED8_G RPD12 is OC5 - for PWM usage
    rp_LED8_G = 0;      // no remapable
    tris_LED8_G = 0;    // output
 
//    rp_LED8_B = 0x0B; // LED8_B RPD3 is OC4 - for PWM usage
    rp_LED8_B = 0;      // no remapable
    tris_LED8_B = 0;    // output
    
    // disable analog (set pins as digital))
    ansel_LED8_R = 0;
    ansel_LED8_B = 0;
}

void RGBLED_SetValue(unsigned char bValR, unsigned char bValG, unsigned char bValB)
{
    bColR = bValR;
    bColG = bValG;
    bColB = bValB;
}

void RGBLED_Close()
{
    // stop the timer
      T5CONbits.ON = 0;   // turn off Timer5
    // turn off colors
    lat_LED8_R = 0;
    lat_LED8_G = 0;
    lat_LED8_B = 0;
}