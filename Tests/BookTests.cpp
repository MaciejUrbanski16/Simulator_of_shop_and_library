//
// Created by Admin on 11.02.2021.
//

#include <gtest/gtest.h>

#include "../Managers/BookManager.h"
#include "../Application.h"

class BookTests : public testing::Test
{
public:
    shop::BookManager books;
    BookTests()
    {
        books;
    }
};

TEST_F(BookTests, readingBooksFromFileToContainerOfBooksObjects)
{
    //GIVEN
    books;

    //WHEN
    books.readItemsFromFile();
    std::vector<shop::ConcreteBook> read = books.getBooks();

    //THEN
    ASSERT_TRUE(!read.empty());
}

TEST_F(BookTests, findingConcreteBook)
{
    //GIVEN
    books;
    std::string title = "Bajki robotow";
    //WHEN
    books.readItemsFromFile();
    std::vector<shop::ConcreteBook> read = books.getBooks();

    //THEN
    ASSERT_EQ(title.length(), read[0].getPairOfTitleAndAuthorBook().second.length());
}

TEST_F(BookTests, checkIfIsAvailableConcreteBook)
{
    //GIVEN
    books;
    shop::Ware ware;

    //WHEN
    books.readItemsFromFile();

    std::vector<shop::ConcreteBook> read = books.getBooks();
    ware.position = 1;

    //THEN
    ASSERT_TRUE(books.checkAmountofBookInShop(ware));
}



/*TEST_F(BookTests, getObjectOfBook)
{
    //GIVEN
    books;
    std::pair<std::string, std::string> p("Andreij Kowla","Ucecka");

    //WHEN
    shop::ConcreteBook book(p,12.99);

    //THEN
    EXPECT_EQ(12.99,book.getPrice());

}

TEST_F(BookTests, readProperValuesOfBooks)
{
    //GIVEN
    books;

    //WHEN
    books.readItemsFromFile();

    //THEN
    EXPECT_TRUE(!books.titleOfBooksInShop.empty());
    EXPECT_TRUE(!books.pricesOfBooksInShop.empty());
    EXPECT_TRUE(!books.amountOfBooksInShop.empty());
}

/*TEST_F(BookTests, returnBookFromBasketToShop)
{
    //GIVEN
    books;
    Application app;


    //WHEN
    books.readItemsFromFile();

    int currentAmount = books.amountOfBooksInShop[0];
    app.removedThings.push_back(books.titleOfBooksInShop[0]);

    app.saveRemovedToFile();
    app.readRemovedFromFile();
    books.searchInRemoved(app);

    //THEN
    EXPECT_EQ(currentAmount + 1 , books.amountOfBooksInShop[0]);
}*/

/*TEST_F(BookTests, searchingBookAfterEnteredLetter)
{
    //GIVEN
    books;

    //WHEN
    books.readItemsFromFile();

    //THEN
    EXPECT_EQ(shop::BookManager::FOUND,books.searchingBook());

}*/

/*TEST_F(BookTests, searchingBookAfterEnteredLetterIfNotFound)
{
    //GIVEN
    books;

    //WHEN
    books.readItemsFromFile();
    books.searchingBook();

    //THEN
    EXPECT_EQ(books.getSizeOfCurrentSearchings(),1);

}

TEST_F(BookTests, checkIfBookExist)
{
    //GIVEN
    books;
    std::string title1 = "Dluga_noc";
    std::string title2 = "Sami_swoi";

    //WHEN
    books.readItemsFromFile();


    //THEN
    EXPECT_EQ(books.checkIfBookExist(title1), 0);
    EXPECT_EQ(books.checkIfBookExist(title2), 3);

}

TEST_F(BookTests, addBookToShop)
{
    //GIVEN
    books;
    std::string title1 = "Dluga_noc_1";
    std::string title2 = "Sami_swoi_1";

    //WHEN
    books.readItemsFromFile();



    //THEN
    EXPECT_EQ(books.checkIfBookExist(title1), -1);
    EXPECT_EQ(books.checkIfBookExist(title2), -1);

}

TEST_F(BookTests, checkAmountOfChoosenBook)
{
    //GIVEN
    books;
    Application app;
    shop::Ware ware;
    std::string title1 = "Dluga_noc_1";
    std::string title2 = "Sami_swoi_1";

    //WHEN
    books.readItemsFromFile();
    books.titleOfBooksInShop.push_back(title1);
    books.amountOfBooksInShop.push_back(25);
    books.pricesOfBooksInShop.push_back(11.99);

    ware.position = books.checkIfBookExist(title1);

    //THEN
    EXPECT_TRUE(books.checkAmountofBookInShop(ware));

}*/

