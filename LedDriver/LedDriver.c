#include "LedDriver.h"
#include "RuntimeError.h"
 
static uint16_t *ledsAddress;
static uint16_t ledsImage;

enum {
	ALL_LEDS_OFF = 0,
	ALL_LEDS_ON = ~ALL_LEDS_OFF
};

enum {
	FIRST_LED = 1,
	LAST_LED = 16
};

static void updateHardware(void)
{
	*ledsAddress = ledsImage;
}
 
static uint16_t convertLedNumberToBit(int ledNumber)
{
	return 1 << (ledNumber - 1);
}

static bool is_LedOutOfBounds(int ledNumber)
{
	if ((ledNumber < FIRST_LED) || (LAST_LED < ledNumber)) {
		RUNTIME_ERROR("LedDriver: out-of-bounds LED", ledNumber);
		return true;
	}

	return false;
}

static void clearLedImageBit(int ledNumber) 
{
	ledsImage &= ~(convertLedNumberToBit(ledNumber));
}

static void setLedImageBit(int ledNumber)
{
	ledsImage |= convertLedNumberToBit(ledNumber);	
}
 
void LedDriver_Create(uint16_t *address)
{
	ledsAddress = address;
	ledsImage = ALL_LEDS_OFF;
	*ledsAddress = 0;
}

void LedDriver_Destroy(void)
{
}

void LedDriver_TurnOn(int ledNumber)
{
	if (is_LedOutOfBounds(ledNumber)) {
		return;
	}

	setLedImageBit(ledNumber);
	updateHardware();
}

void LedDriver_TurnOff(int ledNumber)
{
        if (is_LedOutOfBounds(ledNumber)) {
                return;
        }
	
	clearLedImageBit(ledNumber);
	updateHardware();
}

void LedDriver_TurnAllOn(void)
{
	ledsImage = ALL_LEDS_ON; 
	updateHardware();
}

void LedDriver_TurnAllOff(void)
{
	ledsImage = ALL_LEDS_OFF;
	updateHardware();
}

bool LedDriver_IsOn(int ledNumber)
{
	if (is_LedOutOfBounds(ledNumber)) {
		return false;
	}

	return ledsImage & convertLedNumberToBit(ledNumber);
}

bool LedDriver_IsOff(int ledNumber)
{
	return !LedDriver_IsOn(ledNumber);
}

