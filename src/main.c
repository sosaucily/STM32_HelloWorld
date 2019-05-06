/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f7xx.h"
#include "stm32746g_discovery.h"

/*
 * What to do when an assertion fails
 */
void vAssertCalled(uint32_t ulLine, const char *pcFile){};

int main(void)
{

  //1. Reset the RCC clock configuration
  HAL_RCC_DeInit();

  for (;;)
    ;
}
