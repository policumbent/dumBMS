#include "bat.h"


uint16_t bat_dma_buf[MAX_BATTERY_N];
uint8_t battery_n = 1;
bat_t batteries[MAX_BATTERY_N];


/**
  * @brief Starts ADC+DMA and TIM2; counts how many batteries are connected
  *        through the DIP Switch
  */
void bat_init() {
    battery_n += HAL_GPIO_ReadPin(BAT_SEL_1_GPIO_Port, BAT_SEL_1_Pin);
    battery_n += HAL_GPIO_ReadPin(BAT_SEL_2_GPIO_Port, BAT_SEL_2_Pin);
    battery_n += HAL_GPIO_ReadPin(BAT_SEL_3_GPIO_Port, BAT_SEL_3_Pin);
    battery_n += HAL_GPIO_ReadPin(BAT_SEL_4_GPIO_Port, BAT_SEL_4_Pin);

    batteries[0].led_ports[0] = BAT0_LED0_GPIO_Port;
    batteries[0].led_ports[1] = BAT0_LED1_GPIO_Port;
    batteries[0].led_pins[0]  = BAT0_LED0_Pin;
    batteries[0].led_pins[1]  = BAT0_LED1_Pin;

    batteries[1].led_ports[0] = BAT1_LED0_GPIO_Port;
    batteries[1].led_ports[1] = BAT1_LED1_GPIO_Port;
    batteries[1].led_pins[0]  = BAT1_LED0_Pin;
    batteries[1].led_pins[1]  = BAT1_LED1_Pin;

    batteries[2].led_ports[0] = BAT2_LED0_GPIO_Port;
    batteries[2].led_ports[1] = BAT2_LED1_GPIO_Port;
    batteries[2].led_pins[0]  = BAT2_LED0_Pin;
    batteries[2].led_pins[1]  = BAT2_LED1_Pin;

    batteries[3].led_ports[0] = BAT3_LED0_GPIO_Port;
    batteries[3].led_ports[1] = BAT3_LED1_GPIO_Port;
    batteries[3].led_pins[0]  = BAT3_LED0_Pin;
    batteries[3].led_pins[1]  = BAT3_LED1_Pin;

    batteries[4].led_ports[0] = BAT4_LED0_GPIO_Port;
    batteries[4].led_ports[1] = BAT4_LED1_GPIO_Port;
    batteries[4].led_pins[0]  = BAT4_LED0_Pin;
    batteries[4].led_pins[1]  = BAT4_LED1_Pin;

    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)bat_dma_buf, MAX_BATTERY_N);
    HAL_TIM_Base_Start(&htim2);
}


/**
  * @brief When ready, saves the DMA buffered data into the memory
  */
void bat_adc_callback() {
    for (int i = 0; i < battery_n; i++) {
        /* TODO: implement a low pass filter and conversion from raw adc data to
        actual voltage value */ 
        batteries[i].charge = bat_dma_buf[i];
    }
}