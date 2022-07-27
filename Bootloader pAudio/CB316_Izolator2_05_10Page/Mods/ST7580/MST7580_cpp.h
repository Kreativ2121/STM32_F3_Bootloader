#ifndef __MST7580_BH704_CPP_H
#define __MST7580_BH704_CPP_H


#include "MST7580.h"
#include "ST7580_Library\Src\ST7580_Serial.c"

#include "..\GPIO\MGPIO.h"
#include "..\ADC\MADC.h"

/*########################################################################################*/



//-----------------------------------------------------------------------------
void MST7580::initModem(){
              
  ST7580InterfaceInit();
  
  HAL_Delay(100);
  
  ST7580MibWrite(MIB_MODEM_CONF, modem_config, sizeof(modem_config));
  HAL_Delay(10);
  //ST7580MibWrite(MIB_PHY_CONF, phy_config, sizeof(phy_config));
  ST7580MibWrite(MIB_PHY_CONF, this->modemConf_Phy, sizeof(phy_config));
  HAL_Delay(10);
  
}//----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void MST7580::onTimer_Main10ms(){
  
  // ... ODBIERANIE ..........................................
  RxFrame = ST7580NextIndicationFrame();
  if (RxFrame != NULL){
    if( (RxFrame->stx == ST7580_STX_03) ){ // DUPLICATED
      // duplicated indication frame with STX = 03 is received 
		  RxFrame = NULL;
     }else{ // ODEBRANY KOMUNIKAT
       // uint8_t d0 = RxFrame->data[4];
       int cnt = RxFrame->length - 4;
       uint8_t *frame = &(RxFrame->data[4]);
       
       // ... interpretacja ...
       uint8_t cmd = frame[0];
       switch( cmd ){
          
       // ... GATEWAY ...............
       case 0x20: frameRX_ToGateway_ID(frame);        break;  // Gateway ID
       case 0x21: frameRX_ToGateway_GetID(frame);     break;  // Gateway GetID
       case 0x22: frameRX_ToGateway_RegAddr(frame);   break;  // Gateway RegAddr
       case 0x23: frameRX_ToGateway_getStatus(frame); break;  // Gateway Status
       case 0x24: frameRX_ToGateway_hiFromUnreg(frame); break;  // Gateway hi from unregistered isolator

       // ... NODE ..................                  
       case 0x50: frameRX_ToNode_ID(frame);           break;  // Node ID
       case 0x51: frameRX_ToNode_GetID(frame);        break;  // Node GetID
       case 0x52: frameRX_ToNode_RegAddr(frame);      break;  // fromST.RegAddr
       case 0x53: frameRX_ToNode_getStatus(frame);    break;  // fromST.Status
       case 0x54: frameRX_ToNode_setRelays(frame);    break;  //
       case 0x55: frameRX_ToNode_setAddr(frame);      break;  //
       case 0x56: frameRX_ToNode_hiUnreg(frame);      break;  //
       case 0x57: frameRX_ToNode_setAddrUnreg(frame);      break;  //

       //case 0x5A: frameRX_ToGateway_SendStats(frame);    break;  //
       }
     };
  }

  // ... NADAWANIE ..........................................
  // sprawdz czy w buforze ramka do wyslania
  
  if( mBuf_Frames.isEmpty() == false ){
  
    // pobierz ramke
    int N = mBuf_Frames.getN(); // w pierwszym bajcie liczba danych o wyslania
    uint8_t cnt = mBuf_Frames.popFirst();
    if( cnt > N ){      // blad wielkosci bufora - cos nie tak
      mBuf_Frames.clear(); 
      return;
    }
    
    // przygotuj bufor
    for( int i=0; i<cnt; i++ )   txBuf[i] = mBuf_Frames.popFirst();
    
    // wyslij po modemie
    uint8_t ret = ST7580DlData(DATA_OPT, txBuf, cnt, NULL);
    if( ret != 0 ){
            // ERROR 
    }
    
  }// .......................................................

  
}//----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void MST7580::onTimer_Main100ms(){
	//sendTX_NextID( 0x00 );
	//sendTX_StatusToGateway();
  
  
}//----------------------------------------------------------------------------
void MST7580::onTimer_Main1000ms(){
	//sendTX_NextID( 0x00 );
	//sendTX_StatusToGateway();


}//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void MST7580::onTimer(){


}//----------------------------------------------------------------------------

























//      // --- TX/LED -------------
//      if( mTxCnt >= 2 ){
//        mTxCnt = 0;
//     //   _oLED = 0; 
//        g485E.onTimer_Frame();
//        
//#ifndef _MODEM_OFF      
//          isTX = true;
//#endif      
//
//        
//      }else if( mTxCnt >= 1 ){
//     //   _oLED = 1; 
//        mTxCnt += 1;
//        
//      }else mTxCnt += 1;
//      
//      
//      
//      mModemWDT = (mModemWDT<100) ? (mModemWDT+1) : 100;
//      
//      if( mModemWDT > 20 ){
//        
//        
////        gRelays.setREL_B_safe( false );
////        gRelays.setREL_A_safe( false );
//          
//        gSystem.mPwrSup_Source = EPwrSupSource::NOT_KNOWN;
//        
//      }
//        if( mIsResetReq ){
//          
//          this->modemRESET();
//          mIsResetReq = false;
//          
//              
//          g485E.bufAdd( 0x5A );                   // naglowek
//          g485E.bufAdd( 0xBF );                   // typ ramki
//    
//          g485E.bufAdd( g485E.mMyAddr );                // address
//          
//          
//          g485E.bufAdd( this->modemConf_Phy[0] );  // B[0]
//          g485E.bufAdd( this->modemConf_Phy[1] );  // B[1]
//          g485E.bufAdd( this->modemConf_Phy[2] );  // B[2]
//          g485E.bufAdd( this->modemConf_Phy[3] );  // B[3]
//          g485E.bufAdd( this->modemConf_Phy[4] );  // B[4]
//          g485E.bufAdd( this->modemConf_Phy[5] );  // B[5]
//          g485E.bufAdd( this->modemConf_Phy[6] );  // B[6]
//          g485E.bufAdd( this->modemConf_Phy[7] );  // B[7]
//          g485E.bufAdd( this->modemConf_Phy[8] );  // B[8]
//          g485E.bufAdd( this->modemConf_Phy[9] );  // B[9]
//          g485E.bufAdd( this->modemConf_Phy[10] );  // B[10]
//          g485E.bufAdd( this->modemConf_Phy[11] );  // B[11]
//          g485E.bufAdd( this->modemConf_Phy[12] );  // B[12]
//          g485E.bufAdd( this->modemConf_Phy[13] );  // B[13]
//               
//          g485E.bufAdd( 0xE0 );                     // CRC
//          g485E.bufAdd( 0xE1 );                     // CRC
//          g485E.bufAdd( 0xFF );                     // stopka
//
//          g485E.Send_IT();
//
//          return;
//    
//        }
//  
//        /* Wait ACK Msg sent back from slave */
//             //RxFrame = BSP_PLM_Receive_Frame();
//             RxFrame = ST7580NextIndicationFrame();
//             if (RxFrame != NULL){
//               if( (RxFrame->stx == ST7580_STX_03) )
//               {
//                  // duplicated indication frame with STX = 03 is received 
//		  RxFrame = NULL;
//               //   jjj = 2;
//               }else{
//                  // ODEBRANY KOMUNIKAT
//                    // jjj = 1;
//                  // zapal LED
//                  //d0 = RxFrame->data[4];
//                 
//
//                 
//#ifdef _MODULE_0
//                 
//                 gMod1.mSens0 = (RxFrame->data[5] << 8) | (RxFrame->data[4] << 0);
//                 gMod1.mRelays = RxFrame->data[6];
//                 gMod1.mUA = (RxFrame->data[7] << 8) | (RxFrame->data[8] << 0);
//                 gMod1.mUB = (RxFrame->data[9] << 8) | (RxFrame->data[10] << 0);
//                 gMod1.mIA = (RxFrame->data[11] << 8) | (RxFrame->data[12] << 0);
//                 gMod1.mIB = (RxFrame->data[13] << 8) | (RxFrame->data[14] << 0);
//                 gMod1.mComWDT = 0;             
//#else
//#ifdef _MODULE_1
//
//                // RELAYS 
//                uint8_t rels = RxFrame->data[4];
//       
//                if( rels & 0x01 ) rels &= ~0x02;
//                if( rels & 0x04 ) rels &= ~0x08;
//                if( g485E.mPrevRels != rels ){
//
//                  gRelays.gRelayCnt = 30;
//                  gRelays.gShortDeadCnt = 400;
//                  
//                    _oREL_A_SET   = ( rels & 0x01 )?1:0;
//                    _oREL_A_RESET = ( rels & 0x02 )?1:0;
//                    _oREL_B_SET   = ( rels & 0x04 )?1:0;
//                    _oREL_B_RESET = ( rels & 0x08 )?1:0;
//                    
//                    if( _oREL_A_SET )   gRelays.mRelA_IsON = true;
//                    if( _oREL_A_RESET ) gRelays.mRelA_IsON = false;
//                    if( _oREL_B_SET )   gRelays.mRelB_IsON = true;
//                    if( _oREL_B_RESET ) gRelays.mRelB_IsON = false;
//                    
//                }
//                g485E.mPrevRels = rels;
//
//              // RAMKA POWROTNA
//              txBuf[0] = gADC.mS0 >> 0;      // SENS0
//              txBuf[1] = gADC.mS0 >> 8;
//              
//              uint8_t rels2 = 0x00;
//              if( gRelays.mRelA_IsON ) rels2 |= 0x01;
//              if( gRelays.mRelB_IsON ) rels2 |= 0x04;
//              txBuf[2] = rels2;
//              
//              txBuf[3] =  (gADC.mUA_avr>>8);        // UA linii
//              txBuf[4] =  (gADC.mUA_avr>>0);        // UA linii
//              txBuf[5] =  (gADC.mUB_avr>>8);        // UB linii
//              txBuf[6] =  (gADC.mUB_avr>>0);        // UB linii
//           
//              txBuf[7] =  (gADC.mIAabs_avr>>8);     // IA linii
//              txBuf[8] =  (gADC.mIAabs_avr>>0);     // IA linii
//              txBuf[9] =  (gADC.mIAabs_avr>>8);     // IB linii
//              txBuf[10] = (gADC.mIAabs_avr>>0);     // IB linii
//              
//              mModemWDT = 0;    // RESET MODEM WDT
//              /*
//              txBuf[0] = gADC.adcValue[0] >> 0;      // SENS0
//              txBuf[1] = gADC.adcValue[0] >> 8;
//              
//              uint8_t rels2 = 0x00;
//              if( g485E.mRelA_IsON ) rels2 |= 0x01;
//              if( g485E.mRelB_IsON ) rels2 |= 0x04;
//              txBuf[2] = rels2;
//              
//              txBuf[3] = (gADC.adcValue[1]>>8);        // UA linii
//              txBuf[4] = (gADC.adcValue[1]>>0);        // UA linii
//              txBuf[5] = (gADC.adcValue[2]>>8);        // UB linii
//              txBuf[6] = (gADC.adcValue[2]>>0);        // UB linii
//           
//              txBuf[7] = (gADC.adcValue[3]>>8);        // IA linii
//              txBuf[8] = (gADC.adcValue[3]>>0);        // IA linii
//              txBuf[9] = (gADC.adcValue[4]>>8);        // IB linii
//              txBuf[10] = (gADC.adcValue[4]>>0);        // IB linii
//
//              */
//           
//           
//      
//             uint8_t ret = ST7580DlData(DATA_OPT, txBuf, 11, NULL);
//             if( ret != 0 ){
//                    // ERROR 
//             }
//             
//           
//#endif                 
//#endif
//                  //jjj = 2;
//                 
//           // !!!      if( d0 != 0 ) BSP_LED_On(0);
//           // !!!      else BSP_LED_Off(0);
//                 
//
//  public: uint16_t  mRelays = 21;
//  public: uint16_t  mSens0 = 22;
//  public: uint16_t  mSens1 = 23;
//  public: uint16_t  mUA = 24;
//  public: uint16_t  mUB = 25;
//  public: uint16_t  mIA = 26;
//  public: uint16_t  mIB = 27;  
//        */         
//	        }
//	     }	
//    
//#ifdef _MODULE_0
//             
//        if( isTX ){
//             /* txBuf[0] = adcValue[0] >> 0;      // SENS0
//              txBuf[1] = adcValue[0] >> 8;
//              
//              uint8_t rels2 = 0x00;
//              if( g485E.mRelA_IsON ) rels2 |= 0x01;
//              if( g485E.mRelB_IsON ) rels2 |= 0x04;
//              txBuf[2] = rels2;
//              
//              txBuf[3] = (adcValue[1]>>8);        // UA linii
//              txBuf[4] = (adcValue[1]>>0);        // UA linii
//              txBuf[5] = (adcValue[2]>>8);        // UB linii
//              txBuf[6] = (adcValue[2]>>0);        // UB linii
//           
//              txBuf[7] = (adcValue[3]>>8);        // IA linii
//              txBuf[8] = (adcValue[3]>>0);        // IA linii
//              txBuf[9] = (adcValue[4]>>8);        // IB linii
//              txBuf[10] = (adcValue[4]>>0);        // IB linii
//           */
//           
//              txBuf[0] = gMod1.mRelaysOut;      // Relays
//      
//             uint8_t ret = ST7580DlData(DATA_OPT, txBuf, 1, NULL);
//             if( ret != 0 ){
//                    // ERROR 
//             }
//             
//             isTX = false;
//             
//       
//             
//        }
//             
//#else
//
//
//#endif


/*########################################################################################*/


#endif
/*########################################################################################*/
