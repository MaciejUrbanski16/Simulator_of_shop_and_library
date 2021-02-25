//
// Created by Admin on 19.02.2021.
//

#include <gtest/gtest.h>
#include "../Managers/SchoolSuppliesManager.h"

#define TESTING 11

using testing::Eq;

namespace
{
    class SchoolSuppliesTests : public ::testing::Test
    {
    public:
        shop::SchoolSuppliesManager schoolSupplies;
        SchoolSuppliesTests()
        {
            schoolSupplies;
        }
    };
}

TEST_F(SchoolSuppliesTests, readingDataFromFile)
{
    //GIVEN
    schoolSupplies;

    //WHEN
    schoolSupplies.readItemsFromFile();

    //THEN
    ASSERT_TRUE(!schoolSupplies.amounts.empty());
    ASSERT_TRUE(!schoolSupplies.schoolSupplies.empty());
}

TEST_F(SchoolSuppliesTests, readingDataFromFile2)
{
    //GIVEN
    schoolSupplies;

    //WHEN
    schoolSupplies.readItemsFromFile();

    //THEN
    ASSERT_EQ(schoolSupplies.schoolSupplies.size(), schoolSupplies.schoolSupplies.size());
}