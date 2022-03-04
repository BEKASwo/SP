#include <stdio.h>

int main()
{
	unsigned char count = 0;
	unsigned char mask = 0x22;

	unsigned char array[12] = {
		238, 42, 138, 168, 4, 85, 
		219, 137, 182, 15, 65, 99};

	for (char i = 0; i < 12; i++)
	{
		char tmp = array[i];
		tmp = ~tmp;
		tmp = tmp & mask;
		if (tmp == mask)
			count++;

	}

	printf("Count: %d\n", count);

	return 0;
}
