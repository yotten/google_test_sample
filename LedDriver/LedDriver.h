#ifndef D_LEDDRIVER_H
#define D_LEDDRIVER_H

#include <stdint.h>

void LedDriver_Create(uint16_t *address);
void LedDriver_Destroy(void);
void LedDriver_TurnOn(int ledNumber);
void LedDriver_TurnOff(int ledNumber);
void LedDriver_TurnAllOn(void);
void LedDriver_IsOn(int ledNumber);

#endif /* D_LEDDRIVER_H */
