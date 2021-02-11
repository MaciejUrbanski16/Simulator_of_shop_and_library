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
        shop::Notepad n1;
        NotepadTests()
        {
            n1;
        }
    };
}

TEST(EnteringNumbers, TEST1)
{
    shop::Ware w;
    int  p =4;
   // EXPECT_EQ(p,w.enteringTheNumber(3,5));
    EXPECT_EQ(1,1);

}

TEST_F(NotepadTests,Test1)
{
    //WHEN
    n1.readItemsFromFile();

    //THEN
    EXPECT_EQ(n1.amount.size(),n1.price.size());
    EXPECT_EQ(n1.dimensions.size(),n1.amount.size());

}

TEST_F(NotepadTests,Test2)
{
    EXPECT_EQ(true, true);
}


TEST_F(NotepadTests,Test3)
{
EXPECT_EQ(true, 1);
}

///*Sprobuje napisac test do odczytywania danych z plikow  txt porownujac rozmiary

/*TEST_F(NotepadTests,TestReadDateFromFile)
{
    int n =4;
    n1.readItemsFromFile();

    EXPECT_EQ(4,n1.dimensions.size());
    EXPECT_EQ(4,n1.amount.size());
    EXPECT_EQ(4,n1.price.size());

    n1.saveItemsToFile();
}*/
