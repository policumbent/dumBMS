#ifndef __BUTTON_H__
#define __BUTTON_H__


#include "main.h"
#include "bat.h"


#define POLLING_PERIOD 50U


typedef struct {
    uint8_t val_previous;
    uint8_t val_current;
    uint8_t val_debounced;
    uint8_t is_toggled;
    GPIO_TypeDef *port;
    uint16_t pin;
} button_t;


void button_init();
void button_polling();


#endif /* __BUTTON_H__ */