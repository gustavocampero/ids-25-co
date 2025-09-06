#include "leds.h"

#define ALL_LED_OFF       0x0000
#define FIRST_BIT         1
#define LED_TO_BIT_OFFSET 1

static uint16_t * puerto;
static uint16_t LedToMask(int led) {
    return FIRST_BIT << (led - LED_TO_BIT_OFFSET);
}

void LedsInitDriver(uint16_t * puerto_virtual) {
    puerto = puerto_virtual;
    *puerto = ALL_LED_OFF;
}

void LedsTurnOn(int led) {
    *puerto |= LedToMask(led);
}

void LedsTurnOff(int led) {
    *puerto &= ~LedToMask(led);
}
