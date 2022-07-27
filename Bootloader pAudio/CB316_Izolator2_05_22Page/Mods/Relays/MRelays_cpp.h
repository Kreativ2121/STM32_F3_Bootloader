#ifndef __MRelays_BH704_CPP_H
#define __MRelays_BH704_CPP_H

#include "MRelays.h"

#include "..\GPIO\MGPIO.h"
#include "..\ADC\MADC.h"
#include "..\System\MSystem.h"
/*########################################################################################*/


//-----------------------------------------------------------------------------
void MRelays::init(){

    gRelays.gShortDeadCnt = 1000;
  
    _oREL_A_RESET = 1;
    _oREL_B_RESET = 1;
    _oREL_A_SET = 0;
    _oREL_B_SET = 0;
    gRelays.gRelayCnt = 30;
    
}//----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void MRelays::initProc(){
  
      gRelays.gShortDeadCnt = 50;
   //  gRelays.gRelayCnt = 30;
/*     _oREL_A_RESET = 1;
     _oREL_B_RESET = 1;

      mRelA_IsON = false;
      mRelB_IsON = false;  */
      
      gSystem.mPwrSup_Source = EPwrSupSource::NOT_KNOWN;
      
#ifdef _SLAWEK_
      setREL_A( true );
      setREL_B( true );
#else
//      setREL_A( false );
//      setREL_B( false );
      setREL_A( false );
      setREL_B( false );

#endif

      _oREL_A_RESET = 1;
      _oREL_B_RESET = 1;

      
      HAL_Delay(100);


     _oREL_A_RESET = 0;
     _oREL_B_RESET = 0;
      
//      _oREL_A_SET = 1;
 //     _oREL_B_SET = 1;

   //   mRelA_IsON = true;
     // g485E.mRelB_IsON = true;
      
}//----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void MRelays::onTimer_Main10ms(){
  
  // if( g485E.mMyAddr == 0 ) return;
   if( g485E.mMyAddr == 255 ) return;
  
   
/*   if( g485E.mMyAddr == 0 ){
     setREL_A( true );
     return;
   }*/
   
   
      // ... PwrSupSource - zalaczyc przekaznik .....................
      // czy tutaj powinien byc jakis delay ?
#ifdef _SLAWEK_
   
#else   
  if( ( gSystem.mPwrSup_Source == EPwrSupSource::A ) && ( mRelA_IsON == false ) ) {
          setREL_A( true );
  }
    if( ( gSystem.mPwrSup_Source == EPwrSupSource::B ) && ( mRelB_IsON == false ) ) 
      setREL_B( true );
#endif
            
}//----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void MRelays::onTimer_1ms(){

  /*
    if( gShortDeadCnt <= 0 ){
      if( gADC.diffs[1] < -180 ){
        _oREL_A_RESET = 1;
        g485E.mRelA_IsON = false;
        gShortDeadCnt = 200;
        gRelayCnt = 30; }
      
       if( gADC.diffs[2] < -180 ){
         _oREL_B_RESET = 1;
         g485E.mRelB_IsON = false;
         gShortDeadCnt = 200;
         gRelayCnt = 30; }

    }else{
        gShortDeadCnt -= 1;
        gADC.adcValueAvr[1] = gADC.adcValue[1] * 2048;
        gADC.adcValueAvr[2] = gADC.adcValue[2] * 2048;
    }      
    */
  
   uint8_t led = 0;
   // ... ZWARCIE ................................................//24.03.2022 - procedura zwarciowa tymczasowo wyłączona
    if( gShortDeadCnt <= 0 ){ //Czas świadomego zezwolenia na wahania prądu
     //gADC.mIAabs_avr


      if( ( gADC.mIAabs_avr > _Ith_value ) || ( gADC.mIBabs_avr > _Ith_value ) ){ //Jeżeli wartość na którymś z przekaźników przekracza wartość progową zacznij odliczać do zwarcia.

#ifdef _MODULE_0
        if( mShortCnt > 600 ){ //zwarcie
#else
        if( mShortCnt > 50 ){ //zwarcie
#endif

          // rozlaczy oba, pozniej wlaczy ten z ktorego sie zasila
          gSystem.mPwrSup_Source = EPwrSupSource::NOT_KNOWN;

          led = 1;

          setREL_B( false );
          setREL_A( false );

        }else  mShortCnt += 1; //odliczanie do zwarcia

         mShortCnt_OFFCnt = 0; //czas do resetowania czasu aktualnego zwarcia

        /*
         if( gSystem.mPwrSup_Source == EPwrSupSource::A )
            setREL_B( false );
         else if( gSystem.mPwrSup_Source == EPwrSupSource::B )
           setREL_A( false );
         else{
           setREL_B( false );
           setREL_A( false );
         }
         */


          /*g485E.mRelB_IsON = false;
          _oREL_B_RESET = 1;
          gShortDeadCnt = 400;
          gRelayCnt = 50;*/
      }else{

        if( mShortCnt_OFFCnt > 200 ){ //resetowanie aktualnego czasu zwarcia po jego nieobecności przez 200ms
           mShortCnt = 0;
        }else{
          mShortCnt_OFFCnt+= 1;
        }
      }

     // _oLED = !led;



    }else{ //Odliczaj w dół aż czas świadomego zezwolenia minie.
        gShortDeadCnt -= 1;
        if( gShortDeadCnt > 10000 ) gShortDeadCnt = 1000; // wieksze niz 10 s

    }



    _oLED = !led;
  //     ... automatyczne wylaczanie Relays ........................
    if( gRelayCnt > 0 ){
      gRelayCnt -= 1;
    }else{
       _oREL_A_RESET = 0;
       _oREL_B_RESET = 0;
       _oREL_A_SET = 0;
       _oREL_B_SET = 0;

    }
}
/*########################################################################################*/


#endif


/*########################################################################################*/
