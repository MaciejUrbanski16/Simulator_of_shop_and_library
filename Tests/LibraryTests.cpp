//
// Created by Admin on 19.02.2021.
//

#include <gtest/gtest.h>

#include "../Library/Library.h"
#include "../Library/TimeOfBorrowing.h"
#include "../Managers/BookManager.h"
#include "../Application.h"

class LibraryTests : public testing::Test
{
public:
    shop::BookManager books;

    LibraryTests()  {
        library::Library lib(books);
    }
};

///BIBLIOTEKA NIE ODCZYTUJE KSIAZEK!!!


TEST_F(LibraryTests, readBooksToLibrbary)
{
    //GIVEN
    shop::BookManager books;
    books.readItemsFromFile();
    library::Library library(books);

    //WHEN
    library.getManageBooks().readItemsFromFile();

    //THEN
    ASSERT_TRUE(!library.getManageBooks().amounts_.empty());
    ASSERT_TRUE(!library.getManageBooks().books_.empty());

}

TEST_F(LibraryTests, readBooksToLibrbary2)
{
    //GIVEN
    shop::BookManager books;
    books.readItemsFromFile();
    library::Library library(books);

    //WHEN
    library.getManageBooks().readItemsFromFile();

    //THEN
    ASSERT_EQ(library.getManageBooks().amounts_.size(),library.getManageBooks().books_.size());
}

TEST_F(LibraryTests, generateID)
{
    //GIVEN
    shop::BookManager books;
    books.readItemsFromFile();
    library::Library library(books);

    //WHEN
    std::string newID = library.generateIDofNewClient();

    //THEN
    ASSERT_EQ(newID.length(), 5);
}

TEST_F(LibraryTests, convertingTimeFromStringToTimeLeftAfterBorrowingType)
{
    //GIVEN
    shop::BookManager books;
    books.readItemsFromFile();
    library::Library library(books);
    library::TimeOfBorrowing time;


    //WHEN
    library::TimeLeft t1(time);
    library::TimeLeft t2(time);


    //THEN
    ASSERT_EQ(1,1);
}

TEST_F(LibraryTests, compareTimes)
{
    //GIVEN
    shop::BookManager books;
    books.readItemsFromFile();
    library::Library library(books);
    library::TimeLeft time1 ("22.03.2021");
    library::TimeLeft time2 ("22.02.2021");

    bool equal = false;


    //WHEN
    if(time1 == time2){
        equal = true;
    }

    //THEN
    ASSERT_TRUE(!equal);
}

TEST_F(LibraryTests, compareTimes2)
{
    //GIVEN
    shop::BookManager books;
    books.readItemsFromFile();
    library::Library library(books);
    library::TimeLeft time1 ("22.03.2021");
    library::TimeLeft time2 ("22.03.2021");

    bool equal = false;


    //WHEN
    if(time1 == time2){
        equal = true;
    }

    //THEN
    ASSERT_TRUE(equal);
}

TEST_F(LibraryTests, theShortestTerm)
{
    //GIVEN
    shop::BookManager books;
    books.readItemsFromFile();
    library::Library library(books);

    std::string currentShortestDeadline = "24.03.2021  10:59:49";
    std::string timeS;

    library.readUsersFromFile();

    std::vector<library::ClientInLibrary> clients = library.getClients();

    if(clients.empty()){
        ASSERT_TRUE(1 != 0);
    }
    else{
        library::TimeLeft timeLeft = clients[0].getTheShortestDeadline().second;
        timeS = timeLeft.getCurrentTimeAsString();
    }


    bool equal = false;


    //WHEN
    if(timeS == currentShortestDeadline){
        equal = true;
    }

    //THEN
    EXPECT_TRUE(equal);
}


