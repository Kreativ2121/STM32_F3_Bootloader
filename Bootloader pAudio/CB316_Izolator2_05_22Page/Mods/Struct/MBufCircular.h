#ifndef __MBufCircular_CB711_H
#define __MBufCircular_CB711_H


/*########################################################################################*/
/******************** KLASY ***************************************************************/      

// byc moze FIFO ???
  class MBufCircular{

    //+++ POLA ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    static const uint8_t cBufLength = 40;   
    public: uint8_t mBuf[cBufLength];   // bufor kolowy
    public: uint8_t mIndexSTART = 0;    // pierwszy zajety (pusty buf jesli == Stop )
    public: uint8_t mIndexSTOP  = 0;    // pierwszy wolny
    
    
    //+++ METODY +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    ///--------------------------------------------------------------------------
    /// czyszczenie bufora
    public: void clear(){
      mIndexSTART = 0;
      mIndexSTOP = 0;
    }//-------------------------------------------------------------------------
      
    ///--------------------------------------------------------------------------
    /// dodaje dana
    public: bool bufAdd( uint8_t aData ){
      
      // sprawdz czy mozna dodac dana
      int stopPrev = mIndexSTOP;
      int stopTmp = (mIndexSTOP+1) % cBufLength;
      if( stopTmp == mIndexSTART ) return false;           // bufor zajety - FAIL
      
      // dodaj dana
      mBuf[ stopPrev ] = aData;
      mIndexSTOP = stopTmp;
      
      return true;
      
    }//-------------------------------------------------------------------------

    ///--------------------------------------------------------------------------
    /// dodaje ramke
    public: bool bufAddFrame( int cnt, uint8_t *frame ){
    
      // sprawdz czy sie zmiesci
      int N = this->getN();
      int N2 = N + cnt + 1;
      if( N2 >= cBufLength ) return false;
      
      // dodaj ramke
      bufAdd( cnt );
      for( int i=0; i<cnt; i++ ) bufAdd( frame[i] );
      
      return true;
    
    }//-------------------------------------------------------------------------
    
    
    
    ///-------------------------------------------------------------------------
    /// kasuje pierwszy element
    public: bool bufRemove(){
        if( mIndexSTART == mIndexSTOP ) return false;  // bufor pusty
        mIndexSTART = (mIndexSTART+1) % cBufLength;    
        return true;
    }//-------------------------------------------------------------------------
    
    ///--------------------------------------------------------------------------
    /// Pobiera pierwszy element
    public: uint8_t getFirst(){
    
      if( mIndexSTART == mIndexSTOP ) return 0;       // bufor pusty
      
      return mBuf[mIndexSTART];      
    
    }//-------------------------------------------------------------------------
    
    ///--------------------------------------------------------------------------
    /// Pobiera pierwszy element i kasuje
    public: uint8_t popFirst(){
      if( mIndexSTART == mIndexSTOP ) return 0;       // bufor pusty
      uint8_t dana = mBuf[mIndexSTART];      
      mIndexSTART = (mIndexSTART+1) % cBufLength;    
      return dana;      
    }//-------------------------------------------------------------------------
    
    
    ///--------------------------------------------------------------------------
    /// Pobiera ostatni element
    public: uint8_t getLast(){
    
      if( mIndexSTART == mIndexSTOP ) return 0;       // bufor pusty
      
      int index = mIndexSTOP;
      index -= 1;
      if( index < 0 ) index += cBufLength;
      
      return mBuf[index];      
    
    }//-------------------------------------------------------------------------

    ///--------------------------------------------------------------------------
    /// Pobiera element N
    public: uint8_t getAt(int aN){
    
      if( mIndexSTART == mIndexSTOP ) return 0;       // bufor pusty
      
      int index = mIndexSTART;
      index += aN;
      if( index > cBufLength ) index -= cBufLength;
      
      return mBuf[index];      
    
    }//-------------------------------------------------------------------------
        
    ///--------------------------------------------------------------------------
    /// Liczba elementow w buforze
    public: int getN(){
      
      int dif = mIndexSTOP - mIndexSTART;
      if( dif < 0 ) dif = cBufLength + dif;
      return dif;
      
    }//-------------------------------------------------------------------------
        
    ///--------------------------------------------------------------------------
    /// czy mozna dodac N elementow
    public: bool checkAddN( int aN ){
    
       int cnt = getN();
       cnt += aN;
       return  cnt < cBufLength;
    
    }//-------------------------------------------------------------------------
    
    ///--------------------------------------------------------------------------
    /// odczytuje ostatnio odlozony znak
    /// zero jesli pusty bufor
    /// wykorzystywane na przyklad do liczenia CRC
    uint8_t readTop( ){
      
      if( mIndexSTART == mIndexSTOP ) return 0;       // bufor pusty
      return mBuf[mIndexSTOP];      // czy to dobrze, skoro STOP wskazuje na pusty ?
        
    }//-------------------------------------------------------------------------

    ///--------------------------------------------------------------------------
    /// czy pusty
    public: inline bool isEmpty(){
      return ( mIndexSTART == mIndexSTOP );
    }//-------------------------------------------------------------------------
    
    ///--------------------------------------------------------------------------
    /// kasuje N elementow (np. po nadaniu po UART)
    /// zwraca liczbe skasowanych elementow
    int bufRemoveN( int aN ){

      // pewnie da sie to zrobic lepiej
      for( int i=0; i<aN; i++ ){
        // sprawdz czy mozna usunac
        if( mIndexSTART == mIndexSTOP ) return i;       // bufor pusty
        int startTmp = (mIndexSTART+1) % cBufLength;    // probne kasowanie
        
        // kasuj element
        mIndexSTART = startTmp;                         // kasuj element
      }
      
      return aN;      
        
    }//-------------------------------------------------------------------------

    ///--------------------------------------------------------------------------
    /// przygotowuje bufor do nadawania UART
    /// zamysl aby przekazac zywy mBuf, a na zawijaniu zatrzymac do nastepnej iteracji
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

    };//************************************************************************************



/*########################################################################################*/
/******************** METODY **************************************************************/      


// 0 1 2 3 4 5 6 7
// x - - - - x x x
// start = 5   stop = 1

// 0 1 2 3 4 5 6 7
// - x x x - - - -
// start = 1   stop = 4

// 0 1 2 3 4 5 6 7
// x x x x x x x x
// start = 6   stop = 6  wolny bufor, przypadek nie mozliwy




#endif
/*########################################################################################*/