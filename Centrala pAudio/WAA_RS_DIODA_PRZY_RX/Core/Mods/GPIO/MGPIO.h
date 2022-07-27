#ifndef __MGPIO_BH704_H
#define __MGPIO_BH704_H

#include "M_STM32F3xx.h"

/*########################################################################################*/


#define _oLED  gIOA->ODR.b.b1

//// --- Przekazniki ------------------------
//// STARE v0.1
//#ifdef  _VER_V0_1
//
//#define _oREL_A_RESET   gIOA->ODR.b.b6
//#define _oREL_A_SET     gIOA->ODR.b.b7
//#define _oREL_B_RESET   gIOB->ODR.b.b12
//#define _oREL_B_SET     gIOB->ODR.b.b13
//
//#else
//// NOWE v0.5
//#define _oREL_A_RESET   gIOA->ODR.b.b7
//#define _oREL_A_SET     gIOA->ODR.b.b6
//#define _oREL_B_RESET   gIOB->ODR.b.b13
//#define _oREL_B_SET     gIOB->ODR.b.b12
//
//#endif
//
//// --- TPS - Switch -----------------------
//#define _oTPS_ON_1      gIOB->ODR.b.b6
//#define _oTPS_ON_2      gIOB->ODR.b.b5
//#define _oTPS_DIAGEN    gIOB->ODR.b.b4
//#define _oTPS_THER      gIOC->ODR.b.b13
//#define _oTPS_SEL       gIOA->ODR.b.b11
//
//#define _iTPS_FAULT     gIOA->IDR.b.b15
//#define _iTPS_CurSense  gIOB->IDR.b.b15

// --- 485 E ------------------------------
// _o485E_EN : 1=TX, 0=RX
#define _o485E_EN      gIOA->ODR.b.b8
#define _o485E_PwrEN   gIOA->ODR.b.b12
//#define _o485E_PwrEN_2 gIOE->ODR.b.b7

#define _d485E_TX  gIOA->IDR.b.b9
#define _d485E_RX  gIOA->IDR.b.b10



//#define _iPB  gIOA->IDR.b.b0
/*
// --- Przekazniki ------------------------
#define _oREL1  gIOE->ODR.b.b14
#define _oREL2  gIOE->ODR.b.b13
#define _oREL3  gIOE->ODR.b.b10
#define _oREL4  gIOE->ODR.b.b12
#define _oREL5  gIOE->ODR.b.b9
#define _oREL6  gIOE->ODR.b.b11


// --- UART -------------------------------
#define _dUSB_TX  gIOC->IDR.b.b12
#define _dUSB_RX  gIOD->IDR.b.b2

#define _d232_TX  gIOC->IDR.b.b10
#define _d232_RX  gIOC->IDR.b.b11

#define _o485C_EN  gIOD->ODR.b.b4
#define _d485C_TX  gIOD->IDR.b.b5
#define _d485C_RX  gIOD->IDR.b.b6

#define _o485D_EN  gIOB->ODR.b.b14
#define _d485D_TX  gIOD->IDR.b.b8
#define _d485D_RX  gIOD->IDR.b.b9

#define _o485E_EN  gIOA->ODR.b.b12
#define _d485E_TX  gIOA->IDR.b.b9
#define _d485E_RX  gIOA->IDR.b.b10


// --- Krancowki --------------------------
#define _oKEN_1  gIOB->ODR.b.b7
#define _oKEN_2  gIOB->ODR.b.b6
#define _oKEN_3  gIOB->ODR.b.b5
#define _oKEN_4  gIOB->ODR.b.b4
#define _oKEN_5  gIOE->ODR.b.b7
#define _oKEN_6  gIOE->ODR.b.b8

//#define _iKSEL   gIOH->IDR.b.b1
//#define _iKSEH   gIOC->IDR.b.b0
//#define _iKFLT   gIOH->IDR.b.b0

#define _aK_1    gIOF->IDR.b.b2
#define _aK_2    gIOA->IDR.b.b4
#define _aK_3    gIOA->IDR.b.b5
#define _aK_4    gIOA->IDR.b.b6
#define _aK_5    gIOA->IDR.b.b7
#define _aK_6    gIOC->IDR.b.b4

#define _aK_CS1  gIOC->IDR.b.b5
#define _aK_CS2  gIOB->IDR.b.b2


// --- LEDy -----------------------------
#define _oLED1   gIOE->ODR.b.b2
#define _oLED2   gIOE->ODR.b.b3
#define _oLED3   gIOE->ODR.b.b4
#define _oLED4   gIOE->ODR.b.b5

// --- TEMPERATURE ----------------------
//#define _iTEMP_INT  gIOB->IDR.b.b5

//#define _dI2C_SCL   gIOB->IDR.b.b6
//#define _dI2C_SDA   gIOB->IDR.b.b7


#define _oOW1  gIOC->ODR.b.b6
#define _iOW1   gIOC->IDR.b.b6

#define _oOW2  gIOC->ODR.b.b9
#define _iOW2   gIOC->IDR.b.b9


// --- DISTANCE -------------------------
#define _oDist_TRIG1  gIOB->ODR.b.b12
#define _iDist_ECHO1  gIOB->IDR.b.b13

#define _DistPIN_1    GPIO_PIN_13
#define _DistPIN_2    GPIO_PIN_14

#define _oDist_TRIG2  gIOD->ODR.b.b12
#define _iDist_ECHO2  gIOD->IDR.b.b13

#define _oDist_TRIG3  gIOD->ODR.b.b14
#define _iDist_ECHO3  gIOD->IDR.b.b15

#define _oDist_TRIG4  gIOC->ODR.b.b7
#define _iDist_ECHO4  gIOC->IDR.b.b8

// --- ZASILACZ ---------------------------

// _oRSP_PU   Power, 0 = ON; 1=OFF
#define _oRSP_PU   gIOE->ODR.b.b15
// _oRSP_POK   Power OK, 1 = OK;0=Error
#define _iRSP_POK  gIOF->IDR.b.b6
*/


#endif
/*########################################################################################*/
