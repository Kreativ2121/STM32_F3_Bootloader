/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#define MA4_WCLK_Pin GPIO_PIN_0
#define MA4_WCLK_GPIO_Port GPIOA
#define DFKOM_CS_Pin GPIO_PIN_3
#define DFKOM_CS_GPIO_Port GPIOA
#define SCK_Pin GPIO_PIN_5
#define SCK_GPIO_Port GPIOA
#define MISO_Pin GPIO_PIN_6
#define MISO_GPIO_Port GPIOA
#define MOSI_Pin GPIO_PIN_7
#define MOSI_GPIO_Port GPIOA
#define LED_CARD_Pin GPIO_PIN_5
#define LED_CARD_GPIO_Port GPIOC
#define MA4_RAT_Pin GPIO_PIN_0
#define MA4_RAT_GPIO_Port GPIOB
#define MA4_BYP_Pin GPIO_PIN_1
#define MA4_BYP_GPIO_Port GPIOB
#define MA4_GPIO0_Pin GPIO_PIN_2
#define MA4_GPIO0_GPIO_Port GPIOB
#define P48FN_Pin GPIO_PIN_9
#define P48FN_GPIO_Port GPIOC
#define MA4_D_DE_Pin GPIO_PIN_8
#define MA4_D_DE_GPIO_Port GPIOA
#define WDTR_Pin GPIO_PIN_11
#define WDTR_GPIO_Port GPIOA
#define MA4_WDTRST_Pin GPIO_PIN_12
#define MA4_WDTRST_GPIO_Port GPIOA
#define SRV_TXDO_Pin GPIO_PIN_10
#define SRV_TXDO_GPIO_Port GPIOC
#define SRV_RXDI_Pin GPIO_PIN_11
#define SRV_RXDI_GPIO_Port GPIOC
#define MA4_BYP0_Pin GPIO_PIN_6
#define MA4_BYP0_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
