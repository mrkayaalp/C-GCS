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
#include "stm32f7xx_hal.h"

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
#define GPIO_14_Pin GPIO_PIN_13
#define GPIO_14_GPIO_Port GPIOC
#define GPIO_13_Pin GPIO_PIN_14
#define GPIO_13_GPIO_Port GPIOC
#define GPIO_12_Pin GPIO_PIN_15
#define GPIO_12_GPIO_Port GPIOC
#define GPIO_11_Pin GPIO_PIN_2
#define GPIO_11_GPIO_Port GPIOF
#define GPIO_10_Pin GPIO_PIN_3
#define GPIO_10_GPIO_Port GPIOF
#define GPIO_9_Pin GPIO_PIN_4
#define GPIO_9_GPIO_Port GPIOF
#define GPIO_8_Pin GPIO_PIN_5
#define GPIO_8_GPIO_Port GPIOF
#define SPI5_NSS_Pin GPIO_PIN_6
#define SPI5_NSS_GPIO_Port GPIOF
#define SPI_RST_Pin GPIO_PIN_1
#define SPI_RST_GPIO_Port GPIOH
#define GPIO_7_Pin GPIO_PIN_0
#define GPIO_7_GPIO_Port GPIOC
#define GPIO_6_Pin GPIO_PIN_1
#define GPIO_6_GPIO_Port GPIOC
#define GPIO_5_Pin GPIO_PIN_2
#define GPIO_5_GPIO_Port GPIOC
#define GPIO_4_Pin GPIO_PIN_3
#define GPIO_4_GPIO_Port GPIOC
#define GPIO_3_Pin GPIO_PIN_1
#define GPIO_3_GPIO_Port GPIOA
#define GPIO_2_Pin GPIO_PIN_2
#define GPIO_2_GPIO_Port GPIOA
#define GPIO_1_Pin GPIO_PIN_3
#define GPIO_1_GPIO_Port GPIOA
#define SPI1_NSS_Pin GPIO_PIN_4
#define SPI1_NSS_GPIO_Port GPIOA
#define GPIO_44_Pin GPIO_PIN_4
#define GPIO_44_GPIO_Port GPIOC
#define GPIO_43_Pin GPIO_PIN_5
#define GPIO_43_GPIO_Port GPIOC
#define GPIO_42_Pin GPIO_PIN_0
#define GPIO_42_GPIO_Port GPIOB
#define GPIO_45_Pin GPIO_PIN_1
#define GPIO_45_GPIO_Port GPIOB
#define PW1_RST_Pin GPIO_PIN_2
#define PW1_RST_GPIO_Port GPIOB
#define PW1_DIO1_Pin GPIO_PIN_12
#define PW1_DIO1_GPIO_Port GPIOF
#define PW1_DIO1_EXTI_IRQn EXTI15_10_IRQn
#define PW1_DIO0_Pin GPIO_PIN_13
#define PW1_DIO0_GPIO_Port GPIOF
#define PW1_DIO0_EXTI_IRQn EXTI15_10_IRQn
#define GPIO_40_Pin GPIO_PIN_14
#define GPIO_40_GPIO_Port GPIOF
#define GPIO_39_Pin GPIO_PIN_15
#define GPIO_39_GPIO_Port GPIOF
#define GPIPO_41_Pin GPIO_PIN_0
#define GPIPO_41_GPIO_Port GPIOG
#define GPIO_38_Pin GPIO_PIN_1
#define GPIO_38_GPIO_Port GPIOG
#define IGNITION_5_Pin GPIO_PIN_9
#define IGNITION_5_GPIO_Port GPIOE
#define IGNITION_4_Pin GPIO_PIN_10
#define IGNITION_4_GPIO_Port GPIOE
#define IGNITION_3_Pin GPIO_PIN_11
#define IGNITION_3_GPIO_Port GPIOE
#define IGNITION_2_Pin GPIO_PIN_12
#define IGNITION_2_GPIO_Port GPIOE
#define IGNITION_1_Pin GPIO_PIN_13
#define IGNITION_1_GPIO_Port GPIOE
#define GPIO_37_Pin GPIO_PIN_14
#define GPIO_37_GPIO_Port GPIOE
#define GPIO_36_Pin GPIO_PIN_15
#define GPIO_36_GPIO_Port GPIOE
#define XBee2_RST_Pin GPIO_PIN_12
#define XBee2_RST_GPIO_Port GPIOB
#define GPIO_35_Pin GPIO_PIN_15
#define GPIO_35_GPIO_Port GPIOB
#define GPIO_34_Pin GPIO_PIN_8
#define GPIO_34_GPIO_Port GPIOD
#define GPIO_33_Pin GPIO_PIN_9
#define GPIO_33_GPIO_Port GPIOD
#define GPIO_32_Pin GPIO_PIN_10
#define GPIO_32_GPIO_Port GPIOD
#define GPIO_31_Pin GPIO_PIN_11
#define GPIO_31_GPIO_Port GPIOD
#define GPIO_30_Pin GPIO_PIN_12
#define GPIO_30_GPIO_Port GPIOD
#define USER_LED8_Pin GPIO_PIN_14
#define USER_LED8_GPIO_Port GPIOD
#define USER_LED7_Pin GPIO_PIN_15
#define USER_LED7_GPIO_Port GPIOD
#define USER_LED6_Pin GPIO_PIN_2
#define USER_LED6_GPIO_Port GPIOG
#define USER_LED5_Pin GPIO_PIN_3
#define USER_LED5_GPIO_Port GPIOG
#define USER_LED4_Pin GPIO_PIN_4
#define USER_LED4_GPIO_Port GPIOG
#define USER_LED3_Pin GPIO_PIN_5
#define USER_LED3_GPIO_Port GPIOG
#define USER_LED2_Pin GPIO_PIN_6
#define USER_LED2_GPIO_Port GPIOG
#define USER_LED1_Pin GPIO_PIN_7
#define USER_LED1_GPIO_Port GPIOG
#define SPI6_NSS_Pin GPIO_PIN_8
#define SPI6_NSS_GPIO_Port GPIOG
#define XBee1_RST_Pin GPIO_PIN_8
#define XBee1_RST_GPIO_Port GPIOA
#define GPIO_29_Pin GPIO_PIN_15
#define GPIO_29_GPIO_Port GPIOA
#define GPIO_28_Pin GPIO_PIN_10
#define GPIO_28_GPIO_Port GPIOC
#define GPIO_27_Pin GPIO_PIN_11
#define GPIO_27_GPIO_Port GPIOC
#define GPIO_26_Pin GPIO_PIN_0
#define GPIO_26_GPIO_Port GPIOD
#define GPIO_25_Pin GPIO_PIN_1
#define GPIO_25_GPIO_Port GPIOD
#define GPIO_24_Pin GPIO_PIN_3
#define GPIO_24_GPIO_Port GPIOD
#define SPI6_DIO0_Pin GPIO_PIN_7
#define SPI6_DIO0_GPIO_Port GPIOD
#define SPI6_DIO0_EXTI_IRQn EXTI9_5_IRQn
#define PW2_DIO0_Pin GPIO_PIN_9
#define PW2_DIO0_GPIO_Port GPIOG
#define PW2_DIO0_EXTI_IRQn EXTI9_5_IRQn
#define PW2_DIO1_Pin GPIO_PIN_10
#define PW2_DIO1_GPIO_Port GPIOG
#define PW2_DIO1_EXTI_IRQn EXTI15_10_IRQn
#define PW2_RST_Pin GPIO_PIN_11
#define PW2_RST_GPIO_Port GPIOG
#define GPIO_15_Pin GPIO_PIN_3
#define GPIO_15_GPIO_Port GPIOB
#define GPIO_16_Pin GPIO_PIN_4
#define GPIO_16_GPIO_Port GPIOB
#define GPIO_17_Pin GPIO_PIN_5
#define GPIO_17_GPIO_Port GPIOB
#define GPIO_18_Pin GPIO_PIN_8
#define GPIO_18_GPIO_Port GPIOB
#define GPIO_19_Pin GPIO_PIN_9
#define GPIO_19_GPIO_Port GPIOB
#define GPIO_20_Pin GPIO_PIN_0
#define GPIO_20_GPIO_Port GPIOE
#define GPIO_21_Pin GPIO_PIN_1
#define GPIO_21_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
