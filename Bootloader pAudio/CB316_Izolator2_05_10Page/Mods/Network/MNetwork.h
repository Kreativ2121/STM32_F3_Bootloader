#ifndef __MNetwork_BH704_H
#define __MNetwork_BH704_H

#include <cstdint>
#include "..\GPIO\MGPIO.h"


/*########################################################################################*/
/******************** KLASY ***************************************************************/      

  class MModuleExt{

    public: uint8_t  mRelaysOut = 0;
    
    public: uint16_t  mRelays = 21;
    public: uint16_t  mSens0 = 22;
    public: uint16_t  mSens1 = 23;
    public: uint16_t  mUA = 24;
    public: uint16_t  mUB = 25;
    public: uint16_t  mIA = 26;
    public: uint16_t  mIB = 27;
    
    
    public: uint32_t mComWDT = 0;  // licznik komunikacji
    
    
    // 
    /// event: TIMER_Main100ms
    public: void onTimer_Main100ms(){
       if( mComWDT < 2000 )       // 200 s
          mComWDT += 1;
    
    };//------------------------------------------------------------------------
    
  };

  MModuleExt gMod1;


  class MNetwork{

    //+++ POLA ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    //+++ METODY +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // --------- KONFIGURACJA ----------------------------

    /// inicjalizacja
    public: void init(){}; 

    /// event: TIMER    
    public: void onTimer(){};
    



    };//************************************************************************************



    MNetwork gNetwork;


/*########################################################################################*/
/******************** METODY **************************************************************/      



#endif
/*########################################################################################*/