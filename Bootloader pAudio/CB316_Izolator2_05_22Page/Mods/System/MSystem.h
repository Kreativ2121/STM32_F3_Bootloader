#ifndef __MSystem_BH704_H
#define __MSystem_BH704_H

#include <cstdint>

#include "..\GPIO\MGPIO.h"

/*########################################################################################*/
/******************** KLASY ***************************************************************/      

enum EPwrSupSource: uint8_t{ NOT_KNOWN=0, A=1, B=2 };



  class MSystem{

    //+++ POLA ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // ... SysTick ........................
  	public: uint16_t mTimer_Cnt1000ms=3 + (g485E.mMyAddr * 3);    // do main_1000ms
    public: uint8_t mTimer_Cnt100ms=0 + (g485E.mMyAddr * 3);    // do main_100ms
    public: uint8_t mTimer_Cnt10ms=5 + (g485E.mMyAddr * 3);     // do main_10ms
    
    public: bool mTimer_Is1000ms = false;		   // czy main_1000ms
    public: bool mTimer_Is100ms = false;       // czy main_100ms
    public: bool mTimer_Is10ms = false;        // czy main_10ms
    
      
    // ... PwrSupSource ....................
    public: EPwrSupSource mPwrSup_Source = EPwrSupSource::NOT_KNOWN;
    public: int8_t mPwr_Cnt = 15; // 1s=10; licznik opozniajacy badanie PwrSource
    
    /// ------------------------------------------------------------------------
    /// is registered
    public: bool mIsReg = false; //czy zarejestrowany

    
    public: uint32_t mID = _M_ID;
    
    
    
    //+++ METODY +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // --------- KONFIGURACJA ----------------------------

    /// inicjalizacja
    public: void init(){
    };//------------------------------------------------------------------------

    
    /// event: TIMER    
    public: void onTimer_1ms(){
      
      // ... 1000 ms ...............
	  mTimer_Cnt1000ms+=1;
	  if( mTimer_Cnt1000ms > 1000 ){
		mTimer_Is1000ms = true;
		mTimer_Cnt1000ms = 0;
	  }

      // ... 100 ms ................
      mTimer_Cnt100ms+=1;
      if( mTimer_Cnt100ms > 100 ){
        mTimer_Is100ms = true;
        mTimer_Cnt100ms = 0;
      }

      // ... 10 ms ................
      mTimer_Cnt10ms+=1;
      if( mTimer_Cnt10ms > 10 ){
        mTimer_Is10ms = true;
        mTimer_Cnt10ms = 0;
      }

      
    };//------------------------------------------------------------------------

    
    /// event: MAIN
    public: void onMain(){
      // TimerXms przerzucone do glownego maina dla czytelnosci kodu !!!
    };//------------------------------------------------------------------------

    
    


     public: void onTimer_Main100ms();
    
  };//**************************************************************************


    MSystem gSystem;


/*########################################################################################*/
/******************** METODY **************************************************************/      




#endif
/*########################################################################################*/
