/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#define _MODULE_ADDR 0x00
#define _LOOP_NR 0x01
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../../Mods/RS485_E/M485_E.h"
#include "../../Mods/Flash_SSD/MFlash.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define PAGE 253
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t mTXBuf[2];
uint8_t mRXBuf[2];
uint8_t data[] = "HELLO \r\n";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile int gIsToJump=0;



#define APP_ADDRESS (uint32_t)0x08010000
typedef void (*pFunction)(void);
//Funkcja do przeskoczenia z bootloadera do aplikacji użytkownika
void JumpToAddress(uint32_t addr) {
    uint32_t JumpAddress = *(uint32_t *) (addr + 0x0004); //Definitions for jump
    pFunction Jump = (pFunction) JumpAddress; //Definitions for jump

    HAL_RCC_DeInit(); //Peripherials deinitialization
    HAL_DeInit();
    SysTick->CTRL = 0;	//SysTick Reset
    SysTick->LOAD = 0;	//SysTick Reset
    SysTick->VAL = 0; 	//SysTick Reset

    /* Ustawić offset tablicy wektorów przerwań (SCB→VTOR). */
    SCB->VTOR = addr;
    /*Ustawić wskaźnik stosu (odczytany z tablicy przerwań
    z adresu 0x0000 [względnego do początku programu aplikacji
     użytkownika]).*/
    __set_MSP(*(uint32_t *) addr);

    Jump(); //Jump to begin of the program -> start_of_program + 0x0004
}

void JumpToApplication() {
    JumpToAddress(APP_ADDRESS);
}


//----------------------------------------------------------------------------
void HAL_UART_TxCpltCallback( UART_HandleTypeDef *huart ){
  //__disable_irq();
  if( huart == g485E.mhUart   )  g485E.onIT_TX();
  //if( huart == gST7580.mhUart )  gST7580.onIT_TX();
 // __enable_irq();
 }//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart ) {
 // __disable_irq();
	int a =5;
	//HAL_UART_Receive_IT( &huart2, mRXBuf, 1 );
  if( huart == g485E.mhUart   )  g485E.onIT_RX();
  //if( huart == gST7580.mhUart )  gST7580.onIT_RX();
//  __enable_irq();
 }//----------------------------------------------------------------------------
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

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  g485E.init( &huart2 );
  int buttonVal = 0;
  MFlash::unlock();
  MFlash::erasePage(PAGE);
  MFlash::lock();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  __enable_irq();
  mTXBuf[0]=6;
  mTXBuf[1]=6;
  //HAL_UART_Receive_IT( &huart2, mRXBuf, 1 );
  while (1)
  {
//	  if(HAL_GPIO_ReadPin (GPIOC, GPIO_PIN_13)==0){
	  if(gIsToJump!=0){
		  JumpToApplication();
	  }
	  //iPB = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
	  //int a = 0;

//	  uint32_t address = MFlash::calcAddr(PAGE,0);
//	  uint16_t retPage = MFlash::calcPage(address,0);
//	  uint16_t var = MFlash::read16(PAGE,0);
//	  buttonVal = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
//	  if( !buttonVal ){
//		  if(var == 0xFFFF){
//			  MFlash::unlock();
//			  MFlash::write16(PAGE,0,0xABCD);
//			  MFlash::lock();
//		  }
//	  }
	  //HAL_UART_Transmit_IT( &huart2, mTXBuf,  1 );


	  //HAL_UART_Transmit (&huart2, data, sizeof (data), 10);


//	  HAL_Delay(1000);
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
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
#include "../../Mods/RS485_E/M485_E_cpp.h"
#include "../../Mods/RS485_E/M485_E_cpp_RX.h"
#include "../../Mods/RS485_E/M485_E_cpp_TX.h"
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
