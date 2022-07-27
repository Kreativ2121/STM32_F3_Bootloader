#ifndef __MFlash_SSD_BH704_H
#define __MFlash_SSD_BH704_H


/*############################################################################*/
/******************** KLASY ***************************************************/      

#include "MFlash.h"

#define _SSD_TABSIZE_  8

  class MFlash_SSD{

    //+++ POLA ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    public: uint32_t mPage = 63;
    public: uint32_t mAddr = 0x08000000 + (63 * 0x800) + 0;
    public: int32_t mOffset = 0;
    
    public: bool mIsSync = false;    // czy zsynchronizowane z flash
    
    public: uint8_t mTable[ _SSD_TABSIZE_ ];
    public: uint8_t mChangeTable[ (_SSD_TABSIZE_/8)+1 ];
        
    //+++ METODY +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
    public: uint32_t init( uint16_t aPage ){
        mPage = aPage;
	mAddr = 0x08000000 + (mPage * 0x800);
        
        table_AllFF();
        changeTable_allSet();

        return 0;
    }//----------------------------------------------------------

    
  public:  uint32_t initParams();
    

    // *** Change Table ********************************************
    public: void changeTable_allSet(){
        for( int i=0; i<((_SSD_TABSIZE_/8)+1); i++ ) mChangeTable[i] = 0xFF;
    }//----------------------------------------------------------
    
    public: void changeTable_allClear(){
        for( int i=0; i<((_SSD_TABSIZE_/8)+1); i++ ) mChangeTable[i] = 0x00;
    }//----------------------------------------------------------
    
    public: void changeTable_bitClear( uint16_t aIndex ){
        if( aIndex >= _SSD_TABSIZE_ ) return;           // blad indeksu
        int ind8A = aIndex / 8;
        int ind8B = aIndex - ind8A*8;
        uint8_t maska = 0x01 << ind8B; 
        mChangeTable[ind8A] &= (~maska);
    }//----------------------------------------------------------

    public: void changeTable_bitSet( uint16_t aIndex ){
        if( aIndex >= _SSD_TABSIZE_ ) return;           // blad indeksu
        int ind8A = aIndex / 8;
        int ind8B = aIndex - ind8A*8;
        uint8_t maska = 0x01 << ind8B; 
        mChangeTable[ind8A] |= (maska);      
    }//----------------------------------------------------------

     public: uint8_t changeTable_getBit( uint16_t aIndex ){
        if( aIndex >= _SSD_TABSIZE_ ) return 0;         // blad indeksu
        // zabezpieczyc przed ujemnym indeksem !!!
       // zabezpieczyc przed przepelnieniem indeksu !!!
        int ind8A = aIndex / 8;
        int ind8B = aIndex - ind8A*8;
        uint8_t maska = 0x01 << ind8B; 
        return  (mChangeTable[ind8A] & maska);
    }//----------------------------------------------------------
    


    // *************************************************************

    
    // *** Table ***************************************************
    public: uint8_t get8( uint16_t aIndex ){
      if( aIndex >= _SSD_TABSIZE_ ) return 0xFF;         // blad indeksu
      return mTable[ aIndex ];
    }//----------------------------------------------------------
    
    public: uint16_t get16( uint16_t aIndex ){
      
      if( (aIndex+0) >= _SSD_TABSIZE_ ) return 0xFF;         // blad indeksu
      if( (aIndex+1) >= _SSD_TABSIZE_ ) return 0xFF;     // blad indeksu
      
      return (uint16_t)((mTable[ aIndex ]<<8) | (mTable[ aIndex+1 ]<<0));
      
    }//----------------------------------------------------------

    public: uint32_t get32( uint16_t aIndex ){
      
      if( (aIndex+0) >= _SSD_TABSIZE_ ) return 0xFF;     // blad indeksu
      if( (aIndex+1) >= _SSD_TABSIZE_ ) return 0xFF;     // blad indeksu
      if( (aIndex+2) >= _SSD_TABSIZE_ ) return 0xFF;     // blad indeksu
      if( (aIndex+3) >= _SSD_TABSIZE_ ) return 0xFF;     // blad indeksu
      
      return (uint32_t)( (mTable[ aIndex ]<<24) | (mTable[ aIndex+1 ]<<16) |
                         (mTable[ aIndex ]<<8 ) | (mTable[ aIndex+1 ]<<0 ));
      
    }//----------------------------------------------------------

    
    public: void set8( uint16_t aIndex, uint8_t aValue ){
      if( aIndex >= _SSD_TABSIZE_ ) return;             // blad indeksu
      uint8_t prevWrt = get8(aIndex);
      if( prevWrt != aValue ){
          mTable[ aIndex ] = aValue;
          changeTable_bitSet( aIndex );
      }
    }//----------------------------------------------------------

    public: void set16( uint16_t aIndex, uint16_t aValue ){
      if( (aIndex+0) >= _SSD_TABSIZE_ ) return;             // blad indeksu
      if( (aIndex+1) >= _SSD_TABSIZE_ ) return;             // blad indeksu
      uint16_t prevWrt = get16(aIndex);
      if( prevWrt != aValue ){
          mTable[ aIndex+0 ] = (aValue>>8) & 0xFF;
          mTable[ aIndex+1 ] = (aValue>>0) & 0xFF;
          changeTable_bitSet( aIndex+0 );
          changeTable_bitSet( aIndex+1 );
      }
    }//----------------------------------------------------------

    public: void set32( uint16_t aIndex, uint32_t aValue ){
      if( (aIndex+0) >= _SSD_TABSIZE_ ) return;             // blad indeksu
      if( (aIndex+1) >= _SSD_TABSIZE_ ) return;             // blad indeksu
      if( (aIndex+2) >= _SSD_TABSIZE_ ) return;             // blad indeksu
      if( (aIndex+3) >= _SSD_TABSIZE_ ) return;             // blad indeksu
      uint32_t prevWrt = get32(aIndex);
      if( prevWrt != aValue ){
          mTable[ aIndex+0 ] = (aValue>>24) & 0xFF;
          mTable[ aIndex+1 ] = (aValue>>16) & 0xFF;
          mTable[ aIndex+2 ] = (aValue>>8 ) & 0xFF;
          mTable[ aIndex+3 ] = (aValue>>0 ) & 0xFF;
          changeTable_bitSet( aIndex+0 );
          changeTable_bitSet( aIndex+1 );
          changeTable_bitSet( aIndex+2 );
          changeTable_bitSet( aIndex+3 );
      }
    }//----------------------------------------------------------

    
    public: void table_AllFF(){
        for( int i=0; i<(_SSD_TABSIZE_); i++ ) mTable[i] = 0xFF;
    }//----------------------------------------------------------
    // *************************************************************
    
    
    // *** FLASH ***************************************************
   
    //--- parseFlash() ---------------------------------------------
    // przejdz po flash i uzupelnij tabele
    // tam gdzie w changetable 1 to nie znaleziono zapisu we flash - wrt 0xFF
    // mOffset na pierwsze 0xFFFF
    // wypelnia mTable, mChangeTable 1=brak wpisow; 0=odczytane
    // nie trzeba zerowac flash wcale, nadpisze stare wartosci w tablicy
     public: void parseFlash(){
       
       changeTable_allSet();
       // idz po adresach flash 
       mOffset = 0;
       do{
            uint16_t dana = MFlash::read16( mPage, mOffset );
            
            if( dana == 0xFFFF ) break;         // koniec przetwarzania
            mOffset += 2;                       // zmien offset przed continue
            if( dana == 0x0000 ) continue;      // wykasowane

            
            // --- FORMAT0 : 0iii iiii vvvv vvvv -------------
            if( (dana & 0x8000) == 0 ){ 

              // ... pobierz wrt z ramki .........
              uint16_t index = (dana >> 8) & 0x7F; 
              if( index == 0x00 )  continue;      // index+1 - zabezpieczenie przed skasowaniem
              index -= 1;
              if( index >= _SSD_TABSIZE_ ) continue; // blad za duzy index !!!
              
              uint16_t wrt   = (dana >> 0) & 0xFF;
              
              // ... update Table ................
              set8( index, wrt ); // + ustawi changeTable na 1
              changeTable_bitClear( index );
                       
            }else{
              // nie obslugiwana ramka !!!
              continue;
            }
            
            
       }while( mOffset < (2048-1) );
       
       
       // --- ustaw odpowiednio offset - na pierwsze FF -------
       flash_searchFF();
       
  }//---------------------------------------------------------- 
  
  //--- flash_searchFF() --------------------------------------
  // szuka FF, zaczynajac od aktualnego mOffset
  // NIE ZERUJE mOffset
  public: void flash_searchFF(){
    
       // --- ustaw odpowiednio offset - na pierwsze FF -------
       do{
          uint16_t dana = MFlash::read16( mPage, mOffset );
          if( dana == 0xFFFF ) return;         // koniec przetwarzania
          mOffset += 2;
       }while( mOffset < (2048-1) );
      
   }//--------------------------------------------------------- 
   

  public: uint8_t isSync(){
    
      // przejdz przez wszystkie changeTable, jesli wszedzie 0
    
    return 0;
  }
   
  public: uint8_t flush(){
      // zapisz wszystkie wpisy z tablicy stosownie do mChangeTable
      
    // idz po kolei po bitach mChange Table
        // tutaj zmieniac index oraz maske - troche trudniejsze
     for( int i=0; i<(_SSD_TABSIZE_); i++ ){
        
        uint8_t bitChange = changeTable_getBit( i );
        
        // jesli bit ustawiony
        if( bitChange != 0 ){
            // zapisz do flash
            uint8_t res = flushIndex( i );
            if( res == 2 ){     // flash czyszczony !!!
               MFlash::unlock();
               MFlash::MFlash::erasePage(mPage);
               MFlash::lock();
               mOffset = 0;
               
               changeTable_allSet();
               i = 0; continue;
            };
        }
    
    
    }
      
      return 0;
  }//----------------------------------------------------------
    
  
  // index <= 126
  public: uint16_t flushIndex(uint16_t aIndex ){
      // zapisz wszystkie wpisy z tablicy stosownie do mChangeTable
      if( aIndex >= _SSD_TABSIZE_ ) return 1; // blad indeksu: za duzy
            
      if( mOffset >= (2048-1) )     return 2; // blad FLASH: ERASE REQ
            
      // --- upewnij sie ze mOffset jest ok -----
      { uint16_t dana = MFlash::read16( mPage, mOffset );
        if( dana != 0xFFFF ){
          mOffset = 0;  flash_searchFF();
        }
      }
      if( mOffset >= (2048-1) )     return 2;   // blad FLASH: ERASE REQ
      
      // --- ZAPIS ------------------------------
      MFlash::unlock();
      uint8_t index = aIndex;
      if( index > 126 ) return 3;               // blad indeksu: za duzy
      uint8_t wrt = mTable[aIndex];
      
      uint16_t dana2 = ((index+1)<<8) | (wrt);
      MFlash::write16( mPage, mOffset, dana2 );
      MFlash::lock();
      
      flash_searchFF(); // update do mOffset
      
      // --- uaktualnij index w changeTable -----
      changeTable_bitClear( aIndex );
      
      return 0;
  }//----------------------------------------------------------
    

    
    
    };//************************************************************************



    MFlash_SSD gFlash_SSD;




/*### STARE CB405 ############################################################*/
    //    public: void update(){
//        mOffset = 0;
//        do{
//          //uint8_t dana = *(__IO uint8_t*)( mAddr + mOffset );
//          uint16_t dana = MFlash::read16( mPage, mOffset );
//          if( dana == 0xFFFF ) break;
//          mOffset += 2;
//        }while( mOffset < 2040 );
//        
//        mOffset = mOffset - 2;
//        if( mOffset == 0 ) mOffset = 0;
//    
//    }//----------------------------------------------------------

//    public: uint16_t write16( uint16_t aDana ){
//    
//      mOffset += 2;
//      
//      // --- PRZEKROCZONY ZAKRES STRONY ---------
//      if( mOffset >= 2040 ){
//        MFlash::unlock();
//        MFlash::MFlash::erasePage(mPage);
//        MFlash::lock();
//        this->update();
//        mOffset = 0;
//      }
//      
//      // --- ZAPIS ------------------------------
//      MFlash::unlock();
//      uint16_t dana = 0x0000 | (aDana);
//      MFlash::write16( mPage, mOffset, dana );
//      MFlash::lock();
//      
//      return MFlash::read16( mPage, mOffset );
//      
//    }//----------------------------------------------------------

//    public: uint16_t read16(){
//        return MFlash::read16( mPage, mOffset );
//    }//----------------------------------------------------------
//    
//    public: uint16_t readParams( uint16_t aSize, uint8_t *tab ){
//      return 0;
//    }//----------------------------------------------------------
//
//    
//    public: uint16_t writeParams( uint16_t aSize, uint8_t *tab ){
//      return 0;
//    }//----------------------------------------------------------

//    public: uint32_t init( uint16_t aPage ){
//        mPage = aPage;
//	mAddr = 0x08000000 + (mPage * 0x800);
//        this->update();
//        return 0;
//    }//----------------------------------------------------------
    
#endif
/*############################################################################*/
