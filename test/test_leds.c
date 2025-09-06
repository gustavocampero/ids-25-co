#include "unity.h"
#include "leds.h"

static uint16_t puerto_virtual;

void setUp(void) {
    LedsInitDriver(&puerto_virtual);
}

void tearDown(void) {
}

void test_al_inciar_todos_los_leds_estan_apagados(void) {
    uint16_t puerto_virtual = 0xFFFF;

    LedsInitDriver(&puerto_virtual);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

void test_prender_un_led_y_verificar_que_no_cambia_el_resto(void) {
    LedsTurnOn(3);
    TEST_ASSERT_EQUAL_HEX16(1 << 2, puerto_virtual);
}

void test_prender_un_led_cualquiera_y_apagarlo(void) {
    LedsTurnOn(5);
    LedsTurnOff(5);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

void test_prender_mas_de_un_led_apagar_uno_y_verificar_que_el_resto_sigue_sin_cambios(void) {
    LedsTurnOn(3);
    LedsTurnOn(5);
    LedsTurnOff(3);
    TEST_ASSERT_EQUAL_HEX16(1 << 4, puerto_virtual);
}
