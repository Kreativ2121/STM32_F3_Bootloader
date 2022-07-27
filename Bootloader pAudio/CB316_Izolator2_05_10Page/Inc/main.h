/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
//#include <cstdio>
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

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
#define oSens_swTHER_Pin GPIO_PIN_13
#define oSens_swTHER_GPIO_Port GPIOC
#define oPLC_RESETN_Pin GPIO_PIN_14
#define oPLC_RESETN_GPIO_Port GPIOC
#define iPL_RX_ON_Pin GPIO_PIN_15
#define iPL_RX_ON_GPIO_Port GPIOC
#define oT_REQ_Pin GPIO_PIN_0
#define oT_REQ_GPIO_Port GPIOA
#define oLED_Pin GPIO_PIN_1
#define oLED_GPIO_Port GPIOA
#define iPL_TX_ON_Pin GPIO_PIN_4
#define iPL_TX_ON_GPIO_Port GPIOA
#define aVBRA_ADC2_IN2_Pin GPIO_PIN_5
#define aVBRA_ADC2_IN2_GPIO_Port GPIOA
#define oRel_A_Reset_Pin GPIO_PIN_6
#define oRel_A_Reset_GPIO_Port GPIOA
#define oRel_A_Set_Pin GPIO_PIN_7
#define oRel_A_Set_GPIO_Port GPIOA
#define aCurHOT_ADC1_IN11_Pin GPIO_PIN_0
#define aCurHOT_ADC1_IN11_GPIO_Port GPIOB
#define aCurCOLD_ADC1_IN12_Pin GPIO_PIN_1
#define aCurCOLD_ADC1_IN12_GPIO_Port GPIOB
#define iFAULTB_HOT_Pin GPIO_PIN_2
#define iFAULTB_HOT_GPIO_Port GPIOB
#define oFAULT_RESET_Pin GPIO_PIN_10
#define oFAULT_RESET_GPIO_Port GPIOB
#define iFAULTB_COLD_Pin GPIO_PIN_11
#define iFAULTB_COLD_GPIO_Port GPIOB
#define oRel_B_Reset_Pin GPIO_PIN_12
#define oRel_B_Reset_GPIO_Port GPIOB
#define oRel_B_Set_Pin GPIO_PIN_13
#define oRel_B_Set_GPIO_Port GPIOB
#define aVBRB_ADC2_14_Pin GPIO_PIN_14
#define aVBRB_ADC2_14_GPIO_Port GPIOB
#define aSens_swSens_ADC2_IN15_Pin GPIO_PIN_15
#define aSens_swSens_ADC2_IN15_GPIO_Port GPIOB
#define o485_PWR_EN_Pin GPIO_PIN_8
#define o485_PWR_EN_GPIO_Port GPIOA
#define oSens_swSEL_Pin GPIO_PIN_11
#define oSens_swSEL_GPIO_Port GPIOA
#define USART1_DE_Pin GPIO_PIN_12
#define USART1_DE_GPIO_Port GPIOA
#define iSens_swFAULT_Pin GPIO_PIN_15
#define iSens_swFAULT_GPIO_Port GPIOA
#define oSens_swDIAGEN_Pin GPIO_PIN_4
#define oSens_swDIAGEN_GPIO_Port GPIOB
#define oSens_IsON_2_Pin GPIO_PIN_5
#define oSens_IsON_2_GPIO_Port GPIOB
#define oSens_IsON_1_Pin GPIO_PIN_6
#define oSens_IsON_1_GPIO_Port GPIOB
#define oCurMod_ON_Pin GPIO_PIN_9
#define oCurMod_ON_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
