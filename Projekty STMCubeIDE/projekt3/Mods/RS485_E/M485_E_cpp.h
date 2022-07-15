#ifndef __M485E_CA529_CPP_H
#define __M485E_CA529_CPP_H

#include "M485_E.h"
//#include "../Flash_SSD/MFlash.h"
/*########################################################################################*/



int tabIndex = 0;
uint8_t tab[100];
uint16_t cnt = 0, nr = 3;


void M485E::onReceive( uint8_t aCh ){
  
//  ITM_EVENT8( 1, mRXBuf[0] );

	//DEBUG
	tab[tabIndex] = aCh;
	tabIndex += 1;
	if( tabIndex >= 100 ) tabIndex = 0;


      
INTTOPC_PROC_LABEL:
    switch( mRecState ){
      // ------------------------------------------------

    case 0:
    	if( aCh == 0x55 ){
    		mRXFrameBuf[0] = aCh;
			mRecState += 1;
			break;}

//    	//Funkcje tymczasowe -----------------------------
//		if( aCh == 0xFA){//Test: Wpisz wartość do pamięci
//			uint16_t data = MFlash::read16(253,0);//debug
//			MFlash::unlock();
//			MFlash::write16(253,0,0xFAFB);
//			MFlash::lock();
//			data = MFlash::read16(253,0);//debug
//			break;}
//		if( aCh == 0xFB){//Test: Skasuj wartość z pamięci (skasuj stronę)
//			MFlash::unlock();
//			MFlash::erasePage(253);
//			MFlash::lock();
//			break;}
//		if( aCh == 0xFC){//Test: Odczytaj wartość z pamięci
//			uint16_t data = MFlash::read16(253,0);
//			uint8_t lo=data&(0xff);
//			uint8_t hi=(data>>8) & 0xff;
//			sendTX_React(lo,hi);
//			break;}
//	  // -------------------------------
    case 1:
    	if( aCh == 0x04 ){
    		mRXFrameBuf[1] = aCh;
			mRecState += 1;
			break;}
    case 2:
    	if( aCh == 0x00 ){
			mRecState = 10;
			break;}
    	if( aCh == 0x01 ){
			mRecState = 20;
			break;}
    	if( aCh == 0x02 ){
			mRecState = 30;
			break;}
    	if( aCh == 0x0E ){
    		mRecState = 50;
    		break;
    	}
//    	if( aCh == 0x0F ){
//    		mRecState = 40;
//    		break;
//    	}

    //ReadPage
    case 10: mRXFrameBuf[2] = aCh; mRecState += 1; break; //page
    case 11: mRXFrameBuf[3] = aCh; mRecState += 1; break; //OH
    case 12: mRXFrameBuf[4] = aCh; mRecState += 1; break; //OL
    case 13: mRXFrameBuf[5] = aCh; mRecState += 1; break; //HH
    case 14: mRXFrameBuf[6] = aCh; mRecState += 1; break; //HL
    case 15: mRXFrameBuf[7] = aCh; mRecState += 1; break; //LH
    case 16: mRXFrameBuf[8] = aCh; mRecState += 1; break; //LL
    case 17: mRXFrameBuf[9] = aCh; sendTX_ReadPage( mRXFrameBuf[2], mRXFrameBuf[3], mRXFrameBuf[4] ); mRecState = 0; break;

    //WritePage
	case 20: mRXFrameBuf[2] = aCh; mRecState += 1; break; //page
	case 21: mRXFrameBuf[3] = aCh; mRecState += 1; break; //OH
	case 22: mRXFrameBuf[4] = aCh; mRecState += 1; break; //OL
	case 23: mRXFrameBuf[5] = aCh; mRecState += 1; break; //HH
	case 24: mRXFrameBuf[6] = aCh; mRecState += 1; break; //HL
	case 25: mRXFrameBuf[7] = aCh; mRecState += 1; break; //LH
	case 26: mRXFrameBuf[8] = aCh; mRecState += 1; break; //LL
	case 27: mRXFrameBuf[9] = aCh; frameRX_WritePage( mRXFrameBuf[2], mRXFrameBuf[3], mRXFrameBuf[4], mRXFrameBuf[5], mRXFrameBuf[6], mRXFrameBuf[7], mRXFrameBuf[8]); mRecState = 0; break;

    //ErasePage
	case 30: mRXFrameBuf[2] = aCh; mRecState += 1; break;
	case 31: mRXFrameBuf[3] = aCh; mRecState += 1; break;
	case 32: mRXFrameBuf[4] = aCh; mRecState += 1; break;
	case 33: mRXFrameBuf[5] = aCh; mRecState += 1; break;
	case 34: mRXFrameBuf[6] = aCh; mRecState += 1; break;
	case 35: mRXFrameBuf[7] = aCh; mRecState += 1; break;
	case 36: mRXFrameBuf[8] = aCh; mRecState += 1; break;
	case 37: mRXFrameBuf[9] = aCh; frameRX_ErasePage( mRXFrameBuf[2] ); mRecState = 0; break;

//	//JumpToApplication
//	case 40: mRXFrameBuf[2] = aCh; mRecState += 1; break;
//	case 41: mRXFrameBuf[3] = aCh; mRecState += 1; break;
//	case 42: mRXFrameBuf[4] = aCh; mRecState += 1; break;
//	case 43: mRXFrameBuf[5] = aCh; mRecState += 1; break;
//	case 44: mRXFrameBuf[6] = aCh; mRecState += 1; break;
//	case 45: mRXFrameBuf[7] = aCh; mRecState += 1; break;
//	case 46: mRXFrameBuf[8] = aCh; mRecState += 1; break;
//	case 47: mRXFrameBuf[9] = aCh; frameRX_Jump(); mRecState = 0; break;

	//JumpToAddress
	case 50: mRXFrameBuf[2] = aCh; mRecState += 1; break;
	case 51: mRXFrameBuf[3] = aCh; mRecState += 1; break;
	case 52: mRXFrameBuf[4] = aCh; mRecState += 1; break;
	case 53: mRXFrameBuf[5] = aCh; mRecState += 1; break;
	case 54: mRXFrameBuf[6] = aCh; mRecState += 1; break;
	case 55: mRXFrameBuf[7] = aCh; mRecState += 1; break;
	case 56: mRXFrameBuf[8] = aCh; mRecState += 1; break;
	case 57: mRXFrameBuf[9] = aCh; frameRX_JumpToAddress( mRXFrameBuf[5], mRXFrameBuf[6], mRXFrameBuf[7], mRXFrameBuf[8] ); mRecState = 0; break;


      // -------------------------------	
     default: {  
        mRecState = 0;	
        goto INTTOPC_PROC_LABEL; }; 
        break;
    };      
    
    // --- RESET WDT ---------------------
    if( mRecState == 0 )
       mFrameTimeOutCnt = 20; // 100 = 1s
    
 /*   uint16_t wrt = (mRecState<<8) | (aCh<<0);*/



}//-------------------------------------------------------------------------
    



/// event: TIMER
void M485E::onTimer_Frame(){
  
}//-------------------------------------------------------------------------
    


/*########################################################################################*/


#endif
/*########################################################################################*/
