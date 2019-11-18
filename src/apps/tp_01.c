#include "../apps.h"

void tp_01(void) {
    DDR_OUTPUT(B, PB7);
    DDR_INPUT(D, PD7);
    uint8_t button_history = 0;
    long press_cycles = 0;

    led_init();

    for(;;) {
        button_update(&button_history, PIN_IS_HIGH(D, PD7));

        if (button_is_down(&button_history)) {
            press_cycles++;
        }

        if (button_is_released(&button_history)) {
            if (press_cycles > CYCLES_IN_SECOND) {
                led_frequency_rotate();
                printf("LONG PRESS (%lu c): changed frequency to %uHz\n",
                       press_cycles,
                       led_frequency_get_hertz());
            } else {
                led_duty_cycle_rotate();
                printf("QUICK PRESS (%lu c): changed duty_cycle to %u%%\n",
                       press_cycles,
                       led_duty_cycle_get_percentage());
            }
            press_cycles = 0;
        }
    }
}
