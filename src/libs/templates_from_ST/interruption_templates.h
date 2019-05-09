#include "stm32f7xx.h"
#include "stm32746g_discovery.h"

//create global variable configuration structs
//---------- interrupt handle variables ------------------
GPIO_InitTypeDef user_button_handle;     // the PI11 user button handle structure
GPIO_InitTypeDef external_button_handle; // the B4 external digital(?) button handle structure
UART_HandleTypeDef uart_handle;          // UART config handle structure
TIM_HandleTypeDef tim_handle;            // timer (TIM2) config handle structure
TIM_HandleTypeDef pwm_tim_handle;        // PWM timer (TIM) config handle structure

//----------- no interrupt handle variables -------------
GPIO_InitTypeDef LEDS;            //the external Led config structure
GPIO_InitTypeDef external_button; // the B4 external button structure for general purpose
TIM_OC_InitTypeDef sConfig;       // the output compare channel's config structure for PWM
UART_HandleTypeDef uart;          //the uart config for general purpose
GPIO_InitTypeDef GPIOTxConfig;    //the uart config for general purpose without BSP
GPIO_InitTypeDef GPIORxConfig;    //the uart config for general purpose without BSP
TIM_HandleTypeDef tim;            // timer (TIM2) config structure for general purpose

//---------- task variables -------------------------------
//---------- 2 EXTERNAL BUTTON HANDLER  -------------------
uint32_t last_debounce_time;   // the last time the output pin was toggled
const uint32_t debounce_delay; // the debounce time in ms (increase if the output flickers)
volatile int push_counter;

//---------- 3 USART HANDLER  -----------------------------
volatile char buffer; //to USART (Receiver) interrupt handler

//interrupt handler functions
void init_user_button(void);     //init board user push button PI11 with external interrupt
void init_external_button(void); //init external push button B port 4 pin with external interrupt
void init_uart(void);            //init USART with external interrupt
void init_timer(void);           // init simple timer interrupt

//general functions
void init_external_led();       //external led on F port 7 pin (8, 9 , 10) for general purpose
void init_GPIO_extern_button(); //external button on B post 4 pin for general purpose
void init_GPIO_BSP_uart();      //uart for general purpose with BSP
void init_GPIO_uart();          //uart for general purpose without BSP
void timer_init();              //timer for general purpose (TIM2)
