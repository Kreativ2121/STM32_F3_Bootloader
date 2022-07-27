#ifndef __M485E_TX_CA529_CPP_H
#define __M485E_TX_CA529_CPP_H

#include "M485_E.h"

/*########################################################################################*/

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

/*########################################################################################*/


#endif
/*########################################################################################*/
