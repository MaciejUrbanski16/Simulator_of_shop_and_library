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

        //kontenery na dane o przechowywanych ksiazkach w sklepie
        std::vector<std::string> titleOfBooksInShop;
        std::vector<int> amountOfBooksInShop;



        ConcreteBook getBook(int index);
        std::string getTitleOfConcreteBook(int index);
        ware_t getPriceOfConcreteBook(int index);
        std::vector<ConcreteBook> getBooks();


        bool checkAmountofBookInShop(const Ware &t); //sprawdza czy w sklepie jest pozycja o zadanym tytlue


        int checkIfBookExist(std::string &title); //zwraca pozycje ksiazki o zadanym tytule

        void editionStateOfBooks();   //usuwanie badz dodawanie zasobow sklaepu ksiazke

        std::string getSearchedBook(int t);     //zwraca tytul szuaknej ksiazki

        int chooseOfSearchedBook();     //zwraca nr wybranej ksiazki z proponowanej listy

        int searchingBook();        //wyszukiwanie tytulu po zadanej pierwszej literze(uwzglednia duze i male litery

        //pokazuje tytuly wyszukanych ksiazek po zadanej pierwszej literze, zwraca parametr FOUND badz NOT_FOUND
        int showSearchedBooks(std::vector<std::string> &searchedBooks);

        //zapisanie wszystkich ksiazek ze sklepu przed wyjsciem z uslugi
        void saveItemsToFile()override ;

        //odczytanie z pliku ksiazek obecnie posiadanych przez sklep
        void readItemsFromFile()override ;

        void searchInRemoved(Application &app);

        std::vector<std::string> returnBookFromBasketToShop(std::vector<std::string> removed);

        int getSizeOfCurrentSearchings();
    };

}
#endif //MACHINEOFSTATE_BOOKMANAGER_H
