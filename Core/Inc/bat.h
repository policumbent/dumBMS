#ifndef __BAT_H__
#define __BAT_H__


#include "adc.h"
#include "tim.h"
#include "can_dumbms.h"


#define MAX_BATTERY_N 5     /* has to be the same as the batteries slots ->
                             * - 4x 3S: general bike powering
                             * - 1x 2S: DumBMS powering                       */

#define BAT_LED_N 2     /* has to be the same as status leds for each battery */

#define BAT_POLLING_PERIOD 1000u


typedef struct {
    float charge;
    uint8_t led_status[BAT_LED_N];
    uint8_t is_connected;
    GPIO_TypeDef* led_ports[BAT_LED_N];
    uint16_t led_pins[BAT_LED_N];
} bat_t;


void bat_init();
void bat_adc_callback();
void bat_volt_check();
void bat_led_status_on_callback();
void bat_led_status_off_callback();

float bat_get_cell_volt(uint8_t cell_n);


#endif /* __BAT_H__ */