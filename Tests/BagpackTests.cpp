//
// Created by Admin on 14.02.2021.
//

#include <gtest/gtest.h>
#include "../BagpackManager.h"


#include "../tests.h"
#define TESTING 11

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

TEST_F(BagpackTests, readingBagsFromFile)
{
    //GIVEN
    bagpacks;

    //WHEN
    bagpacks.readItemsFromFile();

    //THEN
    ASSERT_TRUE(!bagpacks.bagsFromFile.empty());
    ASSERT_TRUE(!bagpacks.amountsOfBags.empty());
}

TEST_F(BagpackTests, sizeOfContainersStoraging_Bags_And_Amounts_AreTheSame)
{
    //GIVEN
    bagpacks;

    //WHEN
    bagpacks.readItemsFromFile();

    //THEN
    ASSERT_EQ(bagpacks.amountsOfBags.size(),bagpacks.bagsFromFile.size());
}

TEST_F(BagpackTests, getBackRemovedBagToShop)
{
    //GIVEN
    bagpacks;
    shop::Ware ware;
    Application app;


    //WHEN
    bagpacks.readItemsFromFile();
    int am = bagpacks.amountsOfBags[6];
    app.removedThings.push_back("OlgS");
    bagpacks.saveItemsToFile();
    bagpacks.readItemsFromFile();
    ware.incrementAmountOfReturnedItem(app.removedThings, bagpacks.allMarks, bagpacks.amountsOfBags);

    //THEN
    EXPECT_EQ(am , bagpacks.amountsOfBags[6]);
}


