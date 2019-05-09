#include "interruption_templates.h"

//init printf() function
#include <string.h>
#define UART_PUTCHAR int __io_putchar(int ch)
UART_PUTCHAR
{
	HAL_UART_Transmit_IT(&uart, (uint8_t *)&ch, 1);
	return ch;
}

void init_GPIO_BSP_uart()
{
	//init uart for GPIO purpose with BSP
	/* enable GPIO clock for A and B port*/
	__HAL_RCC_USART1_CLK_ENABLE();

	/* defining the UART configuration structure */
	uart.Instance = USART1;
	uart.Init.BaudRate = 115200;
	uart.Init.WordLength = UART_WORDLENGTH_8B;
	uart.Init.StopBits = UART_STOPBITS_1;
	uart.Init.Parity = UART_PARITY_NONE;
	uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart.Init.Mode = UART_MODE_TX_RX;

	BSP_COM_Init(COM1, &uart);
}

void init_GPIO_uart()
{
	//init uart for GPIO purpose with HAL
	//PA9 port 9 pin with AF7 alternate function means USART1_TX - no visible/connecting pin
	//PB9 port 7 pint with AF7 alternate function means USART1_RX - no visible/connecting pin
	/* enable GPIO clock for A and B port*/
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/* configure GPIO for UART transmit line */
	GPIOTxConfig.Pin = GPIO_PIN_9; //chose PA port 9 pin
	GPIOTxConfig.Mode = GPIO_MODE_AF_PP;
	GPIOTxConfig.Pull = GPIO_NOPULL;
	GPIOTxConfig.Speed = GPIO_SPEED_FAST;
	GPIOTxConfig.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOA, &GPIOTxConfig);

	/* configure GPIO for UART receive line */
	GPIORxConfig.Pin = GPIO_PIN_7;
	GPIORxConfig.Mode = GPIO_MODE_AF_PP;
	GPIOTxConfig.Pull = GPIO_NOPULL;
	GPIORxConfig.Speed = GPIO_SPEED_FAST;
	GPIORxConfig.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOB, &GPIORxConfig);

	/* enable the clock of the used peripherial instance */
	__HAL_RCC_USART1_CLK_ENABLE();

	/* defining the UART configuration structure */
	uart.Instance = USART1;
	uart.Init.BaudRate = 115200;
	uart.Init.WordLength = UART_WORDLENGTH_8B;
	uart.Init.StopBits = UART_STOPBITS_1;
	uart.Init.Parity = UART_PARITY_NONE;
	uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart.Init.Mode = UART_MODE_TX_RX;

	HAL_UART_Init(&uart);
}

//init uart for interrupt handle with BSP
void init_uart(void)
{
	__HAL_RCC_USART1_CLK_ENABLE(); //giving clock
	/* defining the UART configuration structure */
	uart_handle.Instance = USART1;
	uart_handle.Init.BaudRate = 115200;
	uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
	uart_handle.Init.StopBits = UART_STOPBITS_1;
	uart_handle.Init.Parity = UART_PARITY_NONE;
	uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart_handle.Init.Mode = UART_MODE_TX_RX;
	// uart_handle.Init.Mode = UART_MODE_TX;
	//uart_handle.Init.Mode = UART_MODE_RX;
	BSP_COM_Init(COM1, &uart_handle);				 //init USART
	HAL_NVIC_SetPriority(USART1_IRQn, 3, 0); //set USART interrupt priority
	HAL_NVIC_EnableIRQ(USART1_IRQn);				 //enable the interrupt to HAL
}
