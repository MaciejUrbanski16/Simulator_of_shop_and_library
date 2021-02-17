//
// Created by Admin on 06.08.2020.
//

#ifndef MACHINEOFSTATE_BOOKMANAGER_H
#define MACHINEOFSTATE_BOOKMANAGER_H

#include "ShopWare.h"
#include "ConcreteBook.h"
#include "WriteCsvTsv.h"
#include "ReadCsvTsv.h"

#include "Application.h"

#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <conio.h>
#include <map>



namespace shop {
    class ConcreteBook;

    ///OGÓLNA KLASA DO ZARZĄDZANIA ZBIOREM KSIĄŻEK
    class BookManager : public shop::Ware
    {
    private:
        char letter; //znak podany przez uzytkownika do odnalezienia kontreknej pozycji na liscie
        int choose;
    public:

        BookManager(){}

    private:

        std::map<std::string, std::string> _books1;
        std::vector<ware_t> _prices;

        std::vector<ConcreteBook> _books;
        std::vector<int> _amounts;

        std::vector<std::string>currentSearchings;

        std::string titleToRemove;
        int position_b = -1;

        void addSearchedBooks(char letter);

        //funkcja dodawania ksiazek komunikujaca sie z sprzedawca
        void addThingToShop();

        //usuniecie przedmiotu ze sklepu (dostepne jedynie w trybie sprzedawcy)
        void removeThingFromShop();





        //funkcja dodajaca ksiazke w systemie
        void addBookToShop(std::string &titleOfNewBook,
                           ware_t &praisesOfNewBook,
                           int amountOfNewBook);

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
        std::vector<shop::ware_t > pricesOfBooksInShop;



        ConcreteBook getBook(int index);
        std::string getTitleOfConcreteBook(int index);
        ware_t getPriceOfConcreteBook(int index);
        std::vector<ConcreteBook> getBooks();

        //ware_t getPrice

        //int getSizeOfCurrentSearchings();           //zwraca rozmiar prywatnego vectora currentSearchings

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
