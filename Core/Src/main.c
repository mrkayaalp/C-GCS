/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LoRa.h"
#include "gps.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
LoRa myLoRa;
uint8_t loraReceiveBuffer[8];
uint8_t lennaReceiveBuffer[4];
uint8_t rx_data1;
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
HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == huart5.Instance)
    GPS_CallBack();
}

HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
  if (GPIO_PIN == PW1_DIO0_Pin)
    loraRecevice();
}

void initLoRa()
{

  HAL_Delay(25);

  myLoRa.CS_port = SPI1_NSS_GPIO_Port;
  myLoRa.CS_pin = SPI1_NSS_Pin;
  myLoRa.reset_port = PW1_RST_GPIO_Port;
  myLoRa.reset_pin = PW1_RST_Pin;
  myLoRa.DIO0_port = PW1_DIO0_GPIO_Port;
  myLoRa.DIO0_pin = PW1_DIO0_Pin;
  myLoRa.hSPIx = &hspi1;

  HAL_Delay(25);

  myLoRa.frequency = 433;             // default = 433 MHz
  myLoRa.spredingFactor = SF_7;       // default = SF_7
  myLoRa.bandWidth = BW_125KHz;       // default = BW_125KHz
  myLoRa.crcRate = CR_4_5;            // default = CR_4_5
  myLoRa.power = POWER_20db;          // default = 20db
  myLoRa.overCurrentProtection = 100; // default = 100 mA
  myLoRa.preamble = 8;                // default = 8;

  HAL_Delay(25);

  HAL_GPIO_WritePin(PW1_RST_GPIO_Port, PW1_RST_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);

  uint16_t LoRa_status = LoRa_init(&myLoRa);

  HAL_Delay(25);

  if (LoRa_status != LORA_OK)
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);

  LoRa_startReceiving(&myLoRa);

  HAL_Delay(25);
}

void loraTransmit(uint8_t *data, uint16_t size)
{

  uint8_t ret;
  ret = LoRa_transmit(&myLoRa, (uint8_t *)data, size, 1000);

  if (ret != 1)
  {
    // hata
  }
}

void loraRecevice()
{
  LoRa_receive(&myLoRa, loraReceiveBuffer, sizeof(loraReceiveBuffer));
}

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
  MX_SPI1_Init();
  MX_SPI6_Init();
  MX_UART7_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_SPI4_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_SPI5_Init();
  MX_UART5_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */
 // initLoRa();
  GPS_Init();

  HAL_GPIO_WritePin(PW2_RST_GPIO_Port, PW2_RST_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(SPI6_NSS_GPIO_Port, SPI6_NSS_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(SPI5_NSS_GPIO_Port, SPI5_NSS_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(SPI_RST_GPIO_Port, SPI_RST_Pin, GPIO_PIN_SET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    HAL_GPIO_WritePin(USER_LED1_GPIO_Port, USER_LED1_Pin, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED1_GPIO_Port, USER_LED1_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED2_GPIO_Port, USER_LED2_Pin, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED2_GPIO_Port, USER_LED2_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED3_GPIO_Port, USER_LED3_Pin, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED3_GPIO_Port, USER_LED3_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED4_GPIO_Port, USER_LED4_Pin, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED4_GPIO_Port, USER_LED4_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED5_GPIO_Port, USER_LED5_Pin, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED5_GPIO_Port, USER_LED5_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED6_GPIO_Port, USER_LED6_Pin, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED6_GPIO_Port, USER_LED6_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED7_GPIO_Port, USER_LED7_Pin, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED7_GPIO_Port, USER_LED7_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED8_GPIO_Port, USER_LED8_Pin, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED8_GPIO_Port, USER_LED8_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED7_GPIO_Port, USER_LED7_Pin, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED7_GPIO_Port, USER_LED7_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED6_GPIO_Port, USER_LED6_Pin, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED6_GPIO_Port, USER_LED6_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED5_GPIO_Port, USER_LED5_Pin, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED5_GPIO_Port, USER_LED5_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED4_GPIO_Port, USER_LED4_Pin, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED4_GPIO_Port, USER_LED4_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED3_GPIO_Port, USER_LED3_Pin, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED3_GPIO_Port, USER_LED3_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED2_GPIO_Port, USER_LED2_Pin, 1);
    HAL_Delay(10);
    HAL_GPIO_WritePin(USER_LED2_GPIO_Port, USER_LED2_Pin, 0);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

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
