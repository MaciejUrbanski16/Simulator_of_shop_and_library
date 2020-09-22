//
// Created by Admin on 22.09.2020.
//

#include <gtest/gtest.h>
#include "../accesories.h"

using testing::Eq;

class TowarTests :public  ::testing::Test
{
public:
    shop::Towar t1;
    TowarTests()
    {
        t1;
    };
};

TEST_F(TowarTests, RoundingFloatTest)
{
    EXPECT_EQ(t1.roundFloatToSecond(12.6545445),12.65);
    EXPECT_EQ(t1.roundFloatToSecond(54.67833),54.68);
}

