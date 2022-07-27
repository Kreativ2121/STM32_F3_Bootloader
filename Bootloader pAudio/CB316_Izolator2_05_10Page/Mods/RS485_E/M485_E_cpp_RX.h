#ifndef __M485E_RX_CA529_CPP_H
#define __M485E_RX_CA529_CPP_H

#include "M485_E.h"

/*########################################################################################*/

/// ----------------------------------------------------------
/// FRAME Reg_Addr  0xBC
void M485E::frameRX_RegAddr(){
  
    uint16_t crc = (uint16_t)((mRXFrameBuf[6] << 8) | (mRXFrameBuf[7]));
    if (crc != 0xE0E1) return;  // nie poprawne CRC
  
    uint8_t gateway = mRXFrameBuf[0];
    uint8_t id_HH   = mRXFrameBuf[1];
    uint8_t id_HL   = mRXFrameBuf[2];
    uint8_t id_LH   = mRXFrameBuf[3];
    uint8_t id_LL   = mRXFrameBuf[4];
    uint8_t newAddr = mRXFrameBuf[5];
    
    // ..........................
    uint32_t id = (uint32_t)( ( id_HH << 24 ) | 
                              ( id_HL << 16 ) | 
                              ( id_LH <<  8 ) | 
                              ( id_LL <<  0 ) );
    
    if( gateway == 0xCC ){
    
      if( id != gSystem.mID ) return; // ID innego urzadzenia
    
      mMyAddr = newAddr;
      sendTX_RegAddr( gateway );
    
    }else{
      
      //if( id == gSystem.mID ) return; // pomylka ID
      if( gateway == mMyAddr )
        gST7580.sendTX_RegAddr( id, newAddr );
      
    }

    
}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME ID  0x5B
void M485E::frameRX_ID(){

    uint16_t crc = (uint16_t)((mRXFrameBuf[1] << 8) | (mRXFrameBuf[2]));
    if (crc != 0xE0E1) return;  // nie poprawne CRC

    uint8_t gateway = mRXFrameBuf[0];

    if( gateway == 0xCC ){   // ramka ID do 485
      if( mMyAddr != 0xCC ) return;      // modul zarejestrowany
      sendTX_ID( gateway );
    }else{
      // if( addr == mMyAddr ) return; // blad adresu
      if( gateway == mMyAddr )
        gST7580.sendTX_ID( 0x00 );
    }

}// -----------------------------------------------------------


/// ----------------------------------------------------------
/// FRAME EXT
void M485E::frameRX_Ext(){
 
    uint8_t addr   =  mRXFrameBuf[0];
    uint8_t cnt    =  mRXFrameBuf[1];
    uint8_t *frame = &mRXFrameBuf[2];
  
    uint8_t crcH   =  mRXFrameBuf[3+mRXFrameByteCnt-1];
    uint8_t crcL   =  mRXFrameBuf[4+mRXFrameByteCnt-1];
    
    uint16_t crc = (uint16_t)(( crcH<<8 ) | ( crcL<<0 ));
    if (crc != 0xE0E1) return;  // nie poprawne CRC
        
    // ..........................
    if( mMyAddr != addr ) return;      // modul zarejestrowany
    
    gST7580.mBuf_Frames.bufAddFrame( cnt, frame );
    
}// -----------------------------------------------------------




/// ----------------------------------------------------------
/// FRAME GetID  0x5C // do wywalenia???
void M485E::frameRX_GetID(){
  
    uint16_t crc = (uint16_t)((mRXFrameBuf[2] << 8) | (mRXFrameBuf[3]));
    if (crc != 0xE0E1) return;  // nie poprawne CRC
    
    uint8_t gateway = mRXFrameBuf[0];
    uint8_t addr = mRXFrameBuf[1];
        
    if( gateway == 0xCC ){   // ramka ID do 485
        if( addr != mMyAddr ) return;
        sendTX_GetID( gateway );
    }else{
        // if( addr == mMyAddr ) return; // blad adresu
        if( gateway == mMyAddr )
          gST7580.sendTX_GetID( addr );
    }

}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME GetID  0x5C
void M485E::frameRX_ReceiveMsg(){

    uint16_t crc = (uint16_t)((mRXFrameBuf[2] << 8) | (mRXFrameBuf[3]));
    if (crc != 0xE0E1) return;  // nie poprawne CRC

    uint8_t gateway = mRXFrameBuf[0];
    uint8_t addr = mRXFrameBuf[1];

    if( gateway == 0xCC ){   // ramka ID do 485
        if( addr != mMyAddr ) return;
        sendTX_GetID( gateway );
    }else{
        // if( addr == mMyAddr ) return; // blad adresu
        if( gateway == mMyAddr )
          gST7580.sendTX_GetID( addr );
    }

}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME getStatus
void M485E::frameRX_getStatus(){

    uint16_t crc = (uint16_t)((mRXFrameBuf[4] << 8) | (mRXFrameBuf[5]));
    if (crc != 0xE0E1) return;  // nie poprawne CRC

    uint8_t loop = mRXFrameBuf[0];
    uint8_t gateway = mRXFrameBuf[1];
    uint8_t addr = mRXFrameBuf[2];

    if( ( addr == g485E.mMyAddr) && ( gateway == g485E.mMyAddr ) && (loop == g485E.loopNr) ){
    	// ... params ToSend ............
    	    uint8_t addr   = g485E.mMyAddr;
    	    uint8_t status = 0x01;
    	    uint8_t rels2 = 0x00;
    	    if( gRelays.mRelA_IsON ) rels2 |= 0x01;
    	    if( gRelays.mRelB_IsON ) rels2 |= 0x04;

    	    uint8_t prad1 = gADC.mS0;             // Prad sens 1
    	    uint8_t prad2 = gADC.mS0;             // Prad sens 2
    	    uint8_t uA_H  = (gADC.mUA_avr>>8);    // UA linii
    	    uint8_t uA_L  = (gADC.mUA_avr>>0);    // UA linii
    	    uint8_t uB_H  = (gADC.mUB_avr>>8);    // UB linii
    	    uint8_t uB_L  = (gADC.mUB_avr>>0);    // UB linii
    	    uint8_t iA_H  = (gADC.mIAabs_avr>>8); // IA linii
    	    uint8_t iA_L  = (gADC.mIAabs_avr>>0); // IA linii
    	    uint8_t iB_H  = (gADC.mIBabs_avr>>8); // IB linii
    	    uint8_t iB_L  = (gADC.mIBabs_avr>>0); // IB linii

    	    //Wyliczanie CRC
    	    uint16_t crc = 0x0000;

    	    crc = g485E.addCrc(crc, 0x5A);
    	    crc = g485E.addCrc(crc, loop);
    	    crc = g485E.addCrc(crc, gateway);
    	    crc = g485E.addCrc(crc, addr);
    	    crc = g485E.addCrc(crc, 0xC3);
    	    crc = g485E.addCrc(crc, 0x0C);

    	    crc = g485E.addCrc(crc, status);
    	    crc = g485E.addCrc(crc, rels2);
    	    crc = g485E.addCrc(crc, prad1);
    	    crc = g485E.addCrc(crc, prad2);
    	    crc = g485E.addCrc(crc, uA_H);
    	    crc = g485E.addCrc(crc, uA_L);
    	    crc = g485E.addCrc(crc, uB_H);
    	    crc = g485E.addCrc(crc, uB_L);
    	    crc = g485E.addCrc(crc, iA_H);
    	    crc = g485E.addCrc(crc, iA_L);
    	    crc = g485E.addCrc(crc, iB_H);
    	    crc = g485E.addCrc(crc, iB_L);

    	    uint8_t crc_H = (crc >> 8);
    	    uint8_t crc_L = (crc >> 0);

    	    this->bufAdd(0x5A);
    	    this->bufAdd(g485E.loopNr); // numberOfLoop
    	    this->bufAdd(addr);	// gateway
    	    this->bufAdd(addr);	// addr
    	    this->bufAdd(0xC3);
    	    this->bufAdd(0x0C);
    	    this->bufAdd( crc_H ); // CRC
			this->bufAdd( crc_L ); // CRC
    	    this->bufAdd(status);
    	    this->bufAdd(rels2);
    	    this->bufAdd(prad1);
    	    this->bufAdd(prad2);
    	    this->bufAdd(uA_H);
    	    this->bufAdd(uA_L);
    	    this->bufAdd(uB_H);
    	    this->bufAdd(uB_L);
    	    this->bufAdd(iA_H);
    	    this->bufAdd(iA_L);
    	    this->bufAdd(iB_H);
    	    this->bufAdd(iB_L);

			this->Send_IT();
    }else{
    	if(gateway == g485E.mMyAddr && loop == g485E.loopNr)
    	{
    		gST7580.sendTX_getStatus(addr, gateway);
    	}
    }

}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME Unregister
void M485E::frameRX_unReg(){

    uint16_t crc = (uint16_t)((mRXFrameBuf[4] << 8) | (mRXFrameBuf[5])); // ZMIENIC!
    if (crc != 0xE0E1) return;  // nie poprawne CRC

    uint8_t loop = mRXFrameBuf[0];
    uint8_t gateway = mRXFrameBuf[1];

    if(gateway == g485E.mMyAddr && loop == g485E.loopNr)
    {
    	gST7580.sendTX_hiUnreg(gateway);
    }

}

// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME Send specific address to all unregistered nodes
void M485E::frameRX_setAddrUnreg(){

    uint16_t crc = (uint16_t)((mRXFrameBuf[2] << 8) | (mRXFrameBuf[3])); // ZMIENIC!
    if (crc != 0xE0E1) return;  // nie poprawne CRC

    uint8_t gateway = mRXFrameBuf[0];
    uint8_t newAddr = mRXFrameBuf[1];

    if(gateway == g485E.mMyAddr)
    {
    	gST7580.sendTX_ToNode_setAddrUnreg(newAddr);
    }

}

// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME setRelays
void M485E::frameRX_setRelays(){
	uint16_t crc = (uint16_t)((mRXFrameBuf[4] << 8) | (mRXFrameBuf[5]));
	if (crc != 0xE0E1) return;  // nie poprawne CRC

	uint8_t loop = mRXFrameBuf[0];
	uint8_t gateway = mRXFrameBuf[1];
	uint8_t addr = mRXFrameBuf[2];
	uint8_t rel = mRXFrameBuf[6];

	if(( addr == g485E.mMyAddr) && ( gateway == g485E.mMyAddr ) && (loop == g485E.loopNr) )
	{

		bool isRelA = rel & 0x01;
		bool isRelB = rel & 0x04;

		gRelays.setREL_A( isRelA );
		gRelays.setREL_B( isRelB );

    }else{
    	if(gateway == g485E.mMyAddr && loop == g485E.loopNr)
    	{
    		gST7580.sendTX_setRelays(addr, rel);
    	}
    }


    }

// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME setAddr
void M485E::frameRX_setAddr(){

    uint16_t crc = (uint16_t)((mRXFrameBuf[4] << 8) | (mRXFrameBuf[5]));
    if (crc != 0xE0E1) return;  // nie poprawne CRC

    uint8_t loop = mRXFrameBuf[0];
    uint8_t gateway = mRXFrameBuf[1];
    uint8_t addr = mRXFrameBuf[2];
    uint8_t newAddr = mRXFrameBuf[6];

    if(( addr == g485E.mMyAddr) && ( gateway == g485E.mMyAddr ) && (loop == g485E.loopNr)){
    	g485E.mMyAddr = newAddr;
        gFlash_SSD.set8( 0, g485E.mMyAddr );
        gFlash_SSD.flush();
    }else{
    	if(gateway == g485E.mMyAddr && loop == g485E.loopNr)
    	{
    		gST7580.sendTX_setAddr(addr, newAddr);
    	}
    }

    }

// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME AskStatus    0xC3
void M485E::frameRX_AskStatus(){ //Czy ta komenda jest do wywalenia?

     uint16_t crc = (uint16_t)((mRXFrameBuf[3] << 8) | (mRXFrameBuf[4]));
     if (crc != 0xE0E1) return;  // nie poprawne CRC
     //mComStats.updateRXFrame_Stats();
  
    uint8_t gateway = mRXFrameBuf[0];
    uint8_t addr = mRXFrameBuf[1];
    int8_t rels = mRXFrameBuf[2];
     

    

    /*uint8_t bitMSBMy = ( mMyAddr & 0x80 );
    uint8_t bitMSBAd = ( addr & 0x80 );
    bool isSendM1 = (bitMSBMy == bitMSBAd);*/
    
//    for( int i =0; i<128; i++ ) gDbgTab[i] = 0;
//    for( int i =0; i<128; i++ ) gDbgTab2[i] = 0;
//    gDbgIndex = 0;
          
    if( gateway == 0xCC ){   // ramka ID do 485
        if( addr != mMyAddr ) return;

        // ... relays ...................
        if( rels & 0x01 ) rels &= ~0x02;
        if( rels & 0x04 ) rels &= ~0x08;        
        if( mPrevRels != rels ){
              gRelays.gRelayCnt = 30;
              gRelays.gShortDeadCnt = 400;
              
                _oREL_A_SET   = ( rels & 0x01 )?1:0;
                _oREL_A_RESET = ( rels & 0x02 )?1:0;
                _oREL_B_SET   = ( rels & 0x04 )?1:0;
                _oREL_B_RESET = ( rels & 0x08 )?1:0;
                
                if( _oREL_A_SET )   gRelays.mRelA_IsON = true;
                if( _oREL_A_RESET ) gRelays.mRelA_IsON = false;
                if( _oREL_B_SET )   gRelays.mRelB_IsON = true;
                if( _oREL_B_RESET ) gRelays.mRelB_IsON = false;

         }
         mPrevRels = rels;
         
        // ... wyslij ramke ............
        sendTX_STATUS( gateway ); // 0x42
              
        
    }else{
        // if( addr == mMyAddr ) return; // blad adresu
        if( gateway == mMyAddr )
          gST7580.sendTX_AskStatus( addr, rels );
    }
 
  
}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME CONFIG  0xBF
void M485E::frameRX_Config(){
    uint8_t addr = mRXFrameBuf[0];
    
    if( addr == mMyAddr ){

    }
    
    
}// -----------------------------------------------------------

/*########################################################################################*/


#endif
/*########################################################################################*/
