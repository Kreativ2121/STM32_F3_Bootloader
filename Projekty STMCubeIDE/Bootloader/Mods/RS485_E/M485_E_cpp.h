#ifndef __M485E_CA529_CPP_H
#define __M485E_CA529_CPP_H

#include "M485_E.h"
#include "../Flash_SSD/MFlash.h"
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
    	if( aCh == 0xA5 ){
			mRecState += 1;
			break;}
		if( aCh == 0xFA){//Test: Wpisz wartość do pamięci
			MFlash::write16(0,0,0xFAFA);
			for (int i = 0; i < 6; i++) {
			  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			  HAL_Delay(500);
			}
			break;}
		if( aCh == 0xFB){//Test: Skasuj wartość z pamięci (skasuj stronę)
			MFlash::erasePage(0);
			for (int i = 0; i < 6; i++) {
			  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			  HAL_Delay(500);
			}
			break;}
		if( aCh == 0xFC){//Test: Odczytaj wartość z pamięci
			MFlash::read16(0,0);
			for (int i = 0; i < 6; i++) {
			  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			  HAL_Delay(500);
			}
			sendTX_testAnswer();
			break;}

    case 1:
    	mRXFrameBuf[0] = aCh;  // addr
    	if(aCh == 0xB0)
    		mRecState = 10;
    	else if(aCh == 0xB1)
    		mRecState = 20;
    	else if(aCh == 0xB2)
    		mRecState = 30;
    	else if(aCh == 0xB3)
    		mRecState = 40;
    	else if(aCh == 0xB4)
    		mRecState = 50;
    	else if(aCh == 0xB5)
    		mRecState = 60;
    	break;

    //Bootloader start:
    case 10:
    	mRXFrameBuf[1] = aCh; mRecState+=1; break;//addr
    case 11:
    	mRXFrameBuf[2] = aCh; cnt = mRXFrameBuf[2]; nr = 3; mRecState+=1; break;//data size
    case 12:
    	mRXFrameBuf[nr] = aCh;
    	nr++;
    	cnt--;
    	if(cnt == 0)
    		 mRecState+=1; nr=3; break;
    case 13:
    	if(aCh == 0xFF)
    		//TODO FUNKCJA
    	mRecState = 0;
    	break;

	//Write Flash:
	case 20:
		//TODO
		mRecState = 0;
		break;

	//Read Flash:
    case 30:
    	mRXFrameBuf[1] = aCh; mRecState+=1; break;//addr
    case 31:
    	mRXFrameBuf[2] = aCh; cnt = mRXFrameBuf[2]; mRecState+=1; break;//data size
    case 32:
    	mRXFrameBuf[nr] = aCh;
    	nr++;
    	cnt--;
    	if(cnt == 0)
    		 mRecState+=1; nr=3; break;
    case 33:
    	if(aCh == 0xFF)
    		//frameRX_readFlash();


    		//MFlash::read16( mPage, mOffset );

    	mRecState = 0;
    	break;

	//Bootloader prog ok:
	case 40:
		//TODO
		mRecState = 0;
		break;

	//Bootloader stop:
	case 50:
		//TODO
		mRecState = 0;
		break;

	//Bootloader app start:
	case 60:
		//TODO
		mRecState = 0;
		break;


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
