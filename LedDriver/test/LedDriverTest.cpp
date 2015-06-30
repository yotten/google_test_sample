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

//TEST(MinTest, test1) { ASSERT_EQ(min(1, 2), 1); }
//TEST(MinTest, test2) { ASSERT_EQ(min(1, 1), 1); }
//TEST(MinTest, test3) { ASSERT_EQ(min(1, 0), 0); }
//TEST(MaxTest, test1) { ASSERT_EQ(max(1, 2), 2); }
//TEST(MaxTest, test2) { ASSERT_EQ(max(1, 1), 1); }
//TEST(MaxTest, test3) { ASSERT_EQ(max(1, 0), 1); }

