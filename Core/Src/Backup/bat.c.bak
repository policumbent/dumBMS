#include "bat.h"


uint16_t bat_dma_buf[MAX_BATTERY_N];
uint8_t battery_n = 1;
bat_t batteries[MAX_BATTERY_N];


/**
  * @brief Starts ADC+DMA and TIM2; counts how many batteries are connected
  *        through the DIP Switch
  */
void bat_init() {
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)bat_dma_buf, MAX_BATTERY_N);
    HAL_TIM_Base_Start(&htim2);

    battery_n += HAL_GPIO_ReadPin(BAT_SEL_0_GPIO_Port, BAT_SEL_0_Pin);
    battery_n += HAL_GPIO_ReadPin(BAT_SEL_1_GPIO_Port, BAT_SEL_1_Pin);
    battery_n += HAL_GPIO_ReadPin(BAT_SEL_2_GPIO_Port, BAT_SEL_2_Pin);
    battery_n += HAL_GPIO_ReadPin(BAT_SEL_3_GPIO_Port, BAT_SEL_3_Pin);
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