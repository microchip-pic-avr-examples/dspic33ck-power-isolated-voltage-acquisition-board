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

/**
  Section: Included Files
 */

#include <stdint.h>
#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "revision.h"

// symbolic references for ADC conversion channels
#define ADC_CHANNEL_VPHASE1       (0)
#define ADC_CHANNEL_VPHASE2       (9)
#define ADC_CHANNEL_VPHASE3       (4)
#define ADC_CHANNEL_VREF          (7) 

// 3 phase AC inputs from grid are scaled down with op amp circuits so they can be 
// digitized with 12-bit ADC on dsPIC. ADC input range is 0 to 3.3V. 3 signals on
// ADC input pins sit on a 1.65V bias, so that AC signals (that go negative) can
// be measured with the ADC, which cannot measure negative voltages. 
// So with 0V on AC input, we get 1.65V on ADC input pins
// This 1.65V reference can be measured on pin RB2
// 
// OPAMP_BIAS_IDEAL: ideal value of op amp bias in ADC codes
// ADC reference = 3.3V, 12-bit ADC so 4096 codes
#define OPAMP_BIAS_IDEAL            ((uint16_t)(1.65/3.3*4096)) // in ADC codes

// OPAMP_BIAS_HIGH_LIMIT and OPAMP_BIAS_LOW_LIMIT: measured op amp bias should be within 5% of ideal value
#define OPAMP_BIAS_HIGH_LIMIT       ((uint16_t)(OPAMP_BIAS_IDEAL*1.05)) // in ADC codes
#define OPAMP_BIAS_LOW_LIMIT        ((uint16_t)(OPAMP_BIAS_IDEAL*0.95)) // in ADC codes

//------------------------------------------------------------------------------
// variables with file scope
//------------------------------------------------------------------------------
// TransmitData: SPI transmit buffer 
static uint16_t TransmitData[5];

// vphase: ADC readings of 3 phase voltages
static uint16_t vphase[3]; // in ADC codes

// opamp_bias: op amp DC bias (with 0V @ input, ideally 1.65V @ output of each op-amp)
static uint16_t opamp_bias = 0; // in ADC codes

// For state machine, create state typedef and variable
typedef enum {
  STATE_OFFSET_MEAS = 0, STATE_ONLINE
} STATES;
static STATES state = STATE_OFFSET_MEAS;

//------------------------------------------------------------------------------
// function declarations 
//------------------------------------------------------------------------------
static void __attribute__((always_inline)) CreateSPIMessage(void);

/*******************************************************************************
 * @fn	ISR_CallBack()
 * @brief interrupt callback function
 * @param	None
 * @return None
 *  
 * @details
 * Called either by external interrupt handler or timer 1 interrupt handler
 * in revision.h, if BIDIRECTION = '0', called by timer 1 interrupt handler
 * in revision.h, if BIDIRECTION = '1', called by external interrupt handler
 * there is a small state machine which first measured the op amp DC bias
 * 1000 times and averages it. 
 * Then we move onto the 'online' state
 * here we measure the 3 voltages, pack the results in 4 16 bit words
 * with a checksum and transmit these 4 words over SPI (clk and data only, no cs)
 *********************************************************************************/
void ISR_CallBack(void) 
{
  switch (state)
  {
    case STATE_OFFSET_MEAS:
    {
      //------------------------------------------------------------------------
      // measure op amp bias
      //------------------------------------------------------------------------
      // CNVCHSEL should have already been initialized via MCC to ADC_CHANNEL_VREF
      // but just in case do it here also
      ADCON3Lbits.CNVCHSEL = ADC_CHANNEL_VREF;

      static uint16_t opamp_bias_meas_counter = 0; // counts ADC samples for computing average 
      static uint32_t accumulator = 0; // accumulate ADC readings of op-amp bias so average can be calculated
      ADCON3Lbits.CNVRTCH = 1; // trigger conversion

      while (!ADSTATLbits.AN7RDY)
      {
      }; // wait for conversion to complete             

      // update accumulator and counter
      accumulator += ADCBUF7;
      opamp_bias_meas_counter++;

      if (opamp_bias_meas_counter >= 1000) // 1000 * 10e-6 = 10ms    
      {
        // calculate average 
        opamp_bias = (uint16_t) __builtin_divud(accumulator, opamp_bias_meas_counter);

        // reset counter and accumulator
        opamp_bias_meas_counter = 0;
        accumulator = 0;

        // check if measured value is within limits
        if ((opamp_bias > OPAMP_BIAS_LOW_LIMIT) && (opamp_bias < OPAMP_BIAS_HIGH_LIMIT))
        {          
          // all is good, move onto normal state where sampling 3 phase voltages
          ADCON3Lbits.CNVCHSEL = ADC_CHANNEL_VPHASE1;

          LED_SetHigh();
          state = STATE_ONLINE;
        }
        else
        {
          // repeat measurement of op amp bias

        }
      }
      break;
    }

    case STATE_ONLINE:
    {
      //------------------------------------------------------------------------
      // measure 3 phase voltages
      //------------------------------------------------------------------------
      // phase 1
      ADCON3Lbits.CNVRTCH = 1; // trigger conversion
      while (!ADSTATLbits.AN0RDY)
      {
      }; // wait for conversion to complete
      ADCON3Lbits.CNVCHSEL = ADC_CHANNEL_VPHASE2; // change ADC channel
      vphase[0] = ADCBUF0; // store result

      // phase 2  
      ADCON3Lbits.CNVRTCH = 1; // trigger conversion
      while (!ADSTATLbits.AN9RDY)
      {
      }; // wait for conversion to complete  
      ADCON3Lbits.CNVCHSEL = ADC_CHANNEL_VPHASE3; // change ADC channel
      vphase[1] = ADCBUF9; // store result

      // phase 3 
      ADCON3Lbits.CNVRTCH = 1; // trigger conversion
      while (!ADSTATLbits.AN4RDY)
      {
      }; // wait for conversion to complete
      ADCON3Lbits.CNVCHSEL = ADC_CHANNEL_VPHASE1; // change ADC channel
      vphase[2] = ADCBUF4; // store result      

      break;
    }

    default:
    {
      ADCON3Lbits.CNVCHSEL = ADC_CHANNEL_VPHASE1; // set to sample phase 1
      state = STATE_ONLINE;
      break;
    }

  };

  //----------------------------------------------------------------------------
  // create and send SPI message
  //----------------------------------------------------------------------------
  // create the SPI message
  CreateSPIMessage();

  // send byteCount/2 words over SPI  
  uint16_t byteCount = 8;
  uint16_t dataSentCount;
  dataSentCount = SPI1_Exchange16bitBuffer((uint16_t *) & TransmitData[0], byteCount, NULL);
}

/*******************************************************************************
 * @fn	CreateSPIMessage()
 * @brief create SPI message
 * @param	None
 * @return None
 *  
 * @details
 * we want to send 4*12-bit words (ADC readings of 3 phase voltages + 
 * op amp bias) and also a checksum. 
 * vphase[0]: ADC reading of phase 1 voltage
 * vphase[1]: ADC reading of phase 2 voltage
 * vphase[2]: ADC reading of phase 3 voltage
 * opamp_bias: ADC reading of op amp bias voltage    
 * We can do this with 4*16 bit words
 * we pack these words as follows, and place the checksum in word 3
 * 
 * bit pos  |   word 0          |   word 1          | word 2            
 *--------------------------------------------------------------------------
 *  15      |   vphase[1]:3     |   vphase[2]:7     |   opamp_bias:11
 *  14      |   vphase[1]:2     |   vphase[2]:6     |   opamp_bias:10
 *  13      |   vphase[1]:1     |   vphase[2]:5     |   opamp_bias:9
 *  12      |   vphase[1]:0     |   vphase[2]:4     |   opamp_bias:8
 *  11      |   vphase[0]:11    |   vphase[2]:3     |   opamp_bias:7
 *  10      |   vphase[0]:10    |   vphase[2]:2     |   opamp_bias:6
 *  09      |   vphase[0]:9     |   vphase[2]:1     |   opamp_bias:5
 *  08      |   vphase[0]:8     |   vphase[2]:0     |   opamp_bias:4
 *  07      |   vphase[0]:7     |   vphase[1]:11    |   opamp_bias:3
 *  06      |   vphase[0]:6     |   vphase[1]:10    |   opamp_bias:2   
 *  05      |   vphase[0]:5     |   vphase[1]:9     |   opamp_bias:1
 *  04      |   vphase[0]:4     |   vphase[1]:8     |   opamp_bias:0
 *  03      |   vphase[0]:3     |   vphase[1]:7     |   vphase[2]:11
 *  02      |   vphase[0]:2     |   vphase[1]:6     |   vphase[2]:10
 *  01      |   vphase[0]:1     |   vphase[1]:5     |   vphase[2]:9
 *  00      |   vphase[0]:0     |   vphase[1]:4     |   vphase[2]:8  
 *********************************************************************************/
static void CreateSPIMessage(void)
{      
  TransmitData[0] = (vphase[0] & 0x0FFF) + ((vphase[1] & 0x000F) << 12);
  TransmitData[1] = ((vphase[1] & 0x0FF0) >> 4) + ((vphase[2] & 0x00FF) << 8);
  TransmitData[2] = ((vphase[2] & 0x0F00) >> 8) + (opamp_bias << 4);

  // calculate additive checksum as sum of words 0 to 3
  // transmit in word 4
  uint16_t i;

  // initialize to non zero value as if SPI data line is  
  // is disconnected a checksum of 0x00 may pass
  uint16_t checksum = 0x0055;
  for (i = 0; i < 3; i++)
  {
    checksum = checksum + TransmitData[i];
  }

  // place checksum in last word of SPI transmit buffer
  TransmitData[3] = checksum;
}

#if BIDIRECTIONAL == '1'
void EX_INT1_CallBack(void)
{
  ISR_CallBack();
}
#endif // #if BIDIRECTIONAL == '1'