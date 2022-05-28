#ifndef __M485E_CA529_H
#define __M485E_CA529_H

#include <cstdint>

#include "..\GPIO\MGPIO.h"

/*########################################################################################*/
/******************** KLASY ***************************************************************/      

  

  class M485E{

    enum frameType: uint8_t {STATUS=0xB0, RELAYS=0xB1, EXT =0xB5, ADDR=0xBC, CONFIG=0xBF, OLD=0xC3};
    
    //+++ POLA ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public: UART_HandleTypeDef *mhUart;  // handle

    
    
    public: uint8_t mTX_WDT = 0;        // WDT do wysylania, do resetowania linii EN
    
    static const uint8_t cBufLength = 50;    
    
    public: uint8_t mBuf[cBufLength];   // bufor kolowy
    public: uint8_t mIndexSTART = 0;    // pierwszy zajety (pusty buf jesli == Stop )
    public: uint8_t mIndexSTOP  = 0;    // pierwszy wolnys

    public: int mSendingTXCnt = 0;
    
    public: int mRecState = 0;          // do maszyny stanow odbioru - nr stanu
    public: int mFrameTimeOutCnt = 0;   // do maszyny stanow odbioru - timeout
    public: uint16_t mCRC = 0;
    
    public: uint8_t mRXBuf[2];            // bufor do odbioru przez HW UART
      
    public: bool  mIsFrameReady2Parse = false;  // ramka gotowa do parsowania o onMain
    public: uint8_t mRXFrameBuf[30];     // tymczasowy bufor do odbioru ramek
    public: uint8_t mRXFrameByteCnt;     // liczba bitow danych w ramce RX o zmiennej dl.
    
    public: uint8_t mPrevRels;          // do ustalania deadCounter
    public: int count = 0;				// do funkcji liczacej
    
    public: uint8_t mMyAddr = _MODULE_ADDR;
    public: uint8_t loopNr = _LOOP_NR;
    
    //+++ METODY +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    
    // --------- KONFIGURACJA ----------------------------

    /// inicjalizacja
    public: void init( UART_HandleTypeDef *aUart ){
      
      mhUart = aUart;
      HAL_UART_Receive_IT( mhUart, mRXBuf, 1 );
      
    }//-------------------------------------------------------------------------
    
    
    /// event: TIMER    
    public: void onTimer(){
    }//-------------------------------------------------------------------------
    
    
    public: void onTimer_Main10ms(){
    
      if( _o485E_EN == 1 ){
        
        if( mTX_WDT > 20 ){
          _o485E_EN = 0;
        }else mTX_WDT += 1;
        
      }else mTX_WDT = 0;
      
     // ... Resetowanie maszyny stanow RX - TIMEOUT ..............
     if( mRecState != 0 ){
       if( mFrameTimeOutCnt > 0 ){
         mFrameTimeOutCnt -=1;
         if( mFrameTimeOutCnt == 0 ){
            mRecState = 0;
         }
       }
     }
  
    }//-------------------------------------------------------------------------

    public: void onTimer_Main100ms(){


       }//-------------------------------------------------------------------------
    
    public: void onTimer_Frame();
      
      
        /// event: MAIN - analizowanie ramki
    public: void onMain(){
    
     
  
    }//-------------------------------------------------------------------------
    
    //--------------------------------------------------------------------------
    public: void onReceive( uint8_t aCh );
    
    public: void frameRX_ID();            /// FRAME ID          0x5B
    public: void frameRX_Ext();           /// FRAME Ext         0x61
    public: void frameRX_GetID();         /// FRAME GetID       0x5C
    public: void frameRX_RegAddr();       /// FRAME Reg_Addr    0xBC
    public: void frameRX_AskStatus();     /// FRAME AskStatus   0xC3
    public: void frameRX_Config();        /// FRAME CONFIG      0xBF
    public: void frameRX_unReg();         /// FRAME UNREG       0x
    public: void frameRX_getStatus();     /// FRAME getStatus   0x
    public: void frameRX_setAddr();       /// FRAME setAddr     0x
    public: void frameRX_setRelays();     /// FRAME setRelays   0x
    public: void frameRX_setAddrUnreg();  /// FRAME setAddrUnreg   0xC7
    public: void frameRX_ReceiveMsg();	  /// ADDITIONAL FRAME - STILL NOT USED
    public: void frameRX_readFlash();
        
    public: void sendTX_STATUS(  uint8_t gateway );
    public: void sendTX_ADDR(   uint8_t aPrevAddr );
    public: void sendTX_ID( uint8_t gateway );
    public: void sendTX_Counter( uint8_t gateway , int counter);
    public: void sendTX_GetID( uint8_t gateway );
    public: void sendTX_RegAddr( uint8_t gateway );
    public: void sendTX_setAddr( uint8_t addr, uint8_t newAddr);
    
    public: void sendTX_EXT( uint8_t cnt, uint8_t *frame );
  
    //--------------------------------------------------------------------------
    public: void Send_IT(){
      uint8_t *buf;
      int cnt = 0;
      // sprawdz czy jakiekolwiek dane czekaja
      bool res = bufPrepareTX( &buf, &cnt );
      if( res ){
        
          //HAL_GPIO_WritePin( GPIOA, GPIO_PIN_12, GPIO_PIN_SET );
     //     ITM_EVENT8( 3, 1 );
          _o485E_EN = 1;
          HAL_StatusTypeDef uartRes = HAL_UART_Transmit_IT( mhUart, buf,  cnt );
          // sprawdz czy udalo sie wyslac
          
           mIsEN_to_0 += cnt;
     //      for( int i=0; i<cnt; i++ )
      //          ITM_EVENT8( 1, buf[i] );
          
          if( uartRes == HAL_OK ){   
            mSendingTXCnt = cnt;
          }
      }    
    }//-------------------------------------------------------------------------
    
    

    public: uint8_t mFrameModAddr = 1;
    
    /// ------------------------------------------------------------------------
 //   public: void onTimer_Frame();
           
    uint8_t mIsEN_to_0 = 0;
    /// ------------------------------------------------------------------------
    /// w przerwaniu TX
    public: void onIT_TX(){
      // wyczysc bufor
      
      
      //ITM_EVENT8( 2, mIsEN_to_0 );
      if( mIsEN_to_0 != 0 ){
        // ITM_EVENT8( 2, mIsEN_to_0 );
        mIsEN_to_0 = 0;
      }
      
      
      bufRemoveN(  mhUart->TxXferSize );

        
      //send_IT - skopiowane
      {
         uint8_t *buf;
         int cnt = 0;
         // sprawdz czy jakiekolwiek dane czekaja
         bool res = bufPrepareTX( &buf, &cnt );
         if( res ){
             // HAL_GPIO_WritePin( GPIOA, GPIO_PIN_12, GPIO_PIN_SET );
           //  ITM_EVENT8( 3, 2 );
             _o485E_EN = 1;
             HAL_StatusTypeDef uartRes = HAL_UART_Transmit_IT( mhUart, buf,  cnt );
             mIsEN_to_0 += cnt;
             

             
          //   for( int i=0; i<cnt; i++ )
          //      ITM_EVENT8( 1, buf[i] );
             // sprawdz czy udalo sie wyslac
             if( uartRes == HAL_OK ){   
               mSendingTXCnt = cnt;
             }
          }else{
             //HAL_GPIO_WritePin( GPIOA, GPIO_PIN_12, GPIO_PIN_RESET );
             //_o485E_EN = 0;
             //mIsEN_to_0 = 4;
                       
          }
      }    
      
       if( mIsEN_to_0 <= 0 ){
          
          if( isEmpty() ){
          
            //mIsEN_to_0 = false;
            
         //   ITM_EVENT8( 3, 0 );
            _o485E_EN = 0;
          }
       }
          
      //ITM_EVENT8( 2, mIsEN_to_0 );
    
    }//-------------------------------------------------------------------------
    
    /// ------------------------------------------------------------------------
    /// w przerwaniu RX
    public: void onIT_RX(){
      
   //     ITM_EVENT8( 1, mIsEN_to_0 );
  //    ITM_EVENT8( 2, mRXBuf[0] );
  //    ITM_EVENT8( 1, mIsEN_to_0 );
      


//        #ifndef _USART_PC
//          if( _o485E_EN == 0 ) 
//        #endif
        
          if( _o485E_EN == 0 ){
   //         ITM_EVENT8( 4, mRXBuf[0] );
            onReceive( mRXBuf[0] );
          }else{
  //          ITM_EVENT8( 4, mRXBuf[0] );
          }
        
        if( mIsEN_to_0 <= 0 ){
          
          if( isEmpty() ){
          
            //mIsEN_to_0 = false;
            
    //        ITM_EVENT8( 3, 0 );
            _o485E_EN = 0;
          }
          
          
        }else{
          //ITM_EVENT8( 3, mIsEN_to_0 );
          mIsEN_to_0 -= 1;
        }
        
        

      
//      if( mIsEN_to_0 <= 0 ){
//          mIsEN_to_0 = false;
//          _o485E_EN = 0;
//      }else{
//        //ITM_EVENT8( 3, mIsEN_to_0 );
//        mIsEN_to_0 -= 1;
//      }
      HAL_UART_Receive_IT(  mhUart, mRXBuf, 1 );
    }//-------------------------------------------------------------------------
    
    
    
    
    
    
    
    /// CRC - ala Daniel
    //obliczanie crc
    //wejscie: crc - aktualne crc
    //	     b - nowy znak
    //wyjscie: uaktualnione crc
    uint16_t AddCrc(uint16_t crc,uint8_t b)
    {
        uint8_t i;
        uint16_t c;

        c = ((crc >> 8) ^ b) << 8;
        i = 0;
        do
        {
          if ((c & 0x8000) > 0 )
            c = (c << 1) ^ 0x1021;	//tak
          else
            c = c << 1;                         //nie
        }while(++i < 8);
        crc =  c ^ ((crc) << 8);
        return crc;
    }//-------------------------------------------------------------------------

    
    // odczytaj ze szczytu bufora i oblicz CRC
    inline void crcRX(){
      
      int ind = mIndexSTOP-1;
      if( ind < 0 ) ind += cBufLength;
      
      uint8_t ch = mBuf[ind];
      
      
      mCRC = AddCrc( mCRC, ch );
      
    }//-------------------------------------------------------------------------
    
    
    
    
    
    
    
    
    
    
    
    // --------- BUFOR KOLOWY ----------------------------
    
    
    // procedura uzycia:
    // kazdy dodaje dana gdy trzeba bufAdd
    // przy wysylaniu pyta sie bufPrepareTX -> true znaczy, ze bufor gotowy do wyslania
    // po zakonczeniu wysylania (TX interrupt) bufRemoveN( cnt ) i sprawdza podnownie bufPrepareTx
  
        
    //--------------------------------------------------------------------------
    // czy pusty
    public: inline bool isEmpty(){
      return ( mIndexSTART == mIndexSTOP );
    }//-------------------------------------------------------------------------
    
    //--------------------------------------------------------------------------
    // dodaje dana
    public: inline bool bufAdd( uint8_t aData ){
      
      // sprawdz czy mozna dodac dana
      int stopPrev = mIndexSTOP;
      int stopTmp = (mIndexSTOP+1) % cBufLength;
      if( stopTmp == mIndexSTART ) return false;           // bufor zajety - FAIL
      
      // dodaj dana
      mBuf[ stopPrev ] = aData;
      mIndexSTOP = stopTmp;
      
      return true;
      
    }//-------------------------------------------------------------------------

    
    //--------------------------------------------------------------------------
    // przygotowuje bufor do nadawania UART
    // zamysl aby przekazac zywy mBuf, a na zawijaniu zatrzymac do nastepnej iteracji
    bool bufPrepareTX( uint8_t **aBuf, int *aCnt ){
      
      // sprawdz czy bufor nie pusty
      if( mIndexSTART == mIndexSTOP ) return false;
      
      // liczenie cnt
          // bufor nie przeciety granica
      if( mIndexSTART < mIndexSTOP )  (*aCnt) = mIndexSTOP - mIndexSTART;
          // bufor przeciety granica
      else                            (*aCnt) = cBufLength - mIndexSTART;
      
      // wypelnienie bufora
      (*aBuf) = &(mBuf[mIndexSTART]);
      return true;
      
    }//-------------------------------------------------------------------------
    

    //--------------------------------------------------------------------------
    // kasuje N elementow (po nadaniu po UART)
    // zwraca liczbe skasowanych elementow
    int bufRemoveN( int aN ){

      for( int i=0; i<aN; i++ ){
        // sprawdz czy mozna usunac
        if( mIndexSTART == mIndexSTOP ) return i;       // bufor pusty
        int startTmp = (mIndexSTART+1) % cBufLength;    // probne kasowanie
        
        // kasuj element
        mIndexSTART = startTmp;                         // kasuj element
      }
      
      return aN;      
        
    }//-------------------------------------------------------------------------

    
     //--------------------------------------------------------------------------
    // odczytuje ostatnio odlozony znak
    // zero jesli pusty bufor
    // wykorzystywane na przyklad do liczenia CRC
    uint8_t readTop( ){
      
      if( mIndexSTART == mIndexSTOP ) return 0;       // bufor pusty
      return mBuf[mIndexSTOP];      // czy to dobrze, skoro STOP wskazuje na pusty ?
        
    }//-------------------------------------------------------------------------
    
    };//************************************************************************************



    M485E  g485E;


/*########################################################################################*/
/******************** METODY **************************************************************/      




#endif
/*########################################################################################*/
