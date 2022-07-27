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
#include "stm32f1xx_hal.h"

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
#define LED_CARD_OUT_Pin GPIO_PIN_15
#define LED_CARD_OUT_GPIO_Port GPIOC
#define C4MA_BAT_I_Pin GPIO_PIN_0
#define C4MA_BAT_I_GPIO_Port GPIOB
#define C4MA_PWR_I_Pin GPIO_PIN_1
#define C4MA_PWR_I_GPIO_Port GPIOB
#define C4MA_GPIO0_O_Pin GPIO_PIN_2
#define C4MA_GPIO0_O_GPIO_Port GPIOB
#define SRV_TXD_O_Pin GPIO_PIN_10
#define SRV_TXD_O_GPIO_Port GPIOB
#define SRV_RXD_I_Pin GPIO_PIN_11
#define SRV_RXD_I_GPIO_Port GPIOB
#define C4MA_DE_O_Pin GPIO_PIN_8
#define C4MA_DE_O_GPIO_Port GPIOA
#define C4MA_TXD_O_Pin GPIO_PIN_9
#define C4MA_TXD_O_GPIO_Port GPIOA
#define C4MA_RXD_I_Pin GPIO_PIN_10
#define C4MA_RXD_I_GPIO_Port GPIOA
#define C4MA_RE_O_Pin GPIO_PIN_11
#define C4MA_RE_O_GPIO_Port GPIOA
#define C4MA_WDTR_O_Pin GPIO_PIN_12
#define C4MA_WDTR_O_GPIO_Port GPIOA
#define C4MA_WDTR_CPU_O_Pin GPIO_PIN_15
#define C4MA_WDTR_CPU_O_GPIO_Port GPIOA
#define C4MA_GPIO1_O_Pin GPIO_PIN_4
#define C4MA_GPIO1_O_GPIO_Port GPIOB
#define C4MA_EN_I_Pin GPIO_PIN_5
#define C4MA_EN_I_GPIO_Port GPIOB
#define C4MA_BYP_O_Pin GPIO_PIN_8
#define C4MA_BYP_O_GPIO_Port GPIOB
#define C4MA_BYP_I_Pin GPIO_PIN_9
#define C4MA_BYP_I_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
