#ifndef __MSystem_BH704_CPP_H
#define __MSystem_BH704_CPP_H


/*########################################################################################*/


//------------------------------------------------------------------------------
void MSystem::onTimer_Main100ms(){
 
 // ... PwrSupSource ....................................
 // if all Rels OFF -> UA?UB -> SupSource
  
 // zmienne potrzebne 
  //g.Relays.mRelA_IsON
  //gADC.mUB_avr
  //gADC.mUA_avr 

  // if all Rels OFF - tylko zrodlo zasilania zostanie
  // + problem gdy zmiana zrodla zasilania !!!
  
//  if( ( gRelays.mRelA_IsON == false ) && ( gRelays.mRelB_IsON == false ) ){
//
//    // Pwr_Cnt - czas martwy na ustabilizowanie zasilania ADC
//    if( mPwr_Cnt <= 0 ){
//
//      if( gADC.mUA_avr > 500 )	// 19.03.2022, zmieniliśmy z 500 na 2000, zaczęło działać - włączyły się wszystkie izolatory
//        mPwrSup_Source = EPwrSupSource::A;
//      else if( gADC.mUB_avr > 800 )
//        mPwrSup_Source = EPwrSupSource::B;
//
//      gST7580.mModemWDT = 0;
//
//    }else mPwr_Cnt -= 1;
//
//  }else{
//    mPwr_Cnt = 15;
//
//  }
  // .........................................................
  
}//----------------------------------------------------------------------------  





/*########################################################################################*/


#endif
/*########################################################################################*/
