#include "button.h"


uint32_t but_last_time_ms;
uint32_t but_curr_time_ms;
button_t but_bat_stat;


static void button_val_init(button_t *button, GPIO_TypeDef *port, uint16_t pin);
static uint8_t button_update_val(button_t *button);


void button_init() {
    button_val_init(&but_bat_stat, BUT_BAT_STAT_LED_GPIO_Port, BUT_BAT_STAT_LED_Pin);

    but_last_time_ms = HAL_GetTick();
}


void button_polling() {
    but_curr_time_ms = HAL_GetTick();

    if (but_curr_time_ms - but_last_time_ms >= BUTTON_POLLING_PERIOD) {
        if (!button_update_val(&but_bat_stat)) {
            bat_led_status_on_callback();
        }

        but_last_time_ms = HAL_GetTick();
    }
}


static void button_val_init(button_t *button, GPIO_TypeDef *port, uint16_t pin) {
    button->val_previous = 0;
    button->val_current = 0;
    button->val_debounced = 0;
    button->is_toggled = 0;
    button->port = port;
    button->pin = pin;
}


static uint8_t button_update_val(button_t *button) {
    button->val_current = HAL_GPIO_ReadPin(button->port, button->pin);

    if (button->val_previous != button->val_current) {
        button->is_toggled = 1;
        button->val_previous = button->val_current;
    } else if (button->is_toggled) {
        button->is_toggled = 0;
        button->val_debounced = button->val_previous;
    }

    return button->val_debounced;
}