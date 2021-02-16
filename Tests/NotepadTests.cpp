//
// Created by Admin on 26.01.2021.
//
#include <gtest/gtest.h>
#include "../Notepad.h"

#include "../tests.h"
#define TESTING

using testing::Eq;

namespace
{
    class NotepadTests : public ::testing::Test
    {
    public:
        shop::Notepad notepads;
        NotepadTests()
        {
            notepads;
        }
    };
}


TEST_F(NotepadTests,TestProperSizeAfterReading)
{

    //WHEN
    notepads.readItemsFromFile();

    //THEN
    ASSERT_EQ(notepads.amount.size(),notepads.price.size());
    ASSERT_EQ(notepads.dimensions.size(),notepads.amount.size());

}

TEST_F(NotepadTests,TestReadDateFromFile)
{
    //GIVEN
    notepads;

    //WHEN
    notepads.readItemsFromFile();

    //THEN
    EXPECT_EQ(true,!(notepads.dimensions.empty()));
    EXPECT_EQ(true,!(notepads.amount.empty()));
    EXPECT_EQ(true,!(notepads.price.empty()));

    notepads.saveItemsToFile();
}

TEST_F(NotepadTests,TestReadAddNewNotesToShop)
{
    //GIVEN
    notepads;
    shop::Ware ware;
    Application app;
    app.mode = SELLER_MODE;
    int howMuch = 50;
    int where = 2;



    //WHEN
    notepads.readItemsFromFile();
    int currentAmount = notepads.amount[where];
    notepads.addNotesToShop(app.mode,howMuch,where);
    notepads.saveItemsToFile();
    notepads.readItemsFromFile();


    //THEN
    EXPECT_EQ(currentAmount,notepads.amount[where]);



}

TEST_F(NotepadTests,TestCheckIfChoosenNoteIsAvailble)
{
    //GIVEN
    notepads;
    shop::Ware ware;
    Application app;
    app.mode = SELLER_MODE;
    int where = 1;

    //WHEN
    notepads.readItemsFromFile();

    //THEN
    EXPECT_TRUE(notepads.checkIfNoteIsAvailable(where));

}

TEST_F(NotepadTests,TestAddingtoPurchases)
{
    //GIVEN
    notepads;
    shop::Ware ware;

    std::string name = "N1";
    shop::ware_t price = 12.99;

    //WHEN
    notepads.readItemsFromFile();
    ware.name = name;
    ware.praise = price;

    ware.addToPurchases();

    //THEN
    EXPECT_TRUE(!ware.orderedPurchasesName.empty());
    EXPECT_EQ(ware.orderedPurchasesName.size(),1);

}

TEST_F(NotepadTests,TestRemoveNoteFromBasketToShop)
{
    //GIVEN
    notepads;
    shop::Ware ware;
    Application app;

    app.removedThings.clear();
    app.removedThings.push_back("A6");

    //WHEN
    notepads.readItemsFromFile();
    int currentAmount = notepads.amount[0];

    ware.remove(app.removedThings,notepads.dimensions,notepads.amount);


    //THEN
    EXPECT_EQ(notepads.amount[0],currentAmount + 1);

}
