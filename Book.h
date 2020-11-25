//
// Created by Admin on 06.08.2020.
//

#ifndef MACHINEOFSTATE_BOOK_H
#define MACHINEOFSTATE_BOOK_H

#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <conio.h>
#include "accesories.h"
#include <map>
//#include "Catch_tests/AbsoluteDateTest.cpp"


namespace shop {

    class Book : public shop::Towar    //klasa jako przedstawiciel książki
    {
    private:
        char letter;
        int choose;
    public:
        //Book(const std::string &title);
        Book(){}
        Book(std::string title){this->title = "new";}

    private:
        std::vector<std::string>currentSearchings;
        //std::vector<std::string>::iterator iter;


        std::fstream readTitles;
        std::fstream readAmount;
        std::fstream readPrices;

        std::string titleToRemove;
        towar_int_t position_b = -1;

        void addSearchedBooks();

        //funkcja dodawania ksiazek komunikujaca sie z sprzedawca
        void addThingToShop();

        //usuniecie przedmiotu ze sklepu (dostepne jedynie w trybie sprzedawcy)
        void removeThingFromShop();





        //funkcja dodajaca ksiazke w systemie
        void addBookToShop(       std::string titleOfNewBook,
                                  towar_int_t praisesOfNewBook,
                                  int amountOfNewBook);



        void toLower();
        void toUpper();

    public:
        std::string title;               //tytul
        //std::string editor;              //wydawnictwo
        shop::towar_int_t praiseOfBook{};

        std::string choosenTitle;





        enum
        {
            FOUND,
            NOT_FOUND
        };

        //kontenery na dane o przechowywanych ksiazkach w sklepie
        std::vector<std::string> titleOfBooksInShop;
        std::vector<int> amountOfBooksInShop;
        std::vector<shop::towar_int_t > praisesOfBooksInShop;

        //std::vector<Book> bookBooked;        //zamowione ksiazki
        //std::fstream fileForTitleOfBooks;

        int getSizeOfCurrentSearchings();           //zwraca rozmiar prywatnego vectora currentSearchings

        bool checkAmountofBookInShop(const Towar &t); //sprawdza czy w sklepie jest pozycja o zadanym tytlue


        int checkIfBookExist(std::string title); //zwraca pozycje ksiazki o zadanym tytule

        void editionStateOfBooks();   //usuwanie badz dodawanie zasobow sklaepu ksiazke

        std::string getSearchedBook(int t);     //zwraca tytul szuaknej ksiazki

        int chooseOfSearchedBook();     //zwraca nr wybranej ksizki z proponowanej listy

        int searchingBook();        //wyszukiwanie tytulu po zadanej pierwszej literze(uwzglednia duze i male litery

        //pokazuje tytuly wyszukanych ksiazek po zadanej pierwszej literze, zwraca parametr FOUND badz NOT_FOUND
        int showSearchedBooks(std::vector<std::string> searchedBooks);

        //zapisanie wszystkich ksiazek ze sklepu przed wyjsciem z uslugi
        void saveItemsToFile();

        //odczytanie z pliku ksiazek obecnie posiadanych prze sklep
        void readItemsFromFile();

        void searchInRemoved();

        std::vector<std::string> returnBookFromBasketToShop(std::vector<std::string> removed);
    };

}
#endif //MACHINEOFSTATE_BOOK_H
