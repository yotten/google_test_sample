#include "gtest/gtest.h"

extern "C"
{
#include "sample.h"
}
  
//--------------------------------------------------
// pop2 test
//--------------------------------------------------
TEST(pop, t0) { ASSERT_EQ(add(1, 2), 3); }
TEST(pop, t1) { ASSERT_EQ(add(2, 2), 4); }
 
