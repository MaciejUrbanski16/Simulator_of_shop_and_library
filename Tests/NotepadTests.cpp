//
// Created by Admin on 06.09.2020.
//
#include <gtest/gtest.h>
#include "../Notepad.h"

#include "../tests.h"

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
    int  p =4;
    //EXPECT_EQ(p,enteringTheNumber(3,5));
    EXPECT_EQ(1,1);

}

TEST_F(NotepadTests,Test1)
{
    n1.readItemsFromFile();
    int roz = n1.dimensions.size();



    int roz2 = n1.amount.size();
    int roz3 = n1.price.size();

    EXPECT_EQ(roz,roz2);
    EXPECT_EQ(roz2,roz3);

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
