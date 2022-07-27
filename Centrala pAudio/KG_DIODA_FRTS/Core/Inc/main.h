/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_CARD_Pin GPIO_PIN_2
#define LED_CARD_GPIO_Port GPIOF
#define COM_LED_CARD_Pin GPIO_PIN_2
#define COM_LED_CARD_GPIO_Port GPIOC
#define C4MA_DE_O_Pin GPIO_PIN_0
#define C4MA_DE_O_GPIO_Port GPIOG
#define C4MA_WDTRST_Pin GPIO_PIN_7
#define C4MA_WDTRST_GPIO_Port GPIOE
#define CPU_WDTRST_Pin GPIO_PIN_8
#define CPU_WDTRST_GPIO_Port GPIOE
#define C4MA_TXD_O_Pin GPIO_PIN_8
#define C4MA_TXD_O_GPIO_Port GPIOD
#define C4MA_RXD_I_Pin GPIO_PIN_9
#define C4MA_RXD_I_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
