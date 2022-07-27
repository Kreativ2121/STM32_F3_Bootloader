#ifndef __MFlash_BH704_H
#define __MFlash_BH704_H

#include <stm32f3xx_hal_flash.h>
/*########################################################################################*/
/******************** KLASY ***************************************************************/      

  class MFlash{

    //+++ POLA ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    //+++ METODY +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    /// READ .............................................................
    //--------------------------------------------------------------------
    public: static uint8_t read8( uint16_t aPage, uint16_t aOffset ){
      uint32_t addr = 0x08000000 + (aPage * 0x800) + aOffset;
      uint8_t res = *(__IO uint8_t*)(addr);
      return res;
    };//------------------------------------------------------------------ 
    //--------------------------------------------------------------------  
    public: static  uint16_t read16( uint16_t aPage, uint16_t aOffset ){
      uint32_t addr = 0x08000000 + (aPage * 0x800) + aOffset;
      uint16_t res = *(__IO uint16_t*)(addr);
      return res;
    };//------------------------------------------------------------------
    //--------------------------------------------------------------------  
    public: static uint32_t read32( uint16_t aPage, uint16_t aOffset ){
      uint32_t addr = 0x08000000 + (aPage * 0x800) + aOffset;
      uint32_t res = *(__IO uint32_t*)(addr);
      return res;
    };//------------------------------------------------------------------
    //--------------------------------------------------------------------
    public: static uint64_t read64( uint16_t aPage, uint16_t aOffset ){
      uint32_t addr = 0x08000000 + (aPage * 0x800) + aOffset;
      uint64_t res = *(__IO uint64_t*)(addr);
      return res;
    };//------------------------------------------------------------------
        
    //--------------------------------------------------------------------
    public: static void readTable8( uint16_t aPage, uint16_t aOffset, uint8_t *aData, uint32_t aSize ){ 
        uint32_t addr = 0x08000000 + (aPage * 0x800) + aOffset;
        for( int i=0; i<aSize; i++ ){
           aData[i] = *(__IO uint8_t*)(addr);
           addr += 1;
        }
    };//------------------------------------------------------------------
    //--------------------------------------------------------------------
    public: static void readTable32( uint16_t aPage, uint16_t aOffset, uint32_t *aData, uint32_t aSize ){ 
        uint32_t addr = 0x08000000 + (aPage * 0x800) + aOffset;
        for( int i=0; i<aSize; i++ ){
           aData[i] = *(__IO uint32_t*)(addr);
           addr += 4;
        }
    };//------------------------------------------------------------------
    
    
    /// LOCK .............................................................
    //--------------------------------------------------------------------
    public: static HAL_StatusTypeDef lock(){
      HAL_StatusTypeDef res = HAL_FLASH_Lock();
      return res;
    };//------------------------------------------------------------------
    //--------------------------------------------------------------------
    public: static HAL_StatusTypeDef unlock(){
      HAL_StatusTypeDef res = HAL_FLASH_Unlock();
      return res;
    };//------------------------------------------------------------------

    
    
    /// WRITE ............................................................
    //--------------------------------------------------------------------  
    public: static HAL_StatusTypeDef write16( uint16_t aPage, uint16_t aOffset, uint16_t aData ){
       uint32_t addr = 0x08000000 + (aPage * 0x800) + aOffset;
       HAL_StatusTypeDef res = HAL_FLASH_Program( FLASH_TYPEPROGRAM_HALFWORD , addr, aData );
       return res;
    };//------------------------------------------------------------------
    //--------------------------------------------------------------------  
    public: static HAL_StatusTypeDef write32( uint16_t aPage, uint16_t aOffset, uint32_t aData ){
       uint32_t addr = 0x08000000 + (aPage * 0x800) + aOffset;
       HAL_StatusTypeDef res = HAL_FLASH_Program( FLASH_TYPEPROGRAM_WORD , addr, aData );
       return res;
    };//------------------------------------------------------------------
    //--------------------------------------------------------------------  
    public: static HAL_StatusTypeDef write64( uint16_t aPage, uint16_t aOffset, uint64_t aData ){
       uint32_t addr = 0x08000000 + (aPage * 0x800) + aOffset;
       HAL_StatusTypeDef res = HAL_FLASH_Program( FLASH_TYPEPROGRAM_DOUBLEWORD, addr, aData );
       return res;
    };//------------------------------------------------------------------
        //--------------------------------------------------------------------  
    public: static HAL_StatusTypeDef writeTable32( uint16_t aPage, uint16_t aOffset, uint32_t *aData, uint32_t aSize ){
       uint32_t addr = 0x08000000 + (aPage * 0x800) + aOffset;
       for( int i=0; i<aSize; i++ ){
          HAL_StatusTypeDef res = HAL_FLASH_Program( FLASH_TYPEPROGRAM_WORD , addr, aData[i] );
          addr += 4;
          if( res != HAL_OK ) return res;
       }
       return HAL_OK;
    };//------------------------------------------------------------------
    //--------------------------------------------------------------------  
    /// aSize musi byc podzielna przez 4
    public: static HAL_StatusTypeDef writeTable8( uint16_t aPage, uint16_t aOffset, uint8_t *aData, uint32_t aSize ){
       uint32_t addr = 0x08000000 + (aPage * 0x800) + aOffset;
       for( int i=0; i<aSize; i+=4 ){
          uint32_t wrt = (aData[i+3]<<24) | (aData[i+2]<<16) | (aData[i+1]<<8) | (aData[i+0]<<0);
          HAL_StatusTypeDef res = HAL_FLASH_Program( FLASH_TYPEPROGRAM_WORD , addr, wrt );
          asm("NOP");
          //HAL_StatusTypeDef res = HAL_OK;
          addr += 4;
          if( res != HAL_OK ) return res;
       }
       return HAL_OK;
    };//------------------------------------------------------------------
    
    //--------------------------------------------------------------------    
    //public: static void writeTable8( uint16_t aPage, uint16_t aOffset, uint8_t *aData, uint32_t aSize ){  }
    
    
    
    /// ERASE ............................................................
    //--------------------------------------------------------------------  
    public: static HAL_StatusTypeDef erasePage( uint16_t aPage ){
      
       uint32_t addr = 0x08000000 + (aPage * 0x800);
      
       FLASH_EraseInitTypeDef f;
       f.TypeErase = FLASH_TYPEERASE_PAGES;
       f.PageAddress = addr;
       f.NbPages = 1;
      
       uint32_t PageError = 0;
       HAL_StatusTypeDef res = HAL_FLASHEx_Erase(&f, &PageError);
       return res;
    };//------------------------------------------------------------------
    
    

    /// ADDR itp. ........................................................
    //-------------------------------------------------------------------- 
    public: static uint32_t calcAddr( uint16_t aPage, uint16_t aOffset ){
        uint32_t addr = 0x08000000 + (aPage * 0x800) + aOffset;
        return addr;
    };//------------------------------------------------------------------

    
    
};//************************************************************************************

  //https://www.programmersought.com/article/43611741121/ 
  //https://www.devcoons.com/how-to-write-data-to-the-internal-flash-memory-of-an-stm32/
  //e:\Projects\_Lib\STM32Cube\Repository\STM32Cube_FW_F3_V1.11.0\Projects\STM32F302R8-Nucleo\Examples\FLASH 
  //e:\XCh\OneDrive_AC\Libs\STM32\HAL_F3 


   // MFlash gFlash;

// STM32F3
// 0x0800 0000 - 0x0800 07FF 2 K Page 0
// 0x0800 0800 - 0x0800 0FFF 2 K Page 1
// 0x0800 1000 - 0x0800 17FF 2 K Page 2
// 0x0800 1800 - 0x0800 1FFF 2 K Page 3
// ...

// 0x0801 F800 - 0x0801 FFFF 2 K Page 63 - dla wersji 128KB Flash !!!

// 0x0803 F800 - 0x0803 FFFF 2 K Page 127 - dla wersji 256KB Flash
// 0x0807 F800 - 0x0807 FFFF 2 K Page 255 - dla wersji 512KB Flash

// 0x1FFF D800 - 0x1FFF F7FF 8 K System Memory
// 0x1FFF F800 - 0x1FFF F80F 8 K Option Bytes

// --- EXAMPLES ------------------------------
// // gTemp = *(__IO uint32_t*)(addr);
//  
//   gTemp64 = MFlash::read64(120, 0 );
//   gTemp32 = MFlash::read32(120, 0 );
//   gTemp16 = MFlash::read16(120, 0 );
//   gTemp8  = MFlash::read8 (120, 0 );
//  
//  // MFlash::unlock();
//  // MFlash::erasePage(120);
//  // MFlash::lock();
//   MFlash::readTable8( 120, 0, gTab8, 16 );
//   //MFlash::unlock();
//   //MFlash::writeTable8(120, 12, gTab8, 8 );
//   //MFlash::lock();



/*########################################################################################*/
/******************** METODY **************************************************************/      





#endif
/*########################################################################################*/
