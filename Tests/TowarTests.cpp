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
    EXPECT_EQ(t1.roundFloatToSecond(54.67833),54.67);
    EXPECT_EQ(t1.roundFloatToSecond(33.17833),33.17);

    EXPECT_EQ(t1.roundFloatToSecond(0.17833766765),0.17);
    EXPECT_EQ(t1.roundFloatToSecond(0.17433),0.17);
    EXPECT_EQ(t1.roundFloatToSecond(11.7886999433),11.78);
    EXPECT_EQ(t1.roundFloatToSecond(4.59000000000001),4.59);
}

