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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "w25qxx.h"
#include "Pan_Tompkins.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BUFFSIZE 32
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t value_adc[BUFFSIZE];

bool wynik;
volatile uint8_t dane_gotowe;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile uint8_t recv_char;
void send_string(char* s)
{
	HAL_UART_Transmit(&huart1, (uint8_t*)s, strlen(s), 1000);
}
void setup_uart(UART_HandleTypeDef* uart)
{
	//Bluetooth HM10

	/*HAL_Delay(1000);
	HAL_UART_Transmit(uart, "AT\n", strlen("AT\n"), 100);

	HAL_Delay(100);
	HAL_UART_Transmit(uart, "AT+BAUD0\n", strlen("AT+BAUD0\n"), 100);

	HAL_Delay(100);
	HAL_UART_Transmit(uart, "AT+NAMEekg_bt\n", strlen("AT+NAMEekg_bt\n"), 100);

	HAL_Delay(100);
	HAL_UART_Transmit(uart, "AT+PIN111111\n", strlen("AT+PIN111111\n"), 100);
	*/

	//Bluetooth HC-05

	HAL_Delay(1000);
	HAL_UART_Transmit(uart, "AT\n", strlen("AT\n"), 100);

	HAL_Delay(100);
	HAL_UART_Transmit(uart, "AT+NAME=EKG_BT\n", strlen("AT+NAME=EKG_BT\n"), 100);



}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	dane_gotowe=0;

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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  HAL_ADC_Start_DMA(&hadc1,(uint16_t*)&value_adc,BUFFSIZE);
  HAL_TIM_Base_Start(&htim2);
  HAL_UART_Receive_IT(&huart1, &recv_char, 1);
  setup_uart(&huart1);
  init_PanTompkins();
  W25qxx_Init();
  /*int IntervalCounter=0;
  int iIntervalTime=0;
  int czas[7];
  czas[0]=0;
  czas[1]=0;
  czas[2]=0;
  czas[3]=0;
  czas[4]=0;
  czas[5]=0;
  czas[6]=0;
  int n=0;
  int Arytmia=1;
  int Pulse=0;
  int FifthCounter=0;
  int PrevArytmia=0;
  int State=0;*/
  int curr;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(dane_gotowe==1)
	  {
	     for(curr=0; curr<=15; curr++)
	     {
	         wynik=PanTompkins(value_adc[curr]);
	         if(wynik==0)
	         {
	        	//IntervalCounter++;
	        	//HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	         }
	         else
	         {
	        	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin );
	        	/* czas[n]=IntervalCounter*5;
	        	 IntervalCounter=0;

	        	 if (n==6)
	        	 {
	        		 czas[n-6]=czas[n-5];
	        		 czas[n-5]=czas[n-4];
	        		 czas[n-4]=czas[n-3];
	        		 czas[n-3]=czas[n-2];
	        		 czas[n-2]=czas[n-1];
	        		 czas[n-1]=czas[n];
	        		 czas[n]=wynik;
	        		 Arytmia=RR_Arytmia(czas[n-6],czas[n-5],czas[n-4],Pulse);
	        		 if ((Arytmia==5)&&(PrevArytmia==Arytmia))
	        		 {
	        			FifthCounter++;
	        			if (FifthCounter==4)
	        			{
	        				Pulse=1;
	        			}
	        		}
	        		 else
	        		{
	        			FifthCounter=0;
	        			Pulse=0;
	        		}
	        	 }
	        	 else
	        	 {
	        		 n++;
	        	 }*/
	         }
	     }
	     dane_gotowe=0;
	  }


	  if(dane_gotowe==2)
	  {
		  for(int currr=16; currr<=31; currr++)
		  {
			  wynik=PanTompkins(value_adc[currr]);
			  if(wynik==0)
			  {
	    	 	  //IntervalCounter++;
				  //HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
			  }
			  else
			  {
				  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
				  /* czas[n]=IntervalCounter*5;
	    	 	 IntervalCounter=0;

	    	 	 if (n==2)
	    	 	 {
	    	 		 czas[n-2]=czas[n-1];
	    	 	     czas[n-1]=czas[n];
	    	 	     czas[n]=wynik;
	    	 	     Arytmia=RR_Arytmia(czas[n-2],czas[n-1],czas[n],Pulse);
	    	 	     if ((Arytmia==5)&&(PrevArytmia==Arytmia))
	    	 	     	 {
	    	 	        	FifthCounter++;
	    	 	        	if (FifthCounter==4)
	    	 	        		{
	    	 	        			Pulse=1;
	    	 	        		}
	    	 	     	 }
	    	 	     else
	    	 	     	 {
	    	 	    	 	 FifthCounter=0;
	    	 	    	 	 Pulse=0;
	    	 	     	 }
	    	 	 }
	    	 	 else
	    	 	 {
	    	 		 n++;
	    	 	 }*/
			  }
		  }
	    dane_gotowe=0;
	 }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  //PrevArytmia=Arytmia;
  /* USER CODE END 3 */
  }
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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
}

/* USER CODE BEGIN 4 */
void HAL_ADC_ConvHalfCpltCallback (ADC_HandleTypeDef* hadc1)
{
	//HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
	dane_gotowe=1;
}

void HAL_ADC_ConvCpltCallback (ADC_HandleTypeDef* hadc1)
{
	//HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	dane_gotowe=2;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* uart)
{
	if(uart==&huart1)
	{
		HAL_UART_Receive_IT(&huart1,&recv_char, 1);
	}
}


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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
