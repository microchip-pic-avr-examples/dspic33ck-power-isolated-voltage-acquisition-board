/**
  ADC1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adc1.c

  @Summary
    This is the generated driver implementation file for the ADC1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for ADC1.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.2
        Device            :  dsPIC33CK32MC102      
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include "adc1.h"

/**
 Section: File specific functions
*/

static void (*ADC1_CommonDefaultInterruptHandler)(void);
static void (*ADC1_L1_senseDefaultInterruptHandler)(uint16_t adcVal);
static void (*ADC1_L3_senseDefaultInterruptHandler)(uint16_t adcVal);
static void (*ADC1_VREFDefaultInterruptHandler)(uint16_t adcVal);
static void (*ADC1_L2_senseDefaultInterruptHandler)(uint16_t adcVal);
static void (*ADC1_channel_AN16DefaultInterruptHandler)(uint16_t adcVal);
static void (*ADC1_channel_AN17DefaultInterruptHandler)(uint16_t adcVal);

/**
  Section: Driver Interface
*/

void ADC1_Initialize (void)
{
    // ADSIDL disabled; ADON enabled; 
    ADCON1L = (0x8000 & 0x7FFF); //Disabling ADON bit
    // FORM Integer; SHRRES 12-bit resolution; 
    ADCON1H = 0x60;
    // SHRADCS 2; REFCIE disabled; SHREISEL Early interrupt is generated 1 TADCORE clock prior to data being ready; REFERCIE disabled; EIEN disabled; 
    ADCON2L = 0x00;
    // SHRSAMC 0; 
    ADCON2H = 0x00;
    // SWCTRG disabled; SHRSAMP disabled; SUSPEND disabled; SWLCTRG disabled; SUSPCIE disabled; CNVCHSEL AN7; REFSEL disabled; 
    ADCON3L = 0x07;
    // SHREN enabled; CLKDIV 1; CLKSEL FOSC/2; 
    ADCON3H = (0x80 & 0xFF00); //Disabling C0EN, C1EN, C2EN, C3EN and SHREN bits
    // SIGN0 disabled; SIGN4 disabled; SIGN3 disabled; SIGN2 disabled; SIGN1 disabled; SIGN7 disabled; SIGN6 disabled; SIGN5 disabled; 
    ADMOD0L = 0x00;
    // SIGN10 disabled; SIGN11 disabled; SIGN8 disabled; SIGN9 disabled; 
    ADMOD0H = 0x00;
    // SIGN16 disabled; SIGN17 disabled; 
    ADMOD1L = 0x00;
    // IE1 disabled; IE0 disabled; IE3 disabled; IE2 disabled; IE5 disabled; IE4 disabled; IE10 disabled; IE7 disabled; IE6 disabled; IE9 disabled; IE8 disabled; IE11 disabled; 
    ADIEL = 0x00;
    // IE17 enabled; IE16 enabled; 
    ADIEH = 0x03;
    // CMPEN6 disabled; CMPEN10 disabled; CMPEN5 disabled; CMPEN11 disabled; CMPEN4 disabled; CMPEN3 disabled; CMPEN2 disabled; CMPEN1 disabled; CMPEN0 disabled; CMPEN9 disabled; CMPEN8 disabled; CMPEN7 disabled; 
    ADCMP0ENL = 0x00;
    // CMPEN6 disabled; CMPEN10 disabled; CMPEN5 disabled; CMPEN11 disabled; CMPEN4 disabled; CMPEN3 disabled; CMPEN2 disabled; CMPEN1 disabled; CMPEN0 disabled; CMPEN9 disabled; CMPEN8 disabled; CMPEN7 disabled; 
    ADCMP1ENL = 0x00;
    // CMPEN6 disabled; CMPEN10 disabled; CMPEN5 disabled; CMPEN11 disabled; CMPEN4 disabled; CMPEN3 disabled; CMPEN2 disabled; CMPEN1 disabled; CMPEN0 disabled; CMPEN9 disabled; CMPEN8 disabled; CMPEN7 disabled; 
    ADCMP2ENL = 0x00;
    // CMPEN6 disabled; CMPEN10 disabled; CMPEN5 disabled; CMPEN11 disabled; CMPEN4 disabled; CMPEN3 disabled; CMPEN2 disabled; CMPEN1 disabled; CMPEN0 disabled; CMPEN9 disabled; CMPEN8 disabled; CMPEN7 disabled; 
    ADCMP3ENL = 0x00;
    // CMPEN16 disabled; CMPEN17 disabled; 
    ADCMP0ENH = 0x00;
    // CMPEN16 disabled; CMPEN17 disabled; 
    ADCMP1ENH = 0x00;
    // CMPEN16 disabled; CMPEN17 disabled; 
    ADCMP2ENH = 0x00;
    // CMPEN16 disabled; CMPEN17 disabled; 
    ADCMP3ENH = 0x00;
    // CMPLO 0; 
    ADCMP0LO = 0x00;
    // CMPLO 0; 
    ADCMP1LO = 0x00;
    // CMPLO 0; 
    ADCMP2LO = 0x00;
    // CMPLO 0; 
    ADCMP3LO = 0x00;
    // CMPHI 0; 
    ADCMP0HI = 0x00;
    // CMPHI 0; 
    ADCMP1HI = 0x00;
    // CMPHI 0; 
    ADCMP2HI = 0x00;
    // CMPHI 0; 
    ADCMP3HI = 0x00;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL0CON = 0x400;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL1CON = 0x400;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL2CON = 0x400;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL3CON = 0x400;
    // HIHI disabled; LOLO disabled; HILO disabled; BTWN disabled; LOHI disabled; CMPEN disabled; IE disabled; 
    ADCMP0CON = 0x00;
    // HIHI disabled; LOLO disabled; HILO disabled; BTWN disabled; LOHI disabled; CMPEN disabled; IE disabled; 
    ADCMP1CON = 0x00;
    // HIHI disabled; LOLO disabled; HILO disabled; BTWN disabled; LOHI disabled; CMPEN disabled; IE disabled; 
    ADCMP2CON = 0x00;
    // HIHI disabled; LOLO disabled; HILO disabled; BTWN disabled; LOHI disabled; CMPEN disabled; IE disabled; 
    ADCMP3CON = 0x00;
    // LVLEN9 disabled; LVLEN8 disabled; LVLEN11 disabled; LVLEN7 disabled; LVLEN10 disabled; LVLEN6 disabled; LVLEN5 disabled; LVLEN4 disabled; LVLEN3 disabled; LVLEN2 disabled; LVLEN1 disabled; LVLEN0 disabled; 
    ADLVLTRGL = 0x00;
    // LVLEN17 disabled; LVLEN16 disabled; 
    ADLVLTRGH = 0x00;
    // EIEN9 disabled; EIEN7 disabled; EIEN8 disabled; EIEN5 disabled; EIEN6 disabled; EIEN3 disabled; EIEN4 disabled; EIEN1 disabled; EIEN2 disabled; EIEN0 disabled; EIEN11 disabled; EIEN10 disabled; 
    ADEIEL = 0x00;
    // EIEN17 disabled; EIEN16 disabled; 
    ADEIEH = 0x00;
    // SHRCIE disabled; WARMTIME 32768 Source Clock Periods; 
    ADCON5H = (0xF00 & 0xF0FF); //Disabling WARMTIME bit
	
    //Assign Default Callbacks
    ADC1_SetCommonInterruptHandler(&ADC1_CallBack);
    ADC1_SetL1_senseInterruptHandler(&ADC1_L1_sense_CallBack);
    ADC1_SetL3_senseInterruptHandler(&ADC1_L3_sense_CallBack);
    ADC1_SetVREFInterruptHandler(&ADC1_VREF_CallBack);
    ADC1_SetL2_senseInterruptHandler(&ADC1_L2_sense_CallBack);
    ADC1_Setchannel_AN16InterruptHandler(&ADC1_channel_AN16_CallBack);
    ADC1_Setchannel_AN17InterruptHandler(&ADC1_channel_AN17_CallBack);
    
    // Clearing channel_AN16 interrupt flag.
    IFS6bits.ADCAN16IF = 0;
    // Enabling channel_AN16 interrupt.
    IEC6bits.ADCAN16IE = 1;
    // Clearing channel_AN17 interrupt flag.
    IFS6bits.ADCAN17IF = 0;
    // Enabling channel_AN17 interrupt.
    IEC6bits.ADCAN17IE = 1;

    // Setting WARMTIME bit
    ADCON5Hbits.WARMTIME = 0xF;
    // Enabling ADC Module
    ADCON1Lbits.ADON = 0x1;
    // Enabling Power for the Shared Core
    ADC1_SharedCorePowerEnable();

    //TRGSRC0 Common Software Trigger; TRGSRC1 Common Software Trigger; 
    ADTRIG0L = 0x101;
    //TRGSRC3 None; TRGSRC2 None; 
    ADTRIG0H = 0x00;
    //TRGSRC4 Common Software Trigger; TRGSRC5 None; 
    ADTRIG1L = 0x01;
    //TRGSRC6 None; TRGSRC7 Common Software Trigger; 
    ADTRIG1H = 0x100;
    //TRGSRC8 None; TRGSRC9 Common Software Trigger; 
    ADTRIG2L = 0x100;
    //TRGSRC11 None; TRGSRC10 None; 
    ADTRIG2H = 0x00;
    //TRGSRC17 Common Software Trigger; TRGSRC16 Common Software Trigger; 
    ADTRIG4L = 0x101;
}

void ADC1_SharedCorePowerEnable ( ) 
{
    ADCON5Lbits.SHRPWR = 1;   
    while(ADCON5Lbits.SHRRDY == 0);
    ADCON3Hbits.SHREN = 1;   
}


void __attribute__ ((weak)) ADC1_CallBack ( void )
{ 

}

void ADC1_SetCommonInterruptHandler(void* handler)
{
    ADC1_CommonDefaultInterruptHandler = handler;
}

void __attribute__ ((weak)) ADC1_Tasks ( void )
{
    if(IFS5bits.ADCIF)
    {
        if(ADC1_CommonDefaultInterruptHandler) 
        { 
            ADC1_CommonDefaultInterruptHandler(); 
        }

        // clear the ADC1 interrupt flag
        IFS5bits.ADCIF = 0;
    }
}

void __attribute__ ((weak)) ADC1_L1_sense_CallBack( uint16_t adcVal )
{ 

}

void ADC1_SetL1_senseInterruptHandler(void* handler)
{
    ADC1_L1_senseDefaultInterruptHandler = handler;
}

void __attribute__ ((weak)) ADC1_L1_sense_Tasks ( void )
{
    uint16_t valL1_sense;

    if(ADSTATLbits.AN0RDY)
    {
        //Read the ADC value from the ADCBUF
        valL1_sense = ADCBUF0;

        if(ADC1_L1_senseDefaultInterruptHandler) 
        { 
            ADC1_L1_senseDefaultInterruptHandler(valL1_sense); 
        }
    }
}

void __attribute__ ((weak)) ADC1_L3_sense_CallBack( uint16_t adcVal )
{ 

}

void ADC1_SetL3_senseInterruptHandler(void* handler)
{
    ADC1_L3_senseDefaultInterruptHandler = handler;
}

void __attribute__ ((weak)) ADC1_L3_sense_Tasks ( void )
{
    uint16_t valL3_sense;

    if(ADSTATLbits.AN4RDY)
    {
        //Read the ADC value from the ADCBUF
        valL3_sense = ADCBUF4;

        if(ADC1_L3_senseDefaultInterruptHandler) 
        { 
            ADC1_L3_senseDefaultInterruptHandler(valL3_sense); 
        }
    }
}

void __attribute__ ((weak)) ADC1_VREF_CallBack( uint16_t adcVal )
{ 

}

void ADC1_SetVREFInterruptHandler(void* handler)
{
    ADC1_VREFDefaultInterruptHandler = handler;
}

void __attribute__ ((weak)) ADC1_VREF_Tasks ( void )
{
    uint16_t valVREF;

    if(ADSTATLbits.AN7RDY)
    {
        //Read the ADC value from the ADCBUF
        valVREF = ADCBUF7;

        if(ADC1_VREFDefaultInterruptHandler) 
        { 
            ADC1_VREFDefaultInterruptHandler(valVREF); 
        }
    }
}

void __attribute__ ((weak)) ADC1_L2_sense_CallBack( uint16_t adcVal )
{ 

}

void ADC1_SetL2_senseInterruptHandler(void* handler)
{
    ADC1_L2_senseDefaultInterruptHandler = handler;
}

void __attribute__ ((weak)) ADC1_L2_sense_Tasks ( void )
{
    uint16_t valL2_sense;

    if(ADSTATLbits.AN9RDY)
    {
        //Read the ADC value from the ADCBUF
        valL2_sense = ADCBUF9;

        if(ADC1_L2_senseDefaultInterruptHandler) 
        { 
            ADC1_L2_senseDefaultInterruptHandler(valL2_sense); 
        }
    }
}

void __attribute__ ((weak)) ADC1_channel_AN16_CallBack( uint16_t adcVal )
{ 

}

void ADC1_Setchannel_AN16InterruptHandler(void* handler)
{
    ADC1_channel_AN16DefaultInterruptHandler = handler;
}

void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _ADCAN16Interrupt ( void )
{
    uint16_t valchannel_AN16;
    //Read the ADC value from the ADCBUF
    valchannel_AN16 = ADCBUF16;

    if(ADC1_channel_AN16DefaultInterruptHandler) 
    { 
        ADC1_channel_AN16DefaultInterruptHandler(valchannel_AN16); 
    }

    //clear the channel_AN16 interrupt flag
    IFS6bits.ADCAN16IF = 0;
}

void __attribute__ ((weak)) ADC1_channel_AN17_CallBack( uint16_t adcVal )
{ 

}

void ADC1_Setchannel_AN17InterruptHandler(void* handler)
{
    ADC1_channel_AN17DefaultInterruptHandler = handler;
}

void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _ADCAN17Interrupt ( void )
{
    uint16_t valchannel_AN17;
    //Read the ADC value from the ADCBUF
    valchannel_AN17 = ADCBUF17;

    if(ADC1_channel_AN17DefaultInterruptHandler) 
    { 
        ADC1_channel_AN17DefaultInterruptHandler(valchannel_AN17); 
    }

    //clear the channel_AN17 interrupt flag
    IFS6bits.ADCAN17IF = 0;
}




/**
  End of File
*/
