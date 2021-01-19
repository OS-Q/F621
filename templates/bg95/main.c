#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <dam.h>
#include <qapi_uart.h>
#include <qapi_timer.h>
#include <quectel_utils.h>
#include <quectel_uart_apis.h>

void *_sbrk(int incr) { return (void *)-1; }

int main(void)
{
    /* setup */
    while (1)
    {
        /* loop */
        qapi_Timer_Sleep(1, QAPI_TIMER_UNIT_SEC, 1);
    }
}
