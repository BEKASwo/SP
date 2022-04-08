#include <mbed.h>
#include "BME280.h"

#define ADDRESS_BME280 (0x76 << 1)

I2C i2c(PB_9, PB_8); // SDA pin, SCL pin
BME280 sensor(PB_9, PB_8);


int main()
{
    int address = (0x76 << 1);
    char cmd[4];

    cmd[0] = 0xD0;
    i2c.write(address, &cmd[0], 1);
    i2c.read(address, &cmd[1], 1);

    printf("CHIP ID: %d\n", cmd[1]);
	
    while (1)
    {
        printf("Temp: %d\n", (int)sensor.getTemperature());
        ThisThread::sleep_for(1000);
    }
}
