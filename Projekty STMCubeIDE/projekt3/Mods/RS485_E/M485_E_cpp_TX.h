#ifndef __M485E_TX_CA529_CPP_H
#define __M485E_TX_CA529_CPP_H

#include "M485_E.h"

/*########################################################################################*/

///// ----------------------------------------------------------
//// FRAME REACT TEST
//void M485E::sendTX_React( uint8_t lo, uint8_t hi){
//
//   g485E.bufAdd( 0x5A );
//   g485E.bufAdd( hi );
//   g485E.bufAdd( lo );
//
//   g485E.bufAdd( 0xE0 );          // CRC.H
//   g485E.bufAdd( 0xE1 );          // CRC.L
//   g485E.bufAdd( 0xFF );
//
//   this->Send_IT();
//
//}// -----------------------------------------------------------

///// ----------------------------------------------------------
//// FRAME ReadPageOLD
//void M485E::sendTX_ReadPage( uint8_t pg, uint8_t OH, uint8_t OL){
//	uint16_t offset = OH << 8 | OL;
//	uint16_t pageData = MFlash::read16(pg,offset);
//	uint8_t lo=pageData&(0xff);
//	uint8_t hi=(pageData>>8) & 0xff;
//
//
//	g485E.bufAdd( 0x5A );
//	g485E.bufAdd( 0x00 );
//	g485E.bufAdd( hi );
//	g485E.bufAdd( lo );
//	g485E.bufAdd( 0xE0 );          // CRC.H
//	g485E.bufAdd( 0xE1 );          // CRC.L
//	g485E.bufAdd( 0xFF );
//	this->Send_IT();
//
//}// -----------------------------------------------------------

/// ----------------------------------------------------------
// FRAME ReadPage
void M485E::sendTX_ReadPage( uint8_t pg, uint8_t OH, uint8_t OL){
	uint16_t offset = OH << 8 | OL;
	uint32_t pageData = MFlash::read32(pg,offset);
	uint8_t ll=pageData&(0xff);
	uint8_t lh=(pageData>>8) & 0xff;
	uint8_t hl=(pageData>>16) & 0xff;
	uint8_t hh=(pageData>>24) & 0xff;


	g485E.bufAdd( 0x5A );
	g485E.bufAdd( 0x00 );
	g485E.bufAdd( hh );
	g485E.bufAdd( hl );
	g485E.bufAdd( lh );
	g485E.bufAdd( ll );
	g485E.bufAdd( 0xE0 );          // CRC.H
	g485E.bufAdd( 0xE1 );          // CRC.L
	g485E.bufAdd( 0xFF );
	this->Send_IT();

}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME STATUS (pram: typ ramki)
//void M485E::sendTX_STATUS( uint8_t gateway ){
//
//    // --- zmienne --------------------------------------
//    uint8_t rels2 = 0x00;
//    if( gRelays.mRelA_IsON ) rels2 |= 0x01;
//    if( gRelays.mRelB_IsON ) rels2 |= 0x04;
//    uint8_t status = 0x01;
//
//    // --- wysylanie ------------------------------------
//
//    this->bufAdd( 0x5A );                   // naglowek
//    this->bufAdd( 0x42 );                   // typ ramki
//
//    this->bufAdd( gateway );                // gateway
//    this->bufAdd( mMyAddr );                // address
//    this->bufAdd( status );                 // Status
//    this->bufAdd( rels2 );                  // Relays
//
//    this->bufAdd( gADC.mS0 );               // Prad sens 1
//    this->bufAdd( gADC.mS0 );               // Prad sens 2
//    this->bufAdd( (gADC.mUA_avr>>8) );      // UA linii
//    this->bufAdd( (gADC.mUA_avr>>0) );      // UA linii
//    this->bufAdd( (gADC.mUB_avr>>8) );      // UB linii
//    this->bufAdd( (gADC.mUB_avr>>0) );      // UB linii
//
//    this->bufAdd( (gADC.mIAabs_avr>>8) );     // IA linii
//    this->bufAdd( (gADC.mIAabs_avr>>0) );     // IA linii
//    this->bufAdd( (gADC.mIBabs_avr>>8) );     // IB linii
//    this->bufAdd( (gADC.mIBabs_avr>>0) );     // IB linii
////    this->bufAdd( (gRelays.mShortCnt>>8) );    // DEBUG
////    this->bufAdd( (gRelays.mShortCnt>>0) );    // DEBUG
//
//
//    this->bufAdd( 0xE0 );                     // CRC
//    this->bufAdd( 0xE1 );                     // CRC
//    this->bufAdd( 0xFF );                     // stopka
//
//    this->Send_IT();
//
//}// -----------------------------------------------------------




/// ----------------------------------------------------------
/// FRAME ADDR (pram: stary addr)
//void M485E::sendTX_ADDR( uint8_t aPrevAddr ){
//
//    // --- zmienne --------------------------------------
//    uint8_t addr     = mMyAddr;
//    uint8_t prevAddr = aPrevAddr;
//
//    // --- wysylanie ------------------------------------
//    this->bufAdd( 0x5A );                   // naglowek
//    this->bufAdd( 0xBC );                   // typ ramki
//
//    this->bufAdd( prevAddr );                // address
//    this->bufAdd( addr );                    // Status
//
//    this->bufAdd( 0xE0 );                    // CRC
//    this->bufAdd( 0xE1 );                    // CRC
//    this->bufAdd( 0xFF );                    // stopka
//
//    this->Send_IT();
//
//}// -----------------------------------------------------------


/// ----------------------------------------------------------
/// FRAME EXT
//void M485E::sendTX_EXT( uint8_t cnt, uint8_t *frame ){
//
//   g485E.bufAdd( 0x5A );
//   g485E.bufAdd( 0x51 );          // EXT
//   g485E.bufAdd( g485E.mMyAddr ); // Gateway
//
//   g485E.bufAdd( cnt );           // cnt
//   for( int i=0; i<cnt; i++ ) g485E.bufAdd( frame[i] );
//
//   g485E.bufAdd( 0xE0 );          // CRC.H
//   g485E.bufAdd( 0xE1 );          // CRC.L
//   g485E.bufAdd( 0xFF );
//
//}// -----------------------------------------------------------



  
/// ----------------------------------------------------------
/// FRAME ID
//void M485E::sendTX_ID( uint8_t gateway ){
//
//    // --- zmienne --------------------------------------
//    uint8_t id_HH    = uint8_t( (gSystem.mID >> 24) & 0xFF );
//    uint8_t id_HL    = uint8_t( (gSystem.mID >> 16) & 0xFF );
//    uint8_t id_LH    = uint8_t( (gSystem.mID >>  8) & 0xFF );
//    uint8_t id_LL    = uint8_t( (gSystem.mID >>  0) & 0xFF );
//    uint8_t status   = 0x01;
//
//    // --- wysylanie ------------------------------------
//    this->bufAdd( 0x5A );
//    this->bufAdd( 0x5B );       // typ ramki  ID
//
//    this->bufAdd( gateway );    // gateway
//    this->bufAdd( id_HH );      // id
//    this->bufAdd( id_HL );      // id
//    this->bufAdd( id_LH );      // id
//    this->bufAdd( id_LL );      // id
//    this->bufAdd( status );     // status
//
//    this->bufAdd( 0xE0 );       // CRC.H
//    this->bufAdd( 0xE1 );       // CRC.L
//    this->bufAdd( 0xFF );
//
//    this->Send_IT();
//
//}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME ID
//void M485E::sendTX_Counter( uint8_t gateway, int nr ){
//
//    // --- zmienne --------------------------------------
//
//    // --- wysylanie ------------------------------------
//    this->bufAdd( 0x5A );
//    this->bufAdd( 0x6A );       // typ ramki  ID
//
//    this->bufAdd( gateway );    // gateway
//    this->bufAdd( nr );			// number
//    this->bufAdd( 0x00 );		// stuffing bytes
//    this->bufAdd( 0x00 );		// stuffing bytes
//    this->bufAdd( 0x00 );		// stuffing bytes
//    this->bufAdd( 0x00 );		// stuffing bytes
//    this->bufAdd( 0xE0 );       // CRC.H
//    this->bufAdd( 0xE1 );       // CRC.L
//    this->bufAdd( 0xFF );
//
//    this->Send_IT();
//
//}// -----------------------------------------------------------

/// ----------------------------------------------------------
/// FRAME ID
//void M485E::sendTX_GetID( uint8_t gateway ){
//
//    // --- zmienne --------------------------------------
//    uint8_t id_HH    = uint8_t( (gSystem.mID >> 24) & 0xFF );
//    uint8_t id_HL    = uint8_t( (gSystem.mID >> 16) & 0xFF );
//    uint8_t id_LH    = uint8_t( (gSystem.mID >>  8) & 0xFF );
//    uint8_t id_LL    = uint8_t( (gSystem.mID >>  0) & 0xFF );
//    uint8_t status   = 0x01;
//    uint8_t addr     = mMyAddr;
//
//    uint8_t rels2 = 0x00;
//    if( gRelays.mRelA_IsON ) rels2 |= 0x01;
//    if( gRelays.mRelB_IsON ) rels2 |= 0x04;
//
//    // --- wysylanie ------------------------------------
//    this->bufAdd( 0x5A );
//    this->bufAdd( 0x5C );       // typ ramki GetID
//
//    this->bufAdd( gateway );    // gateway
//    this->bufAdd( addr );       // addr
//    this->bufAdd( status );     // status
//    this->bufAdd( rels2 );      // rels
//
//    this->bufAdd( id_HH );      // id
//    this->bufAdd( id_HL );      // id
//    this->bufAdd( id_LH );      // id
//    this->bufAdd( id_LL );      // id
//
//    this->bufAdd( 0xE0 );       // CRC.H
//    this->bufAdd( 0xE1 );       // CRC.L
//    this->bufAdd( 0xFF );
//
//    this->Send_IT();
//
//}// -----------------------------------------------------------



// ----------------------------------------------------------
/// FRAME RegAddr
//void M485E::sendTX_RegAddr( uint8_t gateway ){
//
//    // --- zmienne --------------------------------------
//    uint8_t addr     = mMyAddr;
//    uint8_t id_HH    = uint8_t( (gSystem.mID >> 24) & 0xFF );
//    uint8_t id_HL    = uint8_t( (gSystem.mID >> 16) & 0xFF );
//    uint8_t id_LH    = uint8_t( (gSystem.mID >>  8) & 0xFF );
//    uint8_t id_LL    = uint8_t( (gSystem.mID >>  0) & 0xFF );
//    uint8_t status   = 0x01;
//
//    uint8_t rels2 = 0x00;
//    if( gRelays.mRelA_IsON ) rels2 |= 0x01;
//    if( gRelays.mRelB_IsON ) rels2 |= 0x04;
//
//    // --- wysylanie ------------------------------------
//    this->bufAdd( 0x5A );
//    this->bufAdd( 0x5D );       // typ ramki  RegAddr
//
//    this->bufAdd( gateway );    // gateway
//    this->bufAdd( addr );       // addr
//    this->bufAdd( id_HH );      // id
//    this->bufAdd( id_HL );      // id
//    this->bufAdd( id_LH );      // id
//    this->bufAdd( id_LL );      // id
//    this->bufAdd( status );     // status
//    this->bufAdd( rels2 );      // relays
//
//    this->bufAdd( 0xE0 );       // CRC.H
//    this->bufAdd( 0xE1 );       // CRC.L
//    this->bufAdd( 0xFF );
//
//    this->Send_IT();
//
//}// -----------------------------------------------------------


/*########################################################################################*/


#endif
/*########################################################################################*/
