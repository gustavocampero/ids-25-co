#include "leds.h"
#include "errores.h"

#define ALL_LED_OFF       0x0000
#define ALL_LED_ON        ~ALL_LED_OFF
#define FIRST_BIT         1
#define LED_TO_BIT_OFFSET 1

static uint16_t * puerto;
static uint16_t LedToMask(int led) {
    return FIRST_BIT << (led - LED_TO_BIT_OFFSET);
}

static bool IsLedValid(int led) {
    bool result = led >= 1 && led <= 16;
    if (!result) {
        RegistrarMensaje(ALERTA, __func__, __LINE__, "El led no es valido");
    }
    return result;
}

void LedsInitDriver(uint16_t * puerto_virtual) {
    puerto = puerto_virtual;
    LedsTurnOffAll();
}

void LedsTurnOn(int led) {
    if (!IsLedValid(led)) {
        return;
    }
    *puerto |= LedToMask(led);
}

void LedsTurnOff(int led) {
    if (!IsLedValid(led)) {
        return;
    }
    *puerto &= ~LedToMask(led);
}

void LedsTurnOnAll(void) {
    *puerto = ALL_LED_ON;
}

void LedsTurnOffAll(void) {
    *puerto = ALL_LED_OFF;
}

uint8_t LedsRead(int led) {
    if (!IsLedValid(led)) {
        return 0;
    }

    return (*puerto & LedToMask(led)) ? 1 : 0;
}
