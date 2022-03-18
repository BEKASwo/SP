#include <stdbool.h>
#include <stdint.h>
#include "nrf_drv_systick.h"
#include "boards.h"

int main(void)
{
    /* Configure LED-pins as outputs. */
    bsp_board_init(BSP_INIT_LEDS);
    bsp_board_init(BSP_INIT_BUTTONS);
    //bsp_board_button_idx_to_pin();

    /* Init systick driver */
    nrf_drv_systick_init();

    /* Toggle LEDs. */

    bool set = false;
    while (true)
    { 
        if (bsp_board_button_state_get(1))
        {
          set = !set;
        }

        if(set)
          bsp_board_led_off(1);
        else
          bsp_board_led_on(1);

    }
}

