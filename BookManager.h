//
// Created by Admin on 06.08.2020.
//

#ifndef MACHINEOFSTATE_BOOKMANAGER_H
#define MACHINEOFSTATE_BOOKMANAGER_H

#include "ShopWare.h"
#include "ConcreteBook.h"
#include "WriteCsvTsv.h"
#include "ReadCsvTsv.h"

#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <conio.h>
#include <map>



namespace shop {
    class ConcreteBook;

    ///GENERAL CLASS TO MANAGE TO ALL BOOKS
    class BookManager : public shop::Ware
    {
    private:
        char letter; //char which is given by user to search concrete book in list of books
        int choose;  //number of chosen book which user want to add to basket or incrementAmountOfReturnedItem from basket
    public:

        BookManager(){}

        //lists of all books and amounts of these books
        std::vector<ConcreteBook> books_;
        std::vector<int> amounts_;

        int getCurrentSearchingSize();

         ~BookManager();

    private:



        //buffer of searched title of books started by given letter
        std::vector<std::string>currentSearchings;

        std::string titleToRemove;
        int position_b = -1;

        //add book to list of searched book that start by given letter
        void addSearchedBooks(char letter);

        //adding book to shop -> this function allows seller to enter his new book to shop
        void addThingToShop();

        //incrementAmountOfReturnedItem book from shop
        void removeThingFromShop();





        //add book to shop automatically -> only in SELLER_MODE
        void addBookToShop(std::string &authorOfNewBook,
                           std::string &titleOfNewBook,
                           ware_t &praisesOfNewBook,
                           int amountOfNewBook);

        //changing letter from capital to small or small to capital to search book in all list of books
        void toLower();
        void toUpper();

    public:

        std::string choosenTitle;

        enum
        {
            FOUND,
            NOT_FOUND
        };

        //containers to starage data of books in shop
        std::vector<std::string> titleOfBooksInShop;
        std::vector<int> amountOfBooksInShop;



        ConcreteBook getBook(int index);
        std::string getTitleOfConcreteBook(int index);
        ware_t getPriceOfConcreteBook(int index);
        std::vector<ConcreteBook> getBooks();


        bool checkAmountofBookInShop(const Ware &t); //checks if there is one book with given title at least


        int checkIfBookExist(std::string &title); //returns position  of book with given title

        void editionStateOfBooks();   //add or remove book (only in SELLER_MODE)

        std::string getTitleOfSearchedBook(int t);     //returns title of searched book

        int chooseOfSearchedBook();     //returns number of title of book which was chosen from given list

        int searchingBook();        //search books based on given letter of title

        //shows searched books which were searched after given first letter of title
        int showSearchedBooks(std::vector<std::string> &searchedBooks);

        //save all books after going out
        void saveItemsToFile()override ;

        //read resources of books
        void readItemsFromFile()override ;

        void searchInRemoved(Application &app);

        std::vector<std::string> returnBookFromBasketToShop(std::vector<std::string> removed);

        int getSizeOfCurrentSearchings();

        std::string tempAuthor;
    };

}
#endif //MACHINEOFSTATE_BOOKMANAGER_H
