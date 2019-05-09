/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
#include "interruption_templates.h"
#include "FreeRTOS.h"
#include "task.h"

/*
 * What to do when an assertion fails
 */
void vAssertCalled(uint32_t ulLine, const char *pcFile){};

TaskHandle_t xTaskHandle1 = NULL;
TaskHandle_t xTaskHandle2 = NULL;

void vTask1_handler(void *params);
void vTask2_handler(void *params);

#ifdef USE_SEMIHOSTING
extern void initialise_monitor_handles();
#endif

#define AVAILABLE = 1
#define NOT_AVAILABLE = 0
#define UART_ACCESS_KEY = AVAILABLE

int main(void)
{
#ifdef USE_SEMIHOSTING
  initialise_monitor_handles();
  printf("Using SemiHosting\n");
#endif

  //1. Reset the RCC clock configuration
  HAL_RCC_DeInit(); // Tutorial

  HAL_Init(); //making HAL configuration // Template

  //2. Update the system core clock variable
  SystemCoreClockUpdate(); // Tutorial

  init_GPIO_BSP_uart();
  // could also try init_uart(), but note this one modified uart_handle not uart for some reason

  // LCD_LOG_Init();

  // HAL_UART_Receive_IT(&uart_handle, *(char *)&buffer, 1); //in the case of USART we must do it once in the main before the callback - without this the first callback won't get signal

  xTaskCreate(
      vTask1_handler,
      "Task1",
      configMINIMAL_STACK_SIZE,
      NULL,
      2,
      &xTaskHandle1);

  xTaskCreate(
      vTask2_handler,
      "Task2",
      configMINIMAL_STACK_SIZE,
      NULL,
      2,
      &xTaskHandle2);

  vTaskStartScheduler();

  for (;;)
    ;
}
//
////---------- 3 USART HANDLER  -------------------
//// Not sure if I need these, two methods but they were in the example
//// USART external interrupt handler
//void USART1_IRQHandler()
//{
//  HAL_UART_IRQHandler(&uart_handle);
//}
//// declare week callback function
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//  if (huart->Instance == USART1)
//  {
//    BSP_LED_Toggle(LED_GREEN);
//
//    HAL_UART_Receive_IT(&uart_handle, &buffer, 1);
//  }
//}

void vTask1_handler(void *params)
{
  while (1)
  {
    if (UART_ACCESS_KEY == AVAILABLE)
    {
      UART_ACCESS_KEY = NOT_AVAILABLE;
      printf("1\r\n");
      UART_ACCESS_KEY = AVAILABLE;
      taskYIELD();
    }
  };

  void vTask2_handler(void *params)
  {
    while (1)
    {
      if (UART_ACCESS_KEY == AVAILABLE)
      {
        UART_ACCESS_KEY = NOT_AVAILABLE;
        printf("2\r\n");
        UART_ACCESS_KEY = AVAILABLE;
        taskYIELD();
      }
    }
  };
