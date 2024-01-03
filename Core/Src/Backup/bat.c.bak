#include "bat.h"


uint16_t bat_dma_buf[BATTERY_N];
bat_t batteries[BATTERY_N];


void bat_init() {
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)bat_dma_buf, BATTERY_N);
    HAL_TIM_Base_Start(&htim2);
}


void bat_adc_callback() {
    for (int i = 0; i < BATTERY_N; i++) {
        batteries[i].charge = bat_dma_buf[i];
    }
}