//
// Created by Admin on 06.08.2020.
//

#include "Book.h"

#include<string>

using namespace std;
using namespace shop;
using namespace base;

void Book :: readItemsFromFile()
{

    titleOfBooksInShop.clear();
    amountOfBooksInShop.clear();
    pricesOfBooksInShop.clear();

    ReadCsvTsv read("book.tsv");
    read.readFromFile(titleOfBooksInShop, amountOfBooksInShop, pricesOfBooksInShop);

}

void Book:: saveItemsToFile()
{

    WriteCsvTsv write("book.tsv");

    std::vector<std::string>header{"TYTUL","ILOSC","CENA"};
    write.addHeader(header);

    std::vector<std::string> dataToTsv;
    std::string readyData;



    for(int i =0; i < titleOfBooksInShop.size(); i++)
    {

        if(i+1 == titleOfBooksInShop.size())
        {

            dataToTsv.push_back(titleOfBooksInShop[i]);

            std::string am = std::to_string(amountOfBooksInShop[i]);
            dataToTsv.push_back(am);

            std::string pr = std::to_string(pricesOfBooksInShop[i]);
            dataToTsv.push_back(pr);
        }
        else
        {

            dataToTsv.push_back(titleOfBooksInShop[i]);

            std::string am = std::to_string(amountOfBooksInShop[i]);
            dataToTsv.push_back(am);

            std::string pr = std::to_string(pricesOfBooksInShop[i]);
            dataToTsv.push_back(pr);
        }

        write.writeToFile(dataToTsv);
        dataToTsv.clear();

    }
}

///----------------------------------------------------------------------------------------------------------------------

void Book::editionStateOfBooks()
{
    cout<<"WYBOR: "<<endl;
    cout<<"1. Dodanie nowej ksiazki do sklepu"<<endl;
    cout<<"2. Usuniecie wybranej ksiazki ze sklepu"<<endl;

    int choose = enteringTheNumber(1,2);
    switch(choose)
    {
        case 1:
            addThingToShop();
            break;
        case 2:
            removeThingFromShop();
            break;
        default:
            break;
    }

}
int Book::searchingBook()
{

    cout<<"Podaj litere, na ktora zaczyna sie tytul: "<<endl;

    while(!_kbhit())
    {
        letter = getch();                //wyszukiwanie ksiazek po wcisnietym znaku
    }

    cout<<"Litera: "<<letter<<endl;

    toUpper();                              //zamiana litery na duza

    addSearchedBooks(letter);                     //dodanie do zbioru wyszukanych pozycji na litere duza

    toLower();                              //zamiana litery na małą

    addSearchedBooks(letter);                     //dodanie do zbioru wyszukanych pozycji na litere duza

    currentSearchings.push_back("ZADNA_Z_POWYZSZYCH");

    if(showSearchedBooks(currentSearchings)==NOT_FOUND)//wyswietlenie wyszukanych pozycji
    {
        return NOT_FOUND;
    } else
    {
        return FOUND;
    }
}

//----------------------------------------------------------------------------------------------------------------------

int Book :: chooseOfSearchedBook()
{
    cout<<"Wybierz z powyzszej listy interesujaca cie pozycje: "<<endl;
    choose = -1;
    bool good,bad;
    do
    {
        cin>>choose;
        cout<<choose<<endl;
        good = cin.good();
        bad = cin.bad();//zabezbieczenie przed wprowadzeniem innegotypu danych jak int
        cin.clear();
        cin.sync();
    }while (choose <=0 || choose>currentSearchings.size()||good==0||bad==1);
    return choose;
}

//----------------------------------------------------------------------------------------------------------------------

int Book::getSizeOfCurrentSearchings()
{
    return currentSearchings.size();
}

void Book::addSearchedBooks(char letter_)
{
    for(int i = 0; i < titleOfBooksInShop.size(); i++)
    {
        if(titleOfBooksInShop[i][0] == letter_)
        {
            currentSearchings.push_back(titleOfBooksInShop[i]);
        }

    }
}
int Book :: showSearchedBooks(std::vector<std::string>&searchedBooks)
{
    if(searchedBooks.empty()||searchedBooks[0]=="ZADNA_Z_POWYZSZYCH")
    {
        cout<<"Brak znalezionych pozycji pod ta litera!!! "<<endl;

       return NOT_FOUND;
    }
    else
    {
        cout<<"Wyszukane pozycje w sklepie to: "<<endl;

        for(int i = 0 ; i<searchedBooks.size();i++)
        {
            cout<<i+1<<". "<<searchedBooks[i]<<endl;
        }
        return FOUND;
    }
}

bool Book ::checkAmountofBookInShop(const Ware &purchases)
{
    bool p;
    this->amountOfBooksInShop[purchases.position]--;
    int checker = 1;//ksiega->amountOfBooksInShop[purchases.position];

    if(this->amountOfBooksInShop[purchases.position]>0)
    {
        p = true;
    }
    else
    {
        cout << "Obecnie brak pozycji o tytule: " << this->titleOfBooksInShop[purchases.position] << endl;
        p = false;
    }

    return p;
}


//----------------------------------------------------------------------------------------------------------------------

 int Book ::checkIfBookExist(std::string &title)
{
    int position = -1;
    for(int i =0; i<this->titleOfBooksInShop.size(); i++)
    {
        if(this->titleOfBooksInShop[i] == title)
        {
            position = i;
            break;
        }
    }
    return position;

}

std::string Book::getSearchedBook(int t)
{
    return currentSearchings[t];
}

//----------------------------------------------------------------------------------------------------------------------

void Book::addBookToShop(std::string &titleOfNewBook, towar_t &praisesOfNewBook, int amountOfNewBook)
{
    //automatyzacja uzupelniania zapasow sklepu
    this->titleOfBooksInShop.push_back(titleOfNewBook);
    this->pricesOfBooksInShop.push_back(praisesOfNewBook);
    this->amountOfBooksInShop.push_back(amountOfNewBook);
}

//----------------------------------------------------------------------------------------------------------------------

void Book:: addThingToShop()
{
    if(mode==CUSTOMER_MODE)
    {
        cout<<"Czynnosc niedozwolona ze wzgledu na brak uprawnien"<<endl;
    }
    else if(mode == SELLER_MODE)
    {
        cout<<"Podaj kolejno tytul ksiazki, cene za sztuke, ilosc ksiazek: ";
        std::string title_a;
        towar_t  pricesToAdd;
        int amountToAdd;
        cin>>title_a;
        cin>>pricesToAdd;
        cin>>amountToAdd;
        this->addBookToShop(title_a,pricesToAdd,amountToAdd);

    }
}

///----------------------------------------------------------------------------------------------------------------------

void Book ::removeThingFromShop()
{

    if(mode==CUSTOMER_MODE)
    {
        cout<<"Czynnosc niedozwolona ze wzgledu na brak uprawnien"<<endl;
    }
    else if(mode == SELLER_MODE)
    {
        cout<<"Podaj tytul ksiazki ktora zamierzasz usunac ze sklepu"<<endl;
        cin>>titleToRemove;
        position_b = checkIfBookExist(titleToRemove);

        if(position_b>=0)
        {
            this->titleOfBooksInShop.erase(this->titleOfBooksInShop.begin() + position_b);
            this->pricesOfBooksInShop.erase(this->pricesOfBooksInShop.begin() + position_b);
            this->amountOfBooksInShop.erase(this->amountOfBooksInShop.begin() + position_b);
        }
        else
        {
            cout<<"Nie znaleziono pozycji do usuniecia"<<endl;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------

void Book::toUpper()
{
    if(letter>95)
    {
        letter = (char)(letter-32); //ptzrsuniecie o 32 pozycje do tylu w kodzie ASCII do duzej litery
    }
}


void Book::toLower()
{
    if(letter<95)
    {
        letter = (char)(letter+32); //przrsuniecie o 32 pozycje do przodu w kodzie ASCII do malej litery
    }
}

void Book::searchInRemoved(Application &app)
{
    for(int i=0;i<app.removedThings.size();i++)
    {
        for(int j=0; j < titleOfBooksInShop.size(); j++)
        {
            if(app.removedThings[i] == titleOfBooksInShop[j])
            {
                amountOfBooksInShop[j]++;
                //delete removedThings;
                app.removedThings.erase(app.removedThings.begin()+i);
                break;
            }
        }

    }

}

std::vector<std::string> Book::returnBookFromBasketToShop(std::vector<std::string> removed)
{
    for(int i=0;i<removed.size();i++)
    {
        for(int j=0; j < titleOfBooksInShop.size(); j++)
        {
            if(removed[i] == titleOfBooksInShop[j])
            {
                removed.erase(removed.begin() + i);
                amountOfBooksInShop[j]++;
            }
        }
    }
    return removed;
}



//----------------------------------------------------------------------------------------------------------------------