/*
#include "ThisThread.h"
#include <mbed.h>

DigitalOut oled1(LED1);
InterruptIn ibutton1(BUTTON1);
static auto sleep_time = 1000ms;

void pressed()
{
    sleep_time += 250ms;
    if (sleep_time > 1000ms)
        sleep_time = 250ms;
}

void released()
{

}

Ticker  toggle_led_ticker;

void led_ticker()
{
    oled1 =!oled1;
}

int main()
{
    toggle_led_ticker.attach(&led_ticker, sleep_time);

    ibutton1.fall(&released);
    ibutton1.rise(&pressed);

}
*/

/*
#include "ThisThread.h"
#include <mbed.h>

#define PRINT_FLAG 66
Thread thread;



void print_thread()
{
    while (ThisThread::flags_get() != PRINT_FLAG)
    {
        printf("Hello from Thread1 :D\n");
        ThisThread::sleep_for(500ms);
    }

    printf("Goodbye AMERICA\n");
}


int main()
{
    thread.start(print_thread);

    ThisThread::sleep_for(5s);
    thread.flags_set(PRINT_FLAG);
}
*/

//#include "InterruptIn.h"
#include "MemoryPool.h"
#include "ThisThread.h"
#include "cmsis_os.h"
#include <cstdint>
#include <mbed.h>
#include <string.h>


DigitalOut led1(PA_9);

InterruptIn but1(BUTTON1);
InterruptIn but2(PC_7);


typedef struct {
    uint32_t       code;
} message_t;

MemoryPool<message_t, 16> mpool;
Queue<message_t, 16> queue;
Thread thread;


void led_line()
{
    led1.write(1);
    ThisThread::sleep_for(600ms);
    led1.write(0);
    ThisThread::sleep_for(200ms);
}

void led_point()
{
    led1.write(1);
    ThisThread::sleep_for(200ms);
    led1.write(0);
    ThisThread::sleep_for(200ms);
}

void led_code(int code)
{
    switch (code) {
        case 0:
            led1.write(1);
            ThisThread::sleep_for(5s);
            led1.write(0);
            break;

        case 1:
            for (int i = 0; i < 3; i++)
                led_point();
            for (int i = 0; i < 3; i++)
                led_line();
            for (int i = 0; i < 3; i++)
                led_point();
            break;

        case 2:
            for (int i = 0; i < 4; i++)
            {
                led_point();
                led_line();
            }
            break;

        case 3:
            for (int i = 0; i < 4; i++)
                led_point();
            for (int i = 0; i < 4; i++)
                led_line();
            break;
    }
}


void send_thread(void)
{
    uint32_t i = 0;

    while (true) {
        
        if (but2)
        {
            ThisThread::sleep_for(200);
            i++;
            if (i > 3)
                i = 1;

            
        }
        
        if (!but1)
        {
            ThisThread::sleep_for(200);
            message_t *message = mpool.alloc();
            message->code = i;
            queue.put(message);
            

            i = 0;
        }
    }
}

int main(void)
{
    thread.start(callback(send_thread));

    while(true)
    {
        osEvent evt = queue.get();
        if (evt.status == osEventMessage)
        {
            message_t *message = (message_t *)evt.value.p;
            printf("\nPhrase code: %d V\n\r", message->code);

            led_code(message->code);

            mpool.free(message);
        }
    }
}