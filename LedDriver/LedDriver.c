#include "LedDriver.h"

static uint16_t *ledsAddress;

enum {
	ALL_LEDS_OFF = 0,
	ALL_LEDS_ON = ~ALL_LEDS_OFF
};
 
static uint16_t convertLedNumberToBit(int ledNumber)
{
	return 1 << (ledNumber - 1);
}

void LedDriver_Create(uint16_t *address)
{
	ledsAddress = address;
	*ledsAddress = 0;
}

void LedDriver_Destroy(void)
{
}

void LedDriver_TurnOn(int ledNumber)
{
	*ledsAddress |= convertLedNumberToBit(ledNumber);
}

void LedDriver_TurnOff(int ledNumber)
{
	*ledsAddress &= ~(convertLedNumberToBit(ledNumber));
}

void LedDriver_TurnAllOn(void)
{
	*ledsAddress = ALL_LEDS_ON; 
}

