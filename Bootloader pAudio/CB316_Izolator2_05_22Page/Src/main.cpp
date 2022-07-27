/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

    
#define _M_ID     0x21070A01
    
   // +++ ADRES +++++

#define _MODULE_ADDR    0x00
#define _MODULE_0
#define _LOOP_NR	0x01

//#define _MODULE_204
//#define _MODULE_1
//#define _MODULE_3
//#define _MODULE_255
   // +++ do wersji testowej nie potrzebny modem
//#define _MODEM_OFF
  // wersja na stara plytke
#define _VER_V0_5
//#define _VER_V0_1
  // +++ wersja z USART PC - nie odbiera wlasnych bajtow
//#define _USART_PC

//#define _SLAWEK_

/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include <cstdint>
    
uint8_t gDbgTab[128];
uint8_t gDbgTab2[128];
uint8_t gDbgIndex = 0;
bool qriz = 0;

//        gDbgTab[ gDbgIndex ] = mRXBuf[0];
//        gDbgTab2[ gDbgIndex ] = _o485E_EN;
//        gDbgIndex = (gDbgIndex + 1) % 128;


//#include <intrinsics.h>
//#include <arm_itm.h>
#include "../Mods/Struct/MBufCircular.h"  


#include "../Mods/GPIO/MGPIO.h"         	// GPIO
#include "../Mods/RS485_E/M485_E.h"     	// 485
#include "../Mods/ADC/MADC.h"           	// ADC
#include "../Mods/ST7580/MST7580.h"     	// Modem
#include "../Mods/Relays/MRelays.h"     	// Relays init onTimer
#include "../Mods/System/MSystem.h"     	// PwrSup_Source;
#include "../Mods/Network/MNetwork.h"   	// M0 M1 itp - timeouty
#include "../Mods/Flash_SSD/MFlash_SSD.h"	// Flash do zapisu adresu

    
//#include "../Mods/ST7580/st7580_appli.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//void NucleoST7580RxInt(UART_HandleTypeDef* UartHandle){}
//void NucleoST7580TxInt(UART_HandleTypeDef* UartHandle){}
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */




//----------------------------------------------------------------------------
void HAL_UART_TxCpltCallback( UART_HandleTypeDef *huart ){ 
  //__disable_irq();
  if( huart == g485E.mhUart   )  g485E.onIT_TX(); 
  if( huart == gST7580.mhUart )  gST7580.onIT_TX();
 // __enable_irq();  
 }//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart ) { 
 // __disable_irq();
  if( huart == g485E.mhUart   )  g485E.onIT_RX(); 
  if( huart == gST7580.mhUart )  gST7580.onIT_RX();
//  __enable_irq();  
 }//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
   /* int32_t sample =  HAL_ADC_GetValue(hadc);
    int32_t sample2 =  HAL_ADC_GetValue(hadc);
    ITM_EVENT16( 2, sample );
    ITM_EVENT16( 3, sample2 );
    gADC.onSample( sample );*/
  
    if( hadc == &hadc2 )       gADC.onSample_ADC2();
    else if( hadc == &hadc1 )  gADC.onSample_ADC1();
      
}//----------------------------------------------------------------------------


// *** IT - SYS ****************************************************************
//----------------------------------------------------------------------------
void HAL_SYSTICK_Callback(void){

    // --- System ----------
    gSystem.onTimer_1ms();
      
    // --- ADC -------------
    //  gADC.onTimer();     // uruchomienie przetwornika
    
    // --- RS485 -------------
  /* __disable_irq();
    
    
    if( gRSCnt >= 1 ){
      gRSCnt = 0;
      g485E.onTimer_Frame();  
    }else gRSCnt += 1;
    
   __enable_irq();*/
    
   // g485E.onTimer();     // Frame.TimeOut WDT
   
   
   
   // --- ST7580 -----------

   
    // --- RELAYs -----------
  // ITM_EVENT16( 1, gADC.mUA_avr );  
  // ITM_EVENT16( 1, avr );  
   gRelays.onTimer_1ms(); // zwarcie + wylaczanie przekaznikow
        
 }//----------------------------------------------------------------------------
 


uint8_t gLEDCnt = 0;


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
    __disable_irq();
  //  SysTick_Config( SystemCoreClock / 100 ); 
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  
  // ... STARE USTAWIENIA !!! ......................
#ifdef _VER_V0_1
  {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
      /*Configure GPIO pins : PBPin PBPin */
    GPIO_InitStruct.Pin = oCurMod_ON_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  }
#endif

   // ... PINY INIT ...............................
   gST7580.pinTREQ( 1 ) ;
   gST7580.pinRESETN( 1 );
  _o485E_PwrEN = 0;  
  _oTPS_SEL = 1;        // kanal 1 do analizy pradu
  _oTPS_DIAGEN = 1;     // enable diagnostics
  _oTPS_THER = 0;       // auto retry mode
  _oTPS_ON_2 = 1;
  _oTPS_ON_1 = 0;

  // ... MODULY INIT ..............................
  gRelays.init();
  gADC.init();
  g485E.init( &huart1 );

  gST7580.init( &huart2 );
  gSystem.init();

//#ifndef _MODULE_0
	  gFlash_SSD.init(31);	// 63 = page number
	  gFlash_SSD.initParams();
//#endif

  
  /*for( int i =0; i<128; i++ )
  	  {gDbgTab[i] = 0;}
  for( int i =0; i<128; i++ )
  	  {gDbgTab2[i] = 0;}*/ //NIE UZYWANE??? TYLKO DLA IAR
  //gDbgIndex = 0;
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  __enable_irq();
// gST7580.enableTX_IRQ();
  //__HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);	// !!!!	
  //gST7580.init();  


  gRelays.initProc();  
  gST7580.initModem();
  gADC.initIRQ();
  
 // g485E.onTimer_Frame(); 
  while (1)
  {
	  // ... Timer_Main 1000ms ..........................
  if( gSystem.mTimer_Is1000ms ){
	  gSystem.mTimer_Is1000ms = false;

	  gST7580.onTimer_Main1000ms();

	  //DEBUG
//	  if(qriz)
//	  {
//	      //gRelays.setREL_A( true );
//	      gRelays.setREL_B( true );
//	  }
//	  else
//	  {
//	      //gRelays.setREL_A( false );
//		  gRelays.setREL_B( false );
//	  }
//	  qriz = !qriz;

  }


    // ... Timer_Main 100ms ..........................
    if( gSystem.mTimer_Is100ms ){
      gSystem.mTimer_Is100ms = false;
      
      gSystem.onTimer_Main100ms();      // PwrSupSource: if all Rels OFF -> 
                                        // 1.5s -> UA?UB -> SupSource
      gST7580.onTimer_Main100ms();      // puste
      
      gMod1.onTimer_Main100ms();        // WDT+=1

      //g485E.sendTX_ID(0x00);
      g485E.onTimer_Main100ms();

      //gLEDCnt += 1;
      //if( gLEDCnt > 10 ){
    //	  _oLED = ~_oLED;
    //	  gLEDCnt = 0;
      //}


    }

    // ... Timer_Main 10ms ..........................
    if( gSystem.mTimer_Is10ms ){
      gSystem.mTimer_Is10ms = false;
      
      gRelays.onTimer_Main10ms();     // PwrSupSource
      gST7580.onTimer_Main10ms();     // Modem: czy ramka -> odbierz (1=wyslij)
      g485E.onTimer_Main10ms();       // WDT do TimeOut

    }

    // ..............................................
    

    
      
     // HAL_Delay(100);
    
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_TIM1
                              |RCC_PERIPHCLK_ADC12;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV32;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

//#ifdef _MODULE_0
  #include "../Mods/RS485_E/M485_E_cpp.h"
  #include "../Mods/RS485_E/M485_E_cpp_RX.h"
  #include "../Mods/RS485_E/M485_E_cpp_TX.h"
/*#else
  #ifdef _MODULE_1
    #include "../Mods/RS485_E/M485_E_cpp_M1.h"
  #else // _MODULE_255
    #include "../Mods/RS485_E/M485_E_cpp.h"
    #include "../Mods/RS485_E/M485_E_cpp_RX.h"
  #endif
#endif*/




#include "../Mods/ST7580/MST7580_cpp.h"
#include "../Mods/ST7580/MST7580_cpp_TX.h"
#include "../Mods/ST7580/MST7580_cpp_RX.h"
#include "../Mods/ADC/MADC_cpp.h"
#include "../Mods/Relays/MRelays_cpp.h"
#include "../Mods/System/MSystem_cpp.h"
#include "../Mods/Flash_SSD/MFlash_SSD_cpp.h"

//#include "../Mods/ST7580/st7580_appli.c"
//#include "e:\XCh\OneDrive_AC\Projects\ZUT\pAudio\soft\ARM\CA9\Mods\ST7580\ST7580_Library\Src\ST7580_Serial.c"

//#include "C:\Programy\Project\pAudio\STM32CubeExpansion_PLM1_V1.1.0\Drivers\BSP\X-NUCLEO-PLM01A1\stm32_plm01a1.c"
//#include "e:\XCh\OneDrive_AC\Projects\ZUT\pAudio\soft\ARM\CA9\Mods\ST7580\drv\stm32_plm01a1.c"
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

