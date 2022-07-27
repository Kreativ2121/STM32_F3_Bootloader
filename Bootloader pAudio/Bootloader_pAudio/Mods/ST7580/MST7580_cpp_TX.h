#ifndef __MST7580_BH704_CPP_TX_H
#define __MST7580_BH704_CPP_TX_H



/// ----------------------------------------------------------
/// FRAME ID
void MST7580::sendTX_ID( uint8_t aParam ){
  
    // --- zmienne --------------------------------------
 
    // --- wysylanie ------------------------------------
    const int cnt = 2;
    uint8_t frame[cnt];
    frame[0] = 0x50;            // cmd = ID
    frame[1] = aParam;          // param
    gST7580.mBuf_Frames.bufAddFrame( cnt, frame );

  
}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// NEXT FRAME ID
void MST7580::sendTX_NextID( uint8_t aParam ){

    // --- zmienne --------------------------------------

    // --- wysylanie ------------------------------------
    const int cnt = 2;
    uint8_t frame[cnt];
    frame[0] = 0x20;            // cmd = ID
    frame[1] = aParam;          // param
    gST7580.mBuf_Frames.bufAddFrame( cnt, frame );


}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// Send Status to Gateway
void MST7580::sendTX_StatusToGateway(){

    // --- zmienne --------------------------------------
	uint8_t rels2 = 0x00;
	if( gRelays.mRelA_IsON ) rels2 |= 0x01;
	if( gRelays.mRelB_IsON ) rels2 |= 0x04;
	uint8_t status = 0x01;
    // --- wysylanie ------------------------------------
    const int cnt = 19;
    uint8_t frame[cnt];
    frame[0] = 0x5A;                     // naglowek
    frame[1] = 0x42;          			 // typ ramki
    frame[2] = 0x00;					 // gateway
    frame[3] = g485E.mMyAddr;					 // address
    frame[4] = status;	//Status
    frame[5] = rels2;	//Relays
    frame[6] = gADC.mS0;	//Prad sens 1
    frame[7] = gADC.mS0;	//Prad sens 2
    frame[8] = (gADC.mUA_avr>>8);	//UA linii
    frame[9] = (gADC.mUA_avr>>0);	//UA linii
    frame[10] = (gADC.mUB_avr>>8);	//UB linii
    frame[11] = (gADC.mUB_avr>>0);	//UB linii
    frame[12] = (gADC.mIAabs_avr>>8);	//IA linii
    frame[13] = (gADC.mIAabs_avr>>0);	//IA linii
    frame[14] = (gADC.mIBabs_avr>>8);	//IB linii
    frame[15] = (gADC.mIBabs_avr>>0);	//IB linii
    frame[16] = 0xE0;	// CRC
    frame[17] = 0xE1;	// CRC
    frame[18] = 0xFF;	// stopka

    gST7580.mBuf_Frames.bufAddFrame( cnt, frame );


}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME RegAddr
void MST7580::sendTX_RegAddr( uint32_t id, uint8_t  newAddr ){
  
    // --- zmienne --------------------------------------
    uint8_t id_HH   = (uint8_t)(id >> 24 );
    uint8_t id_HL   = (uint8_t)(id >> 16 );
    uint8_t id_LH   = (uint8_t)(id >>  8 );
    uint8_t id_LL   = (uint8_t)(id >>  0 );
    
    // --- wysylanie ------------------------------------
    const int cnt = 6;
    uint8_t frame[cnt];
    frame[0] = 0x52;        // cmd = RegAddr
    frame[1] = id_HH;       // id_HH
    frame[2] = id_HL;       // id_HL
    frame[3] = id_LH;       // id_LH
    frame[4] = id_LL;       // id_LL
    frame[5] = newAddr;     // newAddr
    gST7580.mBuf_Frames.bufAddFrame( cnt, frame );
  
}// -----------------------------------------------------------


/// ----------------------------------------------------------
/// FRAME GetID
void MST7580::sendTX_GetID( uint8_t addr ){
  
    // --- zmienne --------------------------------------
 
    // --- wysylanie ------------------------------------
    const int cnt = 3;
    uint8_t frame[cnt];
    frame[0] = 0x51;    // cmd = GetID
    frame[1] = addr;    // addr
    frame[2] = 0x52;    // test
    gST7580.mBuf_Frames.bufAddFrame( cnt, frame );

  
}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME unReg
void MST7580::sendTX_hiUnreg( uint8_t gateway ){

    // --- zmienne --------------------------------------

    // --- wysylanie ------------------------------------
	const int cnt = 2;
	uint8_t frame[cnt];
	frame[0] = 0x56;    // cmd = AskStatus
	frame[1] = gateway;

	gST7580.mBuf_Frames.bufAddFrame( cnt, frame );


}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME getStatus
void MST7580::sendTX_getStatus( uint8_t addr, uint8_t gateway ){

    // --- zmienne --------------------------------------

    // --- wysylanie ------------------------------------
	const int cnt = 3;
	uint8_t frame[cnt];
	frame[0] = 0x53;    // cmd = AskStatus
	frame[1] = addr;    // addr
	frame[2] = gateway; // gateway
	gST7580.mBuf_Frames.bufAddFrame( cnt, frame );


}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME setAddr
void MST7580::sendTX_setAddr( uint8_t addr ,uint8_t newAddr ){

    // --- zmienne --------------------------------------

    // --- wysylanie ------------------------------------
	const int cnt = 3;
	uint8_t frame[cnt];
	frame[0] = 0x55;    // cmd = AskStatus
	frame[1] = addr;    // addr
	frame[2] = newAddr;
	gST7580.mBuf_Frames.bufAddFrame( cnt, frame );


}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME setRelays
void MST7580::sendTX_setRelays( uint8_t addr, uint8_t relays  ){

    // --- zmienne --------------------------------------

    // --- wysylanie ------------------------------------
	const int cnt = 3;
	uint8_t frame[cnt];
	frame[0] = 0x54;    // cmd = AskStatus
	frame[1] = addr;    // addr
	frame[2] = relays;
	gST7580.mBuf_Frames.bufAddFrame( cnt, frame );

}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME ToNode set specific address for specific nodes. Triggered from RS485.
void MST7580::sendTX_ToNode_setAddrUnreg( uint8_t newAddr){

    // --- zmienne --------------------------------------

    // --- wysylanie ------------------------------------
	const int cnt = 2;
	uint8_t frame[cnt];
	frame[0] = 0x57;    // cmd = AskStatus
	frame[1] = newAddr;    // newAddr
	gST7580.mBuf_Frames.bufAddFrame( cnt, frame );

}// -----------------------------------------------------------


#endif
/*########################################################################################*/
