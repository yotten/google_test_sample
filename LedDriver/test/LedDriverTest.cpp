#include "gtest/gtest.h"

extern "C"
{
#include "../LedDriver.h"
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
//TEST(MinTest, test1) { ASSERT_EQ(min(1, 2), 1); }
//TEST(MinTest, test2) { ASSERT_EQ(min(1, 1), 1); }
//TEST(MinTest, test3) { ASSERT_EQ(min(1, 0), 0); }
//TEST(MaxTest, test1) { ASSERT_EQ(max(1, 2), 2); }
//TEST(MaxTest, test2) { ASSERT_EQ(max(1, 1), 1); }
//TEST(MaxTest, test3) { ASSERT_EQ(max(1, 0), 1); }

