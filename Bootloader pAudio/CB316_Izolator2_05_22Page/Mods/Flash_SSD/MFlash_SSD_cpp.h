#ifndef __MFlash_SSD_CPP_BH704_H
#define __MFlash_SSD_CPP_BH704_H

    // [0]      1B       g485E.mMyAddr
    
/// ---------------------------------------------------------
uint32_t  MFlash_SSD::initParams(){
  
    set8(   0, g485E.mMyAddr );
    
    parseFlash();
    
    g485E.mMyAddr   = get8( 0 );
    flush();
    
    return 0;
    
}//----------------------------------------------------------

    
#endif
/*############################################################################*/
