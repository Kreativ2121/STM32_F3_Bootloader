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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "../Inc/main.h"
//#include "usart.h"
#include "gpio.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "../Mods/RS485_E/M485_E.h"
#include "../Mods/GPIO/MGPIO.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

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
////----------------------------------------------------------------------------
//void HAL_UART_TxCpltCallback( UART_HandleTypeDef *huart ){
//  //__disable_irq();
//  if( huart == g485E.mhUart   )  g485E.onIT_TX();
//
//  //if( huart == gST7580.mhUart )  gST7580.onIT_TX();
// // __enable_irq();
// }//----------------------------------------------------------------------------
//
////----------------------------------------------------------------------------
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart ) {
// // __disable_irq();
//
//  if( huart == g485E.mhUart   )  g485E.onIT_RX();
//	//HAL_GPIO_TogglePin (LED_CARD_GPIO_Port, LED_CARD_Pin);
//	//HAL_UART_Receive_IT(  huart, mRXBuf, 1 );
//
//  //if( huart == gST7580.mhUart )  gST7580.onIT_RX();
//  //__enable_irq();
// }//----------------------------------------------------------------------------

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

  //MX_UART5_Init();
  //MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  //_o485E_PwrEN = 0;
  //_o485E_PwrEN_2 = 0;

  //g485E.init( &huart3 );


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  __enable_irq();

  HAL_GPIO_WritePin(C4MA_DE_O_GPIO_Port,C4MA_DE_O_Pin, GPIO_PIN_SET);
//
//
//
//
//  HAL_GPIO_WritePin(CPU_WDTRST_GPIO_Port,CPU_WDTRST_Pin, GPIO_PIN_SET);
   HAL_GPIO_WritePin(C4MA_WDTRST_GPIO_Port,C4MA_WDTRST_Pin, GPIO_PIN_SET);
//
//  HAL_GPIO_WritePin (LED_CARD_GPIO_Port, LED_CARD_Pin, HAL_GPIO_ReadPin(C4MA_ENA_GPIO_Port, C4MA_ENA_Pin));
//  HAL_GPIO_WritePin (LED_CARD_GPIO_Port, LED_CARD_Pin, GPIO_PIN_SET);
//  HAL_Delay (1000);

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//	  for(int i = 0; i < 50000;i++)
//	  {
//
//	  }

	  HAL_GPIO_WritePin (CPU_WDTRST_GPIO_Port, CPU_WDTRST_Pin, GPIO_PIN_RESET);
	  //HAL_Delay(1);
	  for (int i=0; i<100; i++)
	  {

	  }
	  HAL_GPIO_WritePin (CPU_WDTRST_GPIO_Port, CPU_WDTRST_Pin, GPIO_PIN_SET);
	  //HAL_Delay(1);
	  for (int i=0; i<100; i++)
	  	  {

	  	  }
	  HAL_GPIO_WritePin (C4MA_WDTRST_GPIO_Port, C4MA_WDTRST_Pin, GPIO_PIN_RESET);
	  //HAL_Delay(1);
	  for (int i=0; i<100; i++)
	  {

	  }
	  HAL_GPIO_WritePin (C4MA_WDTRST_GPIO_Port, C4MA_WDTRST_Pin, GPIO_PIN_SET);
	  HAL_Delay(5);


//	  HAL_GPIO_TogglePin (CPU_WDTRST_GPIO_Port, CPU_WDTRST_Pin);
//	  HAL_GPIO_TogglePin (C4MA_WDTRST_GPIO_Port, C4MA_WDTRST_Pin);
//	  //HAL_GPIO_TogglePin (OUTPUT2_GPIO_Port, OUTPUT2_Pin);
//
	  HAL_GPIO_WritePin (LED_CARD_GPIO_Port, LED_CARD_Pin, HAL_GPIO_ReadPin(C4MA_ENA_GPIO_Port, C4MA_ENA_Pin));

//	  if (HAL_GPIO_ReadPin(C4MA_ENA_GPIO_Port, C4MA_ENA_Pin) == GPIO_PIN_SET)
//		  HAL_GPIO_WritePin (LED_CARD_GPIO_Port, LED_CARD_Pin, GPIO_PIN_RESET);
//	  else
//		  HAL_GPIO_WritePin (LED_CARD_GPIO_Port, LED_CARD_Pin, GPIO_PIN_SET);



	  HAL_Delay (200);   /* Insert delay 100 ms */

	  //g485E.sendTX_TEST();

	  //HAL_Delay (100);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
//#include "../Mods/RS485_E/M485_E_cpp.h"
//#include "../Mods/RS485_E/M485_E_cpp_TX.h"
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM3 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM3) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
