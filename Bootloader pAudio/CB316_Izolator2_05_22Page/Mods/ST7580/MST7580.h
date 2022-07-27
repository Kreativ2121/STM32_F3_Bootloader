#ifndef __MST7580_BH704_H
#define __MST7580_BH704_H


#include "ST7580_Library\Inc\ST7580_Serial.h"

#include <cstdint>

#include "../Struct/MBufCircular.h"  
#include "..\GPIO\MGPIO.h"

/*########################################################################################*/
/******************** KLASY ***************************************************************/      

// konfiguracja IO na zewnatrz: UART + ResetN + Treq

#define PLM_GPIO_T_REQ_PORT2                         GPIOA
#define PLM_GPIO_T_REQ_PIN2                          GPIO_PIN_0

#define PLM_GPIO_RESETN_PORT                        GPIOC
#define PLM_GPIO_RESETN_PIN                        GPIO_PIN_14



//uint16_t gTXBuf_Index = 0;
//uint8_t gTXBuf[100];
//uint8_t gTXStep[100];


void debTXBuf_add(uint8_t aCh, uint8_t aStep){
  
//  gTXBuf[ gTXBuf_Index ] = aCh;
//  gTXStep[ gTXBuf_Index ] = aStep;
  
//  gTXBuf_Index = gTXBuf_Index + 1;
//  if( gTXBuf_Index >= 100 ) gTXBuf_Index = 0;
    
}//---------------------------------------------------------------------------


  class MST7580{

    //+++ POLA ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public: MBufCircular mBuf_Frames;           // bufor ramek
    
    
    public: UART_HandleTypeDef *mhUart;  // handle
    public: uint8_t mRXBuf[1];            // bufor do odbioru przez HW UART

    public: uint8_t mTXBuf[10];            // bufor do odbioru przez HW UART
    
    
    public: uint8_t mTxCnt;             // Counter do TX - co 300 ms
    
    public: uint16_t mModemWDT = 0;   
    
    public: ST7580Frame* RxFrame;
    
    public: uint8_t txBuf[10] = { 0,0,0,0,0,0,0,0,0,0 };

    public: bool isTX = false;
    
    /// MECHANIZM NIE DZIALA, mial byc do ramki frameRX_Config() w M485_E_cpp_RX.h
    //public: bool  mIsResetReq = false;  // reset modemu w main, ustawia ktos gdy chce zresetowac
    
    
    //+++ METODY +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // --------- KONFIGURACJA ----------------------------
  
    /// inicjalizacja UARTA
  public: void init( UART_HandleTypeDef *aUart ){
      mhUart = aUart;
      HAL_UART_Receive_IT( mhUart, mRXBuf, 1 );
      
     // if( !mIsResetReq ) 
        for( int i=0; i<14; i++ )   modemConf_Phy[i] = phy_config[i];
  }
  
  public: void initModem(); 

    /// event: TIMER    
    public: void onTimer();     // puste
    
    /// event: TIMER_Main10ms
    public: void onTimer_Main10ms();    // czy ramka
    
    /// event: TIMER_Main100ms
    public: void onTimer_Main100ms();   // TX + LED
    
    /// event: TIMER_Main1000ms
    public: void onTimer_Main1000ms();   // STATUS

    public: void frameRX_ToNode_ID(uint8_t *frame);           /// FRAME ID 
    public: void frameRX_ToNode_GetID(uint8_t *frame);        /// FRAME GetID
    public: void frameRX_ToNode_RegAddr(uint8_t *frame);      /// FRAME Reg_Addr
    //public: void frameRX_ToNode_AskStatus(uint8_t *frame);    /// FRAME AskStatus
    public: void frameRX_ToNode_getStatus(uint8_t *frame);    /// FRAME getStatus
    public: void frameRX_ToNode_Ext(uint8_t *frame);          /// FRAME Ext
    public: void frameRX_ToNode_setRelays(uint8_t *frame);    /// FRAME setRelays
    public: void frameRX_ToNode_setAddr(uint8_t *frame);    /// FRAME setRelays

    public: void frameRX_ToGateway_ID(uint8_t *frame);        /// FRAME ID 
    public: void frameRX_ToGateway_GetID(uint8_t *frame);     /// FRAME GetID
    public: void frameRX_ToGateway_RegAddr(uint8_t *frame);   /// FRAME Reg_Addr
    //public: void frameRX_ToGateway_AskStatus(uint8_t *frame); /// FRAME AskStatus
    public: void frameRX_ToGateway_getStatus(uint8_t *frame); /// FRAME getStatus
    public: void frameRX_ToGateway_Ext(uint8_t *frame);       /// FRAME Ext
    public: void frameRX_ToGateway_hiFromUnreg(uint8_t *frame);
    public: void frameRX_ToNode_hiUnreg(uint8_t *frame);
    public: void frameRX_ToNode_setAddrUnreg(uint8_t *frame);

    public: void sendTX_ID( uint8_t aParam );
    public: void sendTX_NextID( uint8_t aParam );
    public: void sendTX_StatusToGateway();
    public: void sendTX_RegAddr( uint32_t id,  uint8_t newAddr );
    public: void sendTX_AskStatus( uint8_t addr, uint8_t relays );
    public: void sendTX_GetID( uint8_t addr );
    public: void sendTX_setAddr( uint8_t addr ,uint8_t newAddr);
    public: void sendTX_getStatus( uint8_t addr, uint8_t gateway );
    public: void sendTX_setRelays( uint8_t addr, uint8_t relays );
    public: void sendTX_hiUnreg( uint8_t gateway );
    public: void sendTX_ToNode_setAddrUnreg(uint8_t addr);
    
    /// ------------------------------------------------------------------------
    /// w przerwaniu RX
    public: void onIT_RX(){
        //  if( _o485E_EN == 0 ) 
   //   onReceive( mRXBuf[0] );
      NucleoST7580RxInt( mRXBuf[0] );
      HAL_UART_Receive_IT(  mhUart, mRXBuf, 1 );
    }//-------------------------------------------------------------------------
    
    
    /// ------------------------------------------------------------------------
    /// w przerwaniu TX
    public: void onIT_TX(){
      //  mTXBuf[0] = 0x12;
        NucleoST7580TxInt( /*mhUart*/ );
         //    HAL_StatusTypeDef uartRes = HAL_UART_Transmit_IT( mhUart, buf,  cnt );
    }//-------------------------------------------------------------------------
    
    public: uint8_t modemConf_Phy[14];
    
    

    
    
    /// ------------------------------------------------------------------------
    /// RESET
    public: void modemRESET(){
      
      __disable_irq();
      this->pinTREQ( 1 ) ;
      this->pinRESETN( 1 );
      this->init( &huart2 );
      
      __enable_irq();
      this->initModem();  
      
      
    }//-------------------------------------------------------------------------
    
    
  //+++ OBSLUGA PINOW DLA EXT.DRIVER +++++++++++++++++++++++++++++++++++
    
    public: void pinRESETN( int aPinState /*GPIO_PinState aPinState*/ ){
        HAL_GPIO_WritePin(PLM_GPIO_RESETN_PORT,PLM_GPIO_RESETN_PIN, (GPIO_PinState)aPinState );
    }//-------------------------------------------------------------------------
    
    public: void pinTREQ( int aPinState /*GPIO_PinState aPinState*/ ){
        HAL_GPIO_WritePin(PLM_GPIO_T_REQ_PORT2,PLM_GPIO_T_REQ_PIN2, (GPIO_PinState)aPinState );
    }//-------------------------------------------------------------------------
    
    public: void enableTX_IRQ(){
       // __HAL_UART_ENABLE_IT(mhUart,UART_IT_TXE);	// !!!!	
      NucleoST7580TxInt();
    }//-------------------------------------------------------------------------
    
    public: void disableTX_IRQ(){
        //__HAL_UART_DISABLE_IT(mhUart,UART_IT_TXE);	// !!!!	
    }//-------------------------------------------------------------------------
    
    
    public: void sendUART8( uint8_t aCh, uint8_t aStep ){
        mTXBuf[0] = aCh;
        HAL_StatusTypeDef uartRes = HAL_UART_Transmit_IT( mhUart, mTXBuf,  1 );
        
        debTXBuf_add( aCh, aStep );
        
    }//-------------------------------------------------------------------------
    
      
    };//************************************************************************************



    MST7580 gST7580;


/*########################################################################################*/
/******************** METODY **************************************************************/      





#endif
/*########################################################################################*/
