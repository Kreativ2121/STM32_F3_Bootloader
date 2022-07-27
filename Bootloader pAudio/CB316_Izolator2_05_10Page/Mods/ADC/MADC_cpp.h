#ifndef __MADC_BH704_CPP_H
#define __MADC_BH704_CPP_H

#include "MADC.h"

/*########################################################################################*/

//-----------------------------------------------------------------------------
void MADC::init(){


}//----------------------------------------------------------------------------


  
//-----------------------------------------------------------------------------
  /// wywolywane po   __enable_irq();
void MADC::initIRQ(){

   HAL_ADC_Start_DMA( &hadc2, (uint32_t*)gADC2_Tab, 3 );
   HAL_ADC_Start_DMA( &hadc1, (uint32_t*)gADC1_Tab, 2 );
 
}//----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void  MADC::onTimer( ){
  


}//----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void  MADC::onSample_ADC1(){

  
  
  
      mIA = gADC1_Tab[0]; // IA
      mIB = gADC1_Tab[1]; // IB
    
      // ... IA .......................
      {
          mIA_iir += mIA;
          mIA_avr = mIA_iir / 2048;
          mIA_iir -= mIA_avr; //adcValueAvr[1] / 2048;

          
          int16_t abs = ( mIA - mIA_avr );
          if( abs < 0 ) abs =  - abs;
              
          gADC.mIAabs_iir += abs;
          mIAabs_avr = gADC.mIAabs_iir / 64;
          gADC.mIAabs_iir -= mIAabs_avr; 
  
      }
  
      // ... IB .......................
      {
          mIB_iir += mIB;
          mIB_avr = mIB_iir / 2048;
          mIB_iir -= mIB_avr; //adcValueAvr[1] / 2048;
          
          int16_t abs = ( mIB - mIB_avr );
          if( abs < 0 ) abs =  - abs;
              
          gADC.mIBabs_iir += abs;
          mIBabs_avr = gADC.mIBabs_iir / 64;
          gADC.mIBabs_iir -= mIBabs_avr; 
  
          
      }
  
  
   /*   
    // gADC.adcValue[1] = gADC1_Tab[0]; // UA
     gADC.adcValue[1] = Joystick2[1]; // UB
     //gADC.adcValue[1] = Joystick2[1]; // UB
    
      gADC.adcValueAvr[1] += gADC.adcValue[1];
      int16_t avr = gADC.adcValueAvr[1] / 2048;
      gADC.adcValueAvr[1] -= avr; //adcValueAvr[1] / 2048;
    
      // ITM_EVENT16( 1, gADC.adcValue[1] );
      */
      
      
   //   ITM_EVENT16( 1, Joystick2[0] );  // UA
  //  ITM_EVENT16( 2, Joystick2[1] );

}//----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void  MADC::onSample_ADC2(){
    
      mUA = gADC2_Tab[0]; // UA
      mUB = gADC2_Tab[1]; // UB
      mS0 = gADC2_Tab[2]; // USense
        
        
      // ... UA .......................
      mUA_iir += mUA;
      int16_t avrA = mUA_iir / 512;
      mUA_iir -= avrA; //adcValueAvr[1] / 2048;
      
      mUA_avr = avrA;
      
     // ... UB .......................
      mUB_iir += mUB;
      int16_t avrB = mUB_iir / 512;
      mUB_iir -= avrB; //adcValueAvr[1] / 2048;
      
      mUB_avr = avrB;
      
      
//      int16_t abs = (mUA-avr);
//      if( abs < 0 ) abs =  - abs;
      
      
//      gADC.adcValueAvr[2] += abs;
//      int16_t avr2 = gADC.adcValueAvr[2] / 512;
//      gADC.adcValueAvr[2] -= avr2; //adcValueAvr[1] / 2048;
      
      
      // ITM_EVENT16( 1, gADC.adcValue[1] );

}//----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/// nie wykorzystywane - stara wersja
void  MADC::setADC2_Channel( uint8_t aChNbr ){
        
          mCurADC2_Channel = aChNbr;
          uint32_t channel = ADC_CHANNEL_1;
          
               if( aChNbr == 1)  channel = ADC_CHANNEL_1;
          else if( aChNbr == 2)  channel = ADC_CHANNEL_2;
          else if( aChNbr == 3)  channel = ADC_CHANNEL_3;
          else if( aChNbr == 4)  channel = ADC_CHANNEL_4;
          else if( aChNbr == 5)  channel = ADC_CHANNEL_5;
          else if( aChNbr == 6)  channel = ADC_CHANNEL_6;
          else if( aChNbr == 7)  channel = ADC_CHANNEL_7;
          else if( aChNbr == 8)  channel = ADC_CHANNEL_8;
          else if( aChNbr == 9)  channel = ADC_CHANNEL_9;
          else if( aChNbr == 10) channel = ADC_CHANNEL_10;
          else if( aChNbr == 11) channel = ADC_CHANNEL_11;
          else if( aChNbr == 12) channel = ADC_CHANNEL_12;
          else if( aChNbr == 13) channel = ADC_CHANNEL_13;
          else if( aChNbr == 14) channel = ADC_CHANNEL_14;
          else if( aChNbr == 15) channel = ADC_CHANNEL_15;
          
          
          ADC_ChannelConfTypeDef sConfig = {0};
          sConfig.Channel = channel;
          sConfig.Rank = ADC_REGULAR_RANK_1;
          sConfig.SingleDiff = ADC_SINGLE_ENDED;
          sConfig.SamplingTime = ADC_SAMPLETIME_4CYCLES_5;
          sConfig.OffsetNumber = ADC_OFFSET_NONE;
          sConfig.Offset = 0;
          if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
          {
            Error_Handler();
          }
          
}//----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/// nie wykorzystywane - stara wersja
void MADC::setADC1_Channel( uint8_t aChNbr ){
        
          mCurADC1_Channel = aChNbr;
          uint32_t channel = ADC_CHANNEL_1;
          
               if( aChNbr == 1)  channel = ADC_CHANNEL_1;
          else if( aChNbr == 2)  channel = ADC_CHANNEL_2;
          else if( aChNbr == 3)  channel = ADC_CHANNEL_3;
          else if( aChNbr == 4)  channel = ADC_CHANNEL_4;
          else if( aChNbr == 5)  channel = ADC_CHANNEL_5;
          else if( aChNbr == 6)  channel = ADC_CHANNEL_6;
          else if( aChNbr == 7)  channel = ADC_CHANNEL_7;
          else if( aChNbr == 8)  channel = ADC_CHANNEL_8;
          else if( aChNbr == 9)  channel = ADC_CHANNEL_9;
          else if( aChNbr == 10) channel = ADC_CHANNEL_10;
          else if( aChNbr == 11) channel = ADC_CHANNEL_11;
          else if( aChNbr == 12) channel = ADC_CHANNEL_12;
          else if( aChNbr == 13) channel = ADC_CHANNEL_13;
          else if( aChNbr == 14) channel = ADC_CHANNEL_14;
          else if( aChNbr == 15) channel = ADC_CHANNEL_15;
          
          
          ADC_ChannelConfTypeDef sConfig = {0};
          sConfig.Channel = channel;
          sConfig.Rank = ADC_REGULAR_RANK_1;
          sConfig.SingleDiff = ADC_SINGLE_ENDED;
          sConfig.SamplingTime = ADC_SAMPLETIME_4CYCLES_5;
          sConfig.OffsetNumber = ADC_OFFSET_NONE;
          sConfig.Offset = 0;
          if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
          {
            Error_Handler();
          }
          
}//----------------------------------------------------------------------------




#endif
/*########################################################################################*/