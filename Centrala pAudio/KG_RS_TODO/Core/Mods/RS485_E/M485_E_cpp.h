#ifndef __M485E_CA529_CPP_H
#define __M485E_CA529_CPP_H

#include "M485_E.h"

/*########################################################################################*/



int tabIndex = 0;
uint8_t tab[100];


void M485E::onReceive( uint8_t aCh ){
  
//  ITM_EVENT8( 1, mRXBuf[0] );

	//DEBUG
	tab[tabIndex] = aCh;
	tabIndex += 1;
	if( tabIndex >= 100 ) tabIndex = 0;




      
INTTOPC_PROC_LABEL:
    switch( mRecState ){
      // ------------------------------------------------

    case 0: if( aCh == 0xA5 )
		mRecState += 1;
		break; // 0

    case 1:
    	mRXFrameBuf[0] = aCh; mRecState += 1; break;  // loop nr
    case 2:
    	mRXFrameBuf[1] = aCh; mRecState += 1; break;  // gateway
    case 3:
    	mRXFrameBuf[2] = aCh; mRecState += 1; break;  // address

    case 4: //mRXFrameByteCnt = 0; // typ ramki
          if( aCh == 0xC3 )
        	  mRecState = 5;
          else if( aCh == 0xC4)
        	  mRecState = 10;
          else if ( aCh == 0xC5)
        	  mRecState = 20;
          else if ( aCh == 0xC6)
        	  mRecState = 30;
          else if ( aCh == 0xC7)
        	  mRecState = 40;

         else{ mRecState = 0; goto INTTOPC_PROC_LABEL; }
         break;

    //-------------------
    // :GetStatus:
    //-------------------
    case 5: mRXFrameBuf[3] = aCh; mRecState += 1; break;  // dataLen
    case 6: mRXFrameBuf[4] = aCh; mRecState += 1; break;  // CRC.H  0xE0
    case 7: mRXFrameBuf[5] = aCh; mRecState += 1; //frameRX_getStatus();
    mRecState = 0; break;  // CRC.L  0xE1

   //-------------------
   // :SetRelays:
   //-------------------
    case 10: mRXFrameBuf[3] = aCh; mRecState += 1; break;  // dataLen
    case 11: mRXFrameBuf[4] = aCh; mRecState += 1; break;  // CRC.H  0xE0
    case 12: mRXFrameBuf[5] = aCh; mRecState += 1; break;  // CRC.L  0xE1
    case 13: mRXFrameBuf[6] = aCh; mRecState += 1; //frameRX_setRelays();
    mRecState = 0; break;  // relay

   //-------------------
   // :SetAddr:
   //-------------------
    case 20: mRXFrameBuf[3] = aCh; mRecState += 1; break;  // dataLen
    case 21: mRXFrameBuf[4] = aCh; mRecState += 1; break;  // CRC.H  0xE0
    case 22: mRXFrameBuf[5] = aCh; mRecState += 1; break;  // CRC.L  0xE1
    case 23: mRXFrameBuf[6] = aCh; //frameRX_setAddr();
    mRecState = 0; break;  // newAddr

   	//-------------------
    // :HiUnreg:
    //-------------------
     case 30: mRXFrameBuf[3] = aCh; mRecState += 1; break;  // dataLen
     case 31: mRXFrameBuf[4] = aCh; mRecState += 1; break;  // CRC.H  0xE0
     case 32: mRXFrameBuf[5] = aCh; //frameRX_unReg();
     mRecState = 0; break; // CRC.L  0xE1

   	//-------------------
    // :setAddrUnreg:
    //-------------------
    //DO ANSCHLUSS
     case 40: mRXFrameBuf[3] = aCh; mRecState += 1; break;  // newAddr
     case 41: mRXFrameBuf[4] = aCh; mRecState += 1; break;  // dataLen
     case 42: mRXFrameBuf[5] = aCh; mRecState += 1; break;  // CRC.H  0xE0
     case 43: mRXFrameBuf[6] = aCh; mRecState += 1; break;  // CRC.L  0xE1
     case 44: if( aCh == 0xFF )
    	 //frameRX_setAddrUnreg();
    mRecState = 0; break;

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
