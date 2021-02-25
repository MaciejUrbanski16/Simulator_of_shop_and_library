//
// Created by Admin on 26.01.2021.
//
#include <gtest/gtest.h>
#include "../Managers/NotepadManager.h"

#define TESTING

using testing::Eq;

namespace
{
    class NotepadTests : public ::testing::Test
    {
    public:
        shop::NotepadManager notepads;
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
    ASSERT_EQ(notepads.amounts.size(),notepads.notepads.size());


}

TEST_F(NotepadTests,TestReadDateFromFile)
{
    //GIVEN
    notepads;

    //WHEN
    notepads.readItemsFromFile();

    //THEN
    EXPECT_EQ(true,!(notepads.notepads.empty()));
    EXPECT_EQ(true,!(notepads.amounts.empty()));


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
    int currentAmount = notepads.amounts[where];
    notepads.addNotesToShop(app.mode,howMuch,where);
    notepads.saveItemsToFile();
    notepads.readItemsFromFile();


    //THEN
    EXPECT_EQ(currentAmount,notepads.amounts[where]);



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
    int currentAmount = notepads.amounts[0];
    std::vector<std::string> formats = notepads.getFormats();
    ware.incrementAmountOfReturnedItem(app.removedThings, formats, notepads.amounts);


    //THEN
    EXPECT_EQ(notepads.amounts[0],currentAmount + 1);

}
