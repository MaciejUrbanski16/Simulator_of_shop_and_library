//
// Created by Admin on 19.02.2021.
//

#include <gtest/gtest.h>

#include "../Library/Library.h"
#include "../BookManager.h"
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