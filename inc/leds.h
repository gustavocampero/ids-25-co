#include <stdint.h>
#include <stdbool.h>

void LedsInitDriver(uint16_t * puerto_virtual);

void LedsTurnOn(int led);
void LedsTurnOff(int led);

void LedsTurnOnAll(void);
void LedsTurnOffAll(void);

uint8_t LedsRead(int led);
