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
} bat_t;


void bat_init();
void bat_adc_callback();


#endif /* __BAT_H__ */