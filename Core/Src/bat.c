#include "bat.h"
#include <memory.h>


#define BAT_CELL_MAX_VOLT 4.2f
#define BAT_CELL_NOM_VOLT 3.7f
#define BAT_MAX_READ_VOLT 2.1f
#define BAT_MAX_ADC_VAL 2605.0f
#define BAT_LPF_ALPHA 0.1f

#define BAT_1ST_STEP 4.0f
#define BAT_2ST_STEP 3.8f

uint32_t bat_last_time_ms;
uint32_t bat_curr_time_ms;

uint16_t bat_dma_buf[MAX_BATTERY_N];
uint8_t bat_undervolt_arr[MAX_BATTERY_N];
bat_t batteries[MAX_BATTERY_N];


static void bat_undervolt_err();


/**
  * @brief Starts ADC+DMA and TIM2; counts how many batteries are connected
  *        through the DIP Switch
  */
void bat_init() {
    //batteries[0].led_ports[0]    = BAT0_LED0_GPIO_Port;
    //batteries[0].led_ports[1]    = BAT0_LED1_GPIO_Port;
    //batteries[0].led_pins[0]     = BAT0_LED0_Pin;
    //batteries[0].led_pins[1]     = BAT0_LED1_Pin;
    //batteries[0].is_connected    = 1; // I mean, otherwise this line of code wouldn't be executed

    //  batteries[1].led_ports[0]    = BAT1_LED0_GPIO_Port;
    //batteries[1].led_ports[1]    = BAT1_LED1_GPIO_Port;
    //batteries[1].led_pins[0]     = BAT1_LED0_Pin;
    //batteries[1].led_pins[1]     = BAT1_LED1_Pin;
    //batteries[1].is_connected    = HAL_GPIO_ReadPin(BAT_SEL_1_GPIO_Port, BAT_SEL_1_Pin);

    //batteries[2].led_ports[0]    = BAT2_LED0_GPIO_Port;
    //batteries[2].led_ports[1]    = BAT2_LED1_GPIO_Port;
    //batteries[2].led_pins[0]     = BAT2_LED0_Pin;
    //batteries[2].led_pins[1]     = BAT2_LED1_Pin;
    //batteries[2].is_connected    = HAL_GPIO_ReadPin(BAT_SEL_2_GPIO_Port, BAT_SEL_2_Pin);

    //batteries[3].led_ports[0]    = BAT3_LED0_GPIO_Port;
    //batteries[3].led_ports[1]    = BAT3_LED1_GPIO_Port;
    //batteries[3].led_pins[0]     = BAT3_LED0_Pin;
    //batteries[3].led_pins[1]     = BAT3_LED1_Pin;
    //batteries[3].is_connected    = HAL_GPIO_ReadPin(BAT_SEL_3_GPIO_Port, BAT_SEL_3_Pin);

    //batteries[4].led_ports[0]    = BAT4_LED0_GPIO_Port;
    //batteries[4].led_ports[1]    = BAT4_LED1_GPIO_Port;
    //batteries[4].led_pins[0]     = BAT4_LED0_Pin;
    //batteries[4].led_pins[1]     = BAT4_LED1_Pin;
    //batteries[4].is_connected    = HAL_GPIO_ReadPin(BAT_SEL_4_GPIO_Port, BAT_SEL_4_Pin);

    memset(bat_undervolt_arr, 0, MAX_BATTERY_N);

    bat_last_time_ms = HAL_GetTick();

    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)bat_dma_buf, MAX_BATTERY_N);
    HAL_TIM_Base_Start(&htim2);
}


/**
  * @brief When ready, saves the DMA buffered data into the memory
  */
void bat_adc_callback() {
    float tmp;

    for (uint8_t i = 0; i < MAX_BATTERY_N; i++) {
        if (batteries[i].is_connected) {
            tmp = ((float)bat_dma_buf[i] / BAT_MAX_ADC_VAL) * BAT_CELL_MAX_VOLT;
            batteries[i].charge = ((1.0f - BAT_LPF_ALPHA) * tmp) + (BAT_LPF_ALPHA * batteries[i].charge);
        }
    }
}


/**
 * @brief Every BAT_POLLING_PERIOD this function will check any undervoltage on
 *        the batteries, if so, it will call bat_undervolt_err(), it also
 *        updates LEDs values
 */
void bat_volt_check() {
    uint8_t flg = 0;
    bat_curr_time_ms = HAL_GetTick();

    if (bat_curr_time_ms - bat_last_time_ms < BAT_POLLING_PERIOD) {
        return;
    }

    for (uint8_t i = 0; i < MAX_BATTERY_N; i++) {
        if (batteries[i].charge <= BAT_CELL_NOM_VOLT) {
            bat_undervolt_arr[i] = 1;
            flg = 1;
        }
        
        if (batteries[i].charge >= BAT_1ST_STEP) {
            batteries[i].led_status[0] = 1;
            batteries[i].led_status[1] = 1;
        } else if (batteries[i].charge >= BAT_2ST_STEP) {
            batteries[i].led_status[0] = 1;
            batteries[i].led_status[1] = 0;
        } else {
            batteries[i].led_status[0] = 0;
            batteries[i].led_status[1] = 0;
        }

        #if DEBUG
            char buf[50];
            sprintf(buf, "bat[%d]: %d\r\n", i, (uint16_t)(batteries[i].charge*1000));
            HAL_UART_Transmit(&huart2, (uint8_t *)buf, strlen(buf), 100);
        #endif /* DEBUG */
    }

    if (flg) {
        bat_undervolt_err();
    }

    bat_last_time_ms = bat_curr_time_ms;
}


/**
 * @brief Turns the LEDs ON or OFF based on led_status field of each battery
 *        struct; starts the htim3 in interrupt mode
 */
void bat_led_status_on_callback() {
    for (uint8_t i = 0; i < MAX_BATTERY_N; i++) {
        for (uint8_t j = 0; j < BAT_LED_N; j++) {
            HAL_GPIO_WritePin(batteries[i].led_ports[j], 
                              batteries[i].led_pins[j],
                              batteries[i].led_status[j]);
        }
    }

    HAL_TIM_Base_Start_IT(&htim3);
}


/**
 * @brief Called from HAL_TIM_PeriodElapsedCallback, turns OFF all batteries
 *        status LEDs
 */
void bat_led_status_off_callback() {
    for (uint8_t i = 0; i < MAX_BATTERY_N; i++) {
        for (uint8_t j = 0; j < BAT_LED_N; j++) {
            HAL_GPIO_WritePin(batteries[i].led_ports[j], 
                              batteries[i].led_pins[j],
                              RESET);
        }
    }

    HAL_TIM_Base_Stop_IT(&htim3);
}


float bat_get_cell_volt(uint8_t cell_n) {
    return batteries[cell_n].charge;
}


/**
 * @brief Sends an undervoltage error message on CAN Bus
 */
static void bat_undervolt_err() {
    can_send_bat_err(bat_undervolt_arr);
    /* TODO: in the future, this function will handle the battery connection */
}