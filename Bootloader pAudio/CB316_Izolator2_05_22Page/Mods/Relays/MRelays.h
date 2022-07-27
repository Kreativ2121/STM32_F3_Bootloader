#ifndef __MRelays_CAC02_H
#define __MRelays_CAC02_H

#include <cstdint>
#include "..\GPIO\MGPIO.h"

/*########################################################################################*/
/******************** KLASY ***************************************************************/      


#ifdef _MODULE_0
    #define _Ith_value  300
    // #define _Ith_value  400
#else
    #define _Ith_value  260
#endif


  class MRelays{

    //+++ POLA ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public: uint32_t gRelayCnt = 0;
    public: int32_t gShortDeadCnt = 0;

    public: uint8_t mRelA_IsON;        // czy przekaznik zalaczony
    public: uint8_t mRelB_IsON;        // czy przekaznik zalaczony
    
    
    public: uint16_t mShortCnt = 0;        // counter opozniajacy OFF po short - dla Mod.0
    
    public: uint16_t mShortCnt_OFFCnt = 0;        // do zerowania ShortCnt
    
    
    //+++ METODY +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // --------- KONFIGURACJA ----------------------------

    /// inicjalizacja
    public: void init(); 
    public: void initProc(); 

    /// event: TIMER    
    public: void onTimer_1ms();
    public: void onTimer_Main10ms();
    

    
    public: void setREL_A( bool aIsON ){
      
      mRelA_IsON = aIsON;
      if( aIsON ) _oREL_A_SET = 1;
      else        _oREL_A_RESET = 1;
      gRelayCnt = 30;
#ifdef _MODULE_0        
        gShortDeadCnt = 50;
#else
        gShortDeadCnt = 200;
#endif      
    };// -----------------------------------
    
    public: void setREL_B( bool aIsON ){
      
      mRelB_IsON = aIsON;
      if( aIsON ) _oREL_B_SET = 1;
      else        _oREL_B_RESET = 1;
      gRelayCnt = 30;
      
#ifdef _MODULE_0        
        gShortDeadCnt = 50;
#else
        gShortDeadCnt = 200;
#endif
      
      
    };// -----------------------------------
    

 //ustawianie ze sprawdzeniem aktualnego stanu - tak aby nie zmieniac gShortDeadCnt
    
    public: void setREL_A_safe( bool aIsON ){
      
      if( aIsON == mRelA_IsON ) return;
      mRelA_IsON = aIsON;
      if( aIsON ) _oREL_A_SET = 1;
      else        _oREL_A_RESET = 1;
      gRelayCnt = 30;
      gShortDeadCnt = 400;
      
    };// -----------------------------------
    
    public: void setREL_B_safe( bool aIsON ){
      
      if( aIsON == mRelB_IsON ) return;
      mRelB_IsON = aIsON;
      if( aIsON ) _oREL_B_SET = 1;
      else        _oREL_B_RESET = 1;
      gRelayCnt = 30;
      gShortDeadCnt = 400;
      
    };// -----------------------------------
    
    
    };//************************************************************************************



    MRelays gRelays;


/*########################################################################################*/
/******************** METODY **************************************************************/      




#endif
/*########################################################################################*/