#ifndef __M485E_CA529_CPP_H
#define __M485E_CA529_CPP_H


/*########################################################################################*/


void M485E::onReceive( uint8_t aCh ){

  //  ITM_EVENT8( 4, aCh );

INTTOPC_PROC_LABEL:
    switch( mRecState ){
      // ------------------------------------------------
     case 0:
  	if( aCh == 0xA5 ){
	    mRecState += 3;
        }
        break;

  /*   case 1:
  	if( aCh == 0xC3 ){
	    mRecState += 1;
            mRXFrameByteCnt = 0;
        }else{
            mRecState = 0;
            goto INTTOPC_PROC_LABEL;
        }; break;

     case 2:  // address
  	mRXFrameBuf[0] = aCh;
	mRecState += 1;
        break;
*/
    case 3:  // przekazniki
  	mRXFrameBuf[1] = aCh;
	//mRecState += 1;
        mRecState = 7;

        break;
/*
    case 4:  // przekazniki EXT out
  	mRXFrameBuf[2] = aCh;
	mRecState += 1;
        break;


    case 5:  // E0
  	mRXFrameBuf[3] = aCh;
	mRecState += 1;
        break;

    case 6:  // E1
  	mRXFrameBuf[4] = aCh;
	mRecState += 1;
        break;
        */

     case 7:
      //  if( mRXFrameBuf[4] == 0xE1 )
      //  if( mRXFrameBuf[3] == 0xE0 )
  	if( aCh == 0xEE ){

          uint8_t addr = mRXFrameBuf[0];
       /*   if( addr == 0x00 ){

          }else if( addr == 0x01 )*/
          if( 1 )
          {

             uint8_t rels = mRXFrameBuf[1];

             if( rels & 0x01 ) rels &= ~0x02;
             if( rels & 0x04 ) rels &= ~0x08;
             if( mPrevRels != rels ){

              gRelays.gRelayCnt = 30;
              gRelays.gShortDeadCnt = 50;

                _oREL_A_SET   = ( rels & 0x01 )?1:0;
                _oREL_A_RESET = ( rels & 0x02 )?1:0;
                _oREL_B_SET   = ( rels & 0x04 )?1:0;
                _oREL_B_RESET = ( rels & 0x08 )?1:0;

                if( _oREL_A_SET )   gRelays.mRelA_IsON = true;
                if( _oREL_A_RESET ) gRelays.mRelA_IsON = false;
                if( _oREL_B_SET )   gRelays.mRelB_IsON = true;
                if( _oREL_B_RESET ) gRelays.mRelB_IsON = false;
           }

           /*

               this->bufAdd( 0xA5 );
               this->bufAdd( 0xE0 );
               this->bufAdd( 0xE1 );

               this->bufAdd( 0xFF );
               this->Send_IT();*/

         }else{


          }



        }
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
       mFrameTimeOutCnt = 10; // 1s, co 100ms w onTimer

 /*   uint16_t wrt = (mRecState<<8) | (aCh<<0);*/



}//-------------------------------------------------------------------------




     /// event: TIMER
void M485E::onTimer_Frame(){

 //    ITM_EVENT8(1, 12);



     this->bufAdd( 0xA0 );

//     this->bufAdd( 0x01 );  // UA linii
//     this->bufAdd( 0x02 );  // IA linii
//     this->bufAdd( 0x03 );  // UB linii
//     this->bufAdd( 0x04 );  // IB linii

     this->bufAdd( (gADC.mUA_avr>>4)    );  // UA linii
     this->bufAdd( (gADC.mIAabs_avr>>1) );  // IA linii
     this->bufAdd( (gADC.mUB_avr>>4)    );  // UB linii
     this->bufAdd( (gADC.mIBabs_avr>>1) );  // IB linii

     this->bufAdd( 0xE0 );
     this->bufAdd( 0xFF );
     this->bufAdd( 0xFF );
     this->Send_IT();

}//-------------------------------------------------------------------------



/*########################################################################################*/


#endif
/*########################################################################################*/
