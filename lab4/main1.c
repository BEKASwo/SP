#include <stdbool.h>
#include <stdint.h>
#include "nrf_drv_systick.h"
#include "boards.h"

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    /* Configure LED-pins as outputs. */
    bsp_board_init(BSP_INIT_LEDS);
    //bsp_board_button_idx_to_pin();

    /* Init systick driver */
    nrf_drv_systick_init();

    /* Toggle LEDs. */

    bool set = false;
    while (true)
    {
        for (int i = 0; i < LEDS_NUMBER; i++)
        {
            bsp_board_led_invert(i);
            nrf_drv_systick_delay_ms(500);
        }
    }
}

/**
 *@}
 **/
