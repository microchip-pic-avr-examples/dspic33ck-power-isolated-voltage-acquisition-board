/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
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
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/watchdog.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/ext_int.h"
#include "isr.h"
#include "revision.h"

//------------------------------------------------------------------------------
// compile time protection
//------------------------------------------------------------------------------
#ifndef BIDIRECTIONAL
#error "BIDIRECTIONAL needs to be defined as '0' or '1' in revision.h"
#else
#if (BIDIRECTIONAL != '0') && (BIDIRECTIONAL != '1')
#error "BIDIRECTIONAL needs to be defined as '0' or '1' in revision.h"
#endif 
#endif // #ifndef BIDIRECTIONAL

//------------------------------------------------------------------------------
// main()
//------------------------------------------------------------------------------
// note: most of the source code is located in isr.c

int main(void)
{
  // initialize the device
  SYSTEM_Initialize();
  
  // set interrupt callback function. Project supports both uni-directional
  // and bi-directional isolated voltage acqusition board hardware.
#if BIDIRECTIONAL == '0'     
  TMR1_SetInterruptHandler(&ISR_CallBack); // set timer 1 interrupt callback function 
  EX_INT1_InterruptDisable(); // disable external interrupt
#else
  IEC0bits.T1IE = false;      // disable timer 1 interrupt
#endif
  
  // enable watchdog timer. With MCC settings, should time out in around 2ms
  WATCHDOG_TimerSoftwareEnable();   

  while (1)
  {
    // clear watchdog timer
    WATCHDOG_TimerClear();
  }
  return 1;
}
/**
 End of File
 */

