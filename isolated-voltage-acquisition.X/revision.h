/*
    (c) 2022 Microchip Technology Inc. and its subsidiaries. You may use this
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

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef REVISION_H
#define	REVISION_H

#define MAJOR           '1'
#define MINOR           '0'
#define PATCH           '0'
#define BIDIRECTIONAL   '0'

//------------------------------------------------------------------------------
// revision history
//------------------------------------------------------------------------------
// 1.0.0
// 11.Oct.2022
// - un-directional optos only. 
// - measure offset at startup only 1000 times, filter and store
// - normal operation, measure the 3 phase voltages only

// 0.2.0
// 11.Oct.2022
// - measure offset at startup only 1000 times, accumulate and compute real average
// - only measure phase voltages if offset is within +/-5% of real value
//
// 0.1.0
// 10.Nov.2022
// - renamed tmr1_isr.c to isr.c
// - added additional revision specifier to differentiate between bi-directional and uni-directional code
// - code supports both uni and bi-directional operation by changing BIDIRECTIONAL to either '0' or '1'
//
#endif	/* REVISION_H */

