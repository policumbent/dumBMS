#ifndef __BAT_H__
#define __BAT_H__

#include "adc.h"
#include "tim.h"

#define BATTERY_N 4     /* has to be the same as the batteries slots */
#define BAT_LED_N 3     /* has to be the same as status leds for each battery */

typedef struct {
    uint16_t charge;
    uint8_t led_status[BAT_LED_N];
} bat_t;

void bat_init();

#endif /* __BAT_H__ */