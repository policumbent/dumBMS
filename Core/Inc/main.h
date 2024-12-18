/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "settings.h"
#include "button.h"
#include "bat.h"
#include "can_dumbms.h"
#include "usart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#define BUT_BAT_STAT_LED_Pin GPIO_PIN_13
#define BUT_BAT_STAT_LED_GPIO_Port GPIOC
#define CAN_ID_Selector_Pin GPIO_PIN_1
#define CAN_ID_Selector_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_MCU_STATUS_Pin GPIO_PIN_5
#define LD2_MCU_STATUS_GPIO_Port GPIOA
#define ADC_BAT0_Pin GPIO_PIN_7
#define ADC_BAT0_GPIO_Port GPIOA
#define ADC_BAT1_Pin GPIO_PIN_4
#define ADC_BAT1_GPIO_Port GPIOC
#define ADC_BAT2_Pin GPIO_PIN_5
#define ADC_BAT2_GPIO_Port GPIOC
#define ADC_BAT3_Pin GPIO_PIN_0
#define ADC_BAT3_GPIO_Port GPIOB
#define ADC_BAT4_Pin GPIO_PIN_1
#define ADC_BAT4_GPIO_Port GPIOB
#define BAT0_LED0_Pin GPIO_PIN_12
#define BAT0_LED0_GPIO_Port GPIOB
#define BAT0_LED1_Pin GPIO_PIN_13
#define BAT0_LED1_GPIO_Port GPIOB
#define BAT1_LED0_Pin GPIO_PIN_14
#define BAT1_LED0_GPIO_Port GPIOB
#define BAT1_LED1_Pin GPIO_PIN_15
#define BAT1_LED1_GPIO_Port GPIOB
#define BAT2_LED0_Pin GPIO_PIN_6
#define BAT2_LED0_GPIO_Port GPIOC
#define BAT2_LED1_Pin GPIO_PIN_7
#define BAT2_LED1_GPIO_Port GPIOC
#define BAT3_LED0_Pin GPIO_PIN_8
#define BAT3_LED0_GPIO_Port GPIOC
#define BAT3_LED1_Pin GPIO_PIN_9
#define BAT3_LED1_GPIO_Port GPIOC
#define BAT4_LED0_Pin GPIO_PIN_8
#define BAT4_LED0_GPIO_Port GPIOA
#define BAT4_LED1_Pin GPIO_PIN_9
#define BAT4_LED1_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define BAT_SEL_1_Pin GPIO_PIN_10
#define BAT_SEL_1_GPIO_Port GPIOC
#define BAT_SEL_2_Pin GPIO_PIN_11
#define BAT_SEL_2_GPIO_Port GPIOC
#define BAT_SEL_3_Pin GPIO_PIN_12
#define BAT_SEL_3_GPIO_Port GPIOC
#define BAT_SEL_4_Pin GPIO_PIN_2
#define BAT_SEL_4_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
