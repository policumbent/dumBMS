#ifndef __BAT_H__
#define __BAT_H__


#include "adc.h"
#include "tim.h"


#define MAX_BATTERY_N 5     /* has to be the same as the batteries slots ->
                             * - 4x 3S: general bike powering
                             * - 1x 2S: DumBMS powering                       */

#define BAT_LED_N 2     /* has to be the same as status leds for each battery */


typedef struct {
    float charge;
    uint8_t led_status[BAT_LED_N];
    GPIO_TypeDef* led_ports[BAT_LED_N];
    uint16_t led_pins[BAT_LED_N];
} bat_t;


void bat_init();
void bat_adc_callback();
void bat_led_status_on_callback();
void bat_led_status_off_callback();


#endif /* __BAT_H__ */