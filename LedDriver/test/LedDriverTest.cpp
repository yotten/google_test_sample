#include "gtest/gtest.h"

extern "C"
{
#include "../LedDriver.h"
#include "../RuntimeError.h"
#include "../mocks/RuntimeErrorStub.h" 
}

static uint16_t virtualLeds;

class LedDriver : public :: testing :: Test {
protected:
	virtual void SetUp() {
		LedDriver_Create(&virtualLeds);
	}

	virtual void TearDown() {
		
	}
};

class DISABLED_LedDriver : public :: testing :: Test {};
TEST_F(LedDriver, LedsOffAfterCreate)
{
	uint16_t virtualLeds = 0xffff;

	LedDriver_Create(&virtualLeds);
	ASSERT_EQ(0, virtualLeds);
}

TEST_F(LedDriver, TurnOnLedOne)
{
	LedDriver_TurnOn(1);
	ASSERT_EQ(1, virtualLeds);	
}

TEST_F(LedDriver, TurnOffLedOne)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOff(1);
	ASSERT_EQ(0, virtualLeds);
}

TEST_F(LedDriver, TurnOnMultipleLeds)
{
	LedDriver_TurnOn(9);
	LedDriver_TurnOn(8);
	ASSERT_EQ(0x0180, virtualLeds);
}

TEST_F(LedDriver, TurnOffAnyLed)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(8);
	ASSERT_EQ(0xff7f, virtualLeds);
}

TEST_F(LedDriver, AllOn)
{
	LedDriver_TurnAllOn();
	ASSERT_EQ(0xffff, virtualLeds);
}

TEST_F(LedDriver, LedMemoryIsNotReadable)
{
	virtualLeds = 0xffff;
	LedDriver_TurnOn(8);
	ASSERT_EQ(0x80, virtualLeds);
}

TEST_F(LedDriver, UpperAndLowerBounds)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOn(16);
	ASSERT_EQ(0x8001, virtualLeds);	
}

TEST_F(LedDriver, OutOfBoundsChangesNothing)
{
	LedDriver_TurnOn(-1);
	LedDriver_TurnOn(0);
	LedDriver_TurnOn(17);
	LedDriver_TurnOn(3141);
	ASSERT_EQ(0, virtualLeds);	
}

TEST_F(LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
	LedDriver_TurnAllOn();
        LedDriver_TurnOff(-1);
        LedDriver_TurnOff(0);
        LedDriver_TurnOff(17);
        LedDriver_TurnOff(3141);
        ASSERT_EQ(0xffff, virtualLeds);
}

TEST_F(LedDriver, OutOfBoundsProducesRuntimeError)
{
	LedDriver_TurnOn(-1);
	ASSERT_STREQ("LedDriver: out-of-bounds LED", RuntimeErrorStub_GetLastError());
	ASSERT_EQ(-1, RuntimeErrorStub_GetLastParameter());
}

TEST_F(DISABLED_LedDriver, OutOfBoundsToDo)
{
	/* TODO */
}

TEST_F(LedDriver, IsOn)
{
	ASSERT_FALSE(LedDriver_IsOn(11));
	LedDriver_TurnOn(11);
	ASSERT_TRUE(LedDriver_IsOn(11));
}

TEST_F(LedDriver, OutOfBoundsLedsAreAlwaysOff)
{
	ASSERT_FALSE(LedDriver_IsOn(0));
	ASSERT_FALSE(LedDriver_IsOn(17));
	ASSERT_TRUE(LedDriver_IsOff(0));
	ASSERT_TRUE(LedDriver_IsOff(17));
}

TEST_F(LedDriver, IsOff)
{
	ASSERT_TRUE(LedDriver_IsOff(12));
	LedDriver_TurnOn(12);
	ASSERT_FALSE(LedDriver_IsOff(12));
}

TEST_F(LedDriver, TurnOffMultipleLeds)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(9);
	LedDriver_TurnOff(8);
	ASSERT_EQ((~0x180)&0xffff, virtualLeds);	
}

TEST_F(LedDriver, AllOff)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnAllOff();
	ASSERT_EQ(0, virtualLeds);	
}

