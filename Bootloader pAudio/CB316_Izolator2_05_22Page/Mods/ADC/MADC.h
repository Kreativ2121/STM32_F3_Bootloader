#ifndef __MADC_BH704_H
#define __MADC_BH704_H

#include <cstdint>

#include "..\GPIO\MGPIO.h"

/*########################################################################################*/
/******************** KLASY ***************************************************************/      

// ADC_1.ch11  IA
// ADC_1.ch12  IB
// ADC_2.ch2   UA
// ADC_2.ch14  UB




uint16_t gADC1_Tab[5];  // [0]=IA; [1]=IB
uint16_t gADC2_Tab[5];  // [0]=UA; [1]=UB


  class MADC{

    //+++ POLA ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public: uint8_t gADC_State = 5;
    
    public: uint8_t mCurADC2_Channel;
    public: uint8_t mCurADC1_Channel;
  
  //  public: __IO int16_t adcValuePREV[6] = {-1,-1,-1,-1,-1,-1};
  //  public: __IO int16_t adcValue[6] = {-1,-1,-1,-1,-1,-1};

    public: int16_t mS0 = 0;

    
    public: int16_t mUA = 0;    
    public: int32_t mUA_iir = 400*512;
    public: int16_t mUA_avr = 400;

    
    public: int16_t mIA = 0;
    public: int32_t mIA_iir = 2000*2048;
    public: int16_t mIA_avr = 2000;
    public: int32_t mIAabs_iir = 0;
    public: int16_t mIAabs_avr = 0;
    
    
    public: int16_t mUB = 0;
    public: int32_t mUB_iir = 400*512;
    public: int16_t mUB_avr = 400;

    
    public: int16_t mIB = 0;
    public: int32_t mIB_iir = 2000*2048;
    public: int16_t mIB_avr = 2000;
    public: int32_t mIBabs_iir = 0;
    public: int16_t mIBabs_avr = 0;
    
    
    //public: __IO int32_t adcValueAvr[6] = {-1,-1,-1,-1,-1,-1};

//    public: int32_t diffsAVR[6] = {-1,-1,-1,-1,-1,-1};
 //   public: int32_t diffs[6] = {-1,-1,-1,-1,-1,-1};
  

  
    //+++ METODY +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    public: void initIRQ(); 
    public: void  onSample_ADC1();
    public: void  onSample_ADC2();
    
    //+++ STARE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    /// inicjalizacja
    public: void init();  // stare

    /// event: TIMER    
    public: void onTimer(); // puste
    
    public: void  setADC1_Channel( uint8_t aChNbr ); // stare
    public: void  setADC2_Channel( uint8_t aChNbr ); // stare
    
    
    };//************************************************************************************



    MADC gADC;


/*########################################################################################*/
/******************** METODY **************************************************************/      






#endif
/*########################################################################################*/