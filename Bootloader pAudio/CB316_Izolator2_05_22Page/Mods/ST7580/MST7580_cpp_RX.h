#ifndef __MST7580_BH704_CPP_RX_H
#define __MST7580_BH704_CPP_RX_H

/// ----------------------------------------------------------
/// FRAME ID  ToNode
void MST7580::frameRX_ToNode_ID( uint8_t *frame ){
                 
}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME GetID  ToNode
void MST7580::frameRX_ToNode_GetID( uint8_t *frame ){
                 
}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME RegAddr  ToNode
void MST7580::frameRX_ToNode_RegAddr( uint8_t *frame ){
  
}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME AskStatus  ToNode
void MST7580::frameRX_ToNode_getStatus( uint8_t *frame ){

    // ... params RX ................
    uint8_t fr_addr   	 = frame[1];
    uint8_t fr_gateway   = frame[2];

    if( fr_addr != g485E.mMyAddr ) return;

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

    gSystem.mIsReg = true;

    // ... send .....................
    uint8_t frameTX[] = {
        0x23,   // RX_Status
		0xC3,	// Type == Status
		fr_gateway,	// odeslij do gateway
        addr,
        status,
        rels2,
        prad1,
        prad2,
        uA_H,
        uA_L,
        uB_H,
        uB_L,
        iA_H,
        iA_L,
        iB_H,
        iB_L
    };

    int cnt = sizeof( frameTX );
    gST7580.mBuf_Frames.bufAddFrame( cnt, frameTX );

}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME AskStatus  ToNode
void MST7580::frameRX_ToNode_setRelays( uint8_t *frame ){

    // ... params RX ................
    uint8_t addr   = frame[1];
    uint8_t relays = frame[2];

    if( addr != g485E.mMyAddr ) return;

    bool isRelA = relays & 0x01;
	bool isRelB = relays & 0x04;

	gRelays.setREL_A( isRelA );
	gRelays.setREL_B( isRelB );

	// BRAKUJE POTWIERDZENIA !!!

}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME AskStatus  ToNode
void MST7580::frameRX_ToNode_setAddr( uint8_t *frame ){

    // ... params RX ................
    uint8_t addr    = frame[1];
    uint8_t newAddr = frame[2];

    if( addr != g485E.mMyAddr ) return;

    g485E.mMyAddr = newAddr;
    gFlash_SSD.set8( 0, g485E.mMyAddr );
    gFlash_SSD.flush();

    // BRAKUJE POTWIERDZENIA !!!

}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME set specific address to unregistered nodes
void MST7580::frameRX_ToNode_setAddrUnreg( uint8_t *frame ){

    // ... params RX ................
    uint8_t newAddr    = frame[1];

    if( gSystem.mIsReg ) return;

    g485E.mMyAddr = newAddr;
    gFlash_SSD.set8( 0, g485E.mMyAddr );
    gFlash_SSD.flush();

    // BRAKUJE POTWIERDZENIA !!!

}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME AskStatus  ToNode
void MST7580::frameRX_ToNode_hiUnreg( uint8_t *frame ){

    // ... params RX ................
    if( gSystem.mIsReg ) return;
    g485E.mMyAddr = 0xCC;
    uint8_t addr =  g485E.mMyAddr;
    uint8_t gateway = frame[1];


    // ... send .....................
        uint8_t frameTX[] = {
            0x24,   // RX_HiReg_Ans
            addr,
			gateway
        };

        int cnt = sizeof( frameTX );
        gST7580.mBuf_Frames.bufAddFrame( cnt, frameTX );


}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME EXT  ToNode
void MST7580::frameRX_ToNode_Ext( uint8_t *frame ){
  
    
}// -----------------------------------------------------------



/// ----------------------------------------------------------
/// FRAME ID  ToGateway 
void MST7580::frameRX_ToGateway_ID( uint8_t *frame ){
                   
}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME GetID  ToGateway
void MST7580::frameRX_ToGateway_GetID( uint8_t *frame ){
    
}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME RegAddr  ToGateway 

void MST7580::frameRX_ToGateway_RegAddr( uint8_t *frame ){
    
}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME AskStatus  ToGateway
void MST7580::frameRX_ToGateway_getStatus( uint8_t *frame ){
	uint8_t type   = frame[1];
	uint8_t gateway = frame[2];
	uint8_t addr  = frame[3];
	uint8_t status  = frame[4];
	uint8_t rels2  = frame[5];
	uint8_t mSO1   = frame[6];
	uint8_t mSO2   = frame[7];
	uint8_t mUA1   = frame[8];
	uint8_t mUA2   = frame[9];
	uint8_t mUB1   = frame[10];
	uint8_t mUB2   = frame[11];
	uint8_t mIA1   = frame[12];
	uint8_t mIA2   = frame[13];
	uint8_t mIB1   = frame[14];
	uint8_t mIB2   = frame[15];

	if(g485E.mMyAddr != gateway) return;

    //Wyliczanie CRC
    uint16_t crc = 0x0000;

    crc = g485E.addCrc(crc, 0x5A);
    crc = g485E.addCrc(crc, g485E.loopNr);
    crc = g485E.addCrc(crc, gateway);
    crc = g485E.addCrc(crc, addr);
    crc = g485E.addCrc(crc, type);
    crc = g485E.addCrc(crc, 0x0C);

    crc = g485E.addCrc(crc, status);
    crc = g485E.addCrc(crc, rels2);
    crc = g485E.addCrc(crc, mSO1);
    crc = g485E.addCrc(crc, mSO2);
    crc = g485E.addCrc(crc, mUA1);
    crc = g485E.addCrc(crc, mUA2);
    crc = g485E.addCrc(crc, mUB1);
    crc = g485E.addCrc(crc, mUB2);
    crc = g485E.addCrc(crc, mIA1);
    crc = g485E.addCrc(crc, mIA2);
    crc = g485E.addCrc(crc, mIB1);
    crc = g485E.addCrc(crc, mIB2);

    uint8_t crc_H = (crc >> 8);
    uint8_t crc_L = (crc >> 0);


    g485E.bufAdd( 0x5A );     // naglowek
    g485E.bufAdd( g485E.loopNr ); // loop number
    g485E.bufAdd( gateway );  // gateway
    g485E.bufAdd( addr );     // address
    g485E.bufAdd( type );     // typ ramki STATUS
    g485E.bufAdd( 0x0C );	  // counter
    g485E.bufAdd( crc_H );    // CRC
    g485E.bufAdd( crc_L );    // CRC

    g485E.bufAdd( status );   // Status
    g485E.bufAdd( rels2 );    // Relays

    g485E.bufAdd( mSO1 );     // Prad sens 1
    g485E.bufAdd( mSO2 );     // Prad sens 2
    g485E.bufAdd( mUA1 );     // UA linii
    g485E.bufAdd( mUA2 );     // UA linii
    g485E.bufAdd( mUB1 );     // UB linii
    g485E.bufAdd( mUB2 );     // UB linii

    g485E.bufAdd( mIA1 );     // IA linii
    g485E.bufAdd( mIA2 );     // IA linii
    g485E.bufAdd( mIB1 );     // IB linii
    g485E.bufAdd( mIB2 );     // IB linii

    g485E.Send_IT();


}// -----------------------------------------------------------


/// ----------------------------------------------------------
/// FRAME AskStatus  ToGateway
void MST7580::frameRX_ToGateway_hiFromUnreg( uint8_t *frame ){
	uint8_t addr  = frame[1];
	uint8_t gateway  = frame[2];

    g485E.bufAdd( 0x5A );     // naglowek
    g485E.bufAdd( g485E.loopNr ); //loop
    g485E.bufAdd( gateway );     // gateway
    g485E.bufAdd( addr );     // address
    g485E.bufAdd( 0xC6 );     // typ ramki STATUS
    g485E.bufAdd( 0x00 );     // ilosc
    g485E.bufAdd( 0xE0 );     // CRC
    g485E.bufAdd( 0xE1 );     // CRC

    g485E.Send_IT();


}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME EXT  ToGateway
void MST7580::frameRX_ToGateway_Ext( uint8_t *frame ){
  
    
}// -----------------------------------------------------------


#endif
/*########################################################################################*/
