#ifndef __MADC_BH704_CPP_H
#define __MADC_BH704_CPP_H


/*########################################################################################*/



//-----------------------------------------------------------------------------
void  MADC::onTimer( ){
  
    
  
  /*  gADC.gADC_State += 1;
    if( gADC.gADC_State >= 5 ) gADC.gADC_State = 0;
*/

    gADC.gADC_State = 1;
  
    switch( gADC.gADC_State ){
    case 0: { gADC.setADC2_Channel( 15 ); HAL_ADC_Start_IT(&hadc2); }; break;
    case 1: { gADC.setADC2_Channel(  2 ); HAL_ADC_Start_IT(&hadc2); }; break;
    case 2: { gADC.setADC2_Channel( 14 ); HAL_ADC_Start_IT(&hadc2); }; break;
    case 3: { gADC.setADC1_Channel( 11 ); HAL_ADC_Start_IT(&hadc1); }; break;
    case 4: { gADC.setADC1_Channel( 12 ); HAL_ADC_Start_IT(&hadc1); }; break;
    default: break;
    }

}//----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
void  MADC::onSample( int32_t aSample ){

  return;
   //__IO uint16_t adcValue = HAL_ADC_GetValue(hadc);
  
 /*  if( _oTPS_SEL ) adcValue = HAL_ADC_GetValue(hadc);
   else            adcValue2 = HAL_ADC_GetValue(hadc);
   _oTPS_SEL ^= 1; */
  
  
  adcValuePREV[gADC_State] = adcValue[gADC_State];
  adcValue[gADC_State] = aSample;
  
  if( gADC_State == 1 ){ // napiecie A
    /*{
       int32_t dif = ((adcValueAvr[gADC_State] / 1024) - adcValue[gADC_State]);
       if (dif < 0) dif = -dif;
       if (dif > 400) adcValueAvr[gADC_State] = 1024 * adcValue[gADC_State];
    }*/
    adcValueAvr[gADC_State] += adcValue[gADC_State];
    adcValueAvr[gADC_State] -= adcValueAvr[gADC_State] / 2048;
    
    diffs[gADC_State] =  adcValue[gADC_State] - (adcValueAvr[gADC_State] / 2048);
    //if( diffs[gADC_State] < 0 ) diffs[gADC_State] = -diffs[gADC_State];
    
     diffsAVR[gADC_State] += diffs[gADC_State];
     diffsAVR[gADC_State] -= diffsAVR[gADC_State] / 4;
   //  if( diffsAVR[gADC_State] < 0 ) diffsAVR[gADC_State] = -diffsAVR[gADC_State];
     
     if( gRelays.gShortDeadCnt > 0 ) adcValueAvr[gADC_State] = adcValue[gADC_State] * 2048;

    
  }else if( gADC_State == 2 ){ // napiecie B
   /* {
       int32_t dif = ((adcValueAvr[gADC_State] / 1024) - adcValue[gADC_State]);
       if (dif < 0) dif = -dif;
       if (dif > 400) adcValueAvr[gADC_State] = 1024 * adcValue[gADC_State];
    }*/
    adcValueAvr[gADC_State] += adcValue[gADC_State];
    adcValueAvr[gADC_State] -= adcValueAvr[gADC_State] / 2048;
    
    diffs[gADC_State] =  adcValue[gADC_State] - (adcValueAvr[gADC_State] / 2048);
    //if( diffs[gADC_State] < 0 ) diffs[gADC_State] = -diffs[gADC_State];
    
     diffsAVR[gADC_State] += diffs[gADC_State];
     diffsAVR[gADC_State] -= diffsAVR[gADC_State] / 4;
  //   if( diffsAVR[gADC_State] < 0 ) diffsAVR[gADC_State] = -diffsAVR[gADC_State];
     
     if( gRelays.gShortDeadCnt > 0 ) adcValueAvr[gADC_State] = adcValue[gADC_State] * 2048;

    
  }else if( gADC_State == 3 ){ // prad A
    adcValueAvr[gADC_State] += adcValue[gADC_State];
    adcValueAvr[gADC_State] -= adcValueAvr[gADC_State] / 4;
  }else if( gADC_State == 4 ){ // prad B
    adcValueAvr[gADC_State] += adcValue[gADC_State];
    adcValueAvr[gADC_State] -= adcValueAvr[gADC_State] / 4;
  }





}//----------------------------------------------------------------------------





//-----------------------------------------------------------------------------
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