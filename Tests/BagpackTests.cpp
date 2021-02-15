//
// Created by Admin on 14.02.2021.
//

#include <gtest/gtest.h>
#include "../BagpackManager.h"


#include "../tests.h"
#define TESTING

using testing::Eq;

namespace
{
    class BagpackTests : public ::testing::Test
    {
    public:
        shop::BagpackManager bagpacks;
        BagpackTests()
        {
            bagpacks;
        }
    };
}
