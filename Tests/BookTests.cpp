//
// Created by Admin on 11.02.2021.
//

#include <gtest/gtest.h>

#include "../Book.h"
#include "../Application.h"

class BookTests : public testing::Test
{
public:
    shop::Book book;
    BookTests()
    {
        book;
    }
};

TEST_F(BookTests, readProperValuesOfBooks)
{
    //GIVEN
    book;

    //WHEN
    book.readItemsFromFile();

    //THEN
    EXPECT_TRUE(!book.titleOfBooksInShop.empty());
    EXPECT_TRUE(!book.pricesOfBooksInShop.empty());
    EXPECT_TRUE(!book.amountOfBooksInShop.empty());
}

/*TEST_F(BookTests, returnBookFromBasketToShop)
{
    //GIVEN
    book;
    Application app;


    //WHEN
    book.readItemsFromFile();

    int currentAmount = book.amountOfBooksInShop[0];
    app.removedThings.push_back(book.titleOfBooksInShop[0]);

    app.saveRemovedToFile();
    app.readRemoveFromFile();
    book.searchInRemoved(app);

    //THEN
    EXPECT_EQ(currentAmount + 1 , book.amountOfBooksInShop[0]);
}*/

TEST_F(BookTests, searchingBookAfterEnteredLetter)
{
    //GIVEN
    book;

    //WHEN
    book.readItemsFromFile();

    //THEN
    EXPECT_EQ(shop::Book::FOUND,book.searchingBook());

}

TEST_F(BookTests, searchingBookAfterEnteredLetterIfNotFound)
{
    //GIVEN
    book;

    //WHEN
    book.readItemsFromFile();
    book.searchingBook();

    //THEN
    EXPECT_EQ(book.getSizeOfCurrentSearchings(),1);

}

TEST_F(BookTests, checkIfBookExist)
{
    //GIVEN
    book;
    std::string title1 = "Dluga_noc";
    std::string title2 = "Sami_swoi";

    //WHEN
    book.readItemsFromFile();


    //THEN
    EXPECT_EQ(book.checkIfBookExist(title1),0);
    EXPECT_EQ(book.checkIfBookExist(title2),3);

}

TEST_F(BookTests, addBookToShop)
{
    //GIVEN
    book;
    std::string title1 = "Dluga_noc_1";
    std::string title2 = "Sami_swoi_1";

    //WHEN
    book.readItemsFromFile();



    //THEN
    EXPECT_EQ(book.checkIfBookExist(title1),-1);
    EXPECT_EQ(book.checkIfBookExist(title2),-1);

}

TEST_F(BookTests, checkAmountOfChoosenBook)
{
    //GIVEN
    book;
    Application app;
    shop::Ware ware;
    std::string title1 = "Dluga_noc_1";
    std::string title2 = "Sami_swoi_1";

    //WHEN
    book.readItemsFromFile();
    book.titleOfBooksInShop.push_back(title1);
    book.amountOfBooksInShop.push_back(25);
    book.pricesOfBooksInShop.push_back(11.99);

    ware.position = book.checkIfBookExist(title1);

    //THEN
    EXPECT_TRUE(book.checkAmountofBookInShop(ware));

}

