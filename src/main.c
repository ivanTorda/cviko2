/**
 ******************************************************************************
 * @file    main.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    11-February-2014
 * @brief   Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup IO_Toggle
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
uint8_t BlinkSpeed = 0;
/* Private function prototypes -----------------------------------------------*/
RCC_ClocksTypeDef RCC_Clocks;
/* Private functions ---------------------------------------------------------*/

/**
 * @brief   Main program
 * @param  None
 * @retval None
 */
int main(void) {
	//init GPIOA
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIOA->MODER |= (0b01) << (5 * 2);
	GPIOA->OTYPER &= ~(uint16_t) (1 << 5);
	GPIOA->PUPDR |= (0b01) << (5 * 2);
	GPIOA->OSPEEDR |= (0b11) << (5 * 2);

	//init GPIOC
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	GPIOA->MODER |= (0b00) << (13 * 2);
	GPIOA->OTYPER &= ~(uint16_t) (13 << 5);
	GPIOA->PUPDR |= (0b00) << (13 * 2);

	int button = 0;


	/* Infinite loop */
	while (1) {
		if (GPIOC->IDR & (uint32_t) 0b0010000000000000) {
			button = 1;
			GPIOA->ODR |= (1 << 5);
		} else {
			button = 0;
			GPIOA->ODR &= ~(1 << 5);
		}

	}
}

/**
 * @brief  Inserts a delay time.
 * @param  nTime: specifies the delay time length, in 1 ms.
 * @retval None
 */
void Delay(__IO uint32_t nTime) {
	TimingDelay = nTime;

	while (TimingDelay != 0)
		;
}

/**
 * @brief  Decrements the TimingDelay variable.
 * @param  None
 * @retval None
 */
void TimingDelay_Decrement(void) {
	if (TimingDelay != 0x00) {
		TimingDelay--;
	}
}

#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
