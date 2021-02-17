//
// Created by Admin on 06.08.2020.
//

#include "BookManager.h"
#include "ConcreteBook.h"

#include<string>

using namespace std;
using namespace shop;
using namespace base;

void BookManager :: readItemsFromFile()
{

    titleOfBooksInShop.clear();
    amountOfBooksInShop.clear();
    pricesOfBooksInShop.clear();

    _books.clear();
    _amounts.clear();


    ReadCsvTsv read("book.tsv");
    read.readFromFile(_books,_amounts);

}

void BookManager:: saveItemsToFile()
{

    WriteCsvTsv write("book.tsv");

    std::vector<std::string>header{"AUTOR","TYTUL","CENA","ILOSC"};
    write.addHeader(header);

    std::vector<std::string> dataToTsv;
    std::string readyData;

    int i = 0 ;
    for(auto & b : _books)
    {
        dataToTsv.push_back(b.getPairOfTitleAndAuthorBook().first);
        dataToTsv.push_back(b.getPairOfTitleAndAuthorBook().second);

        std::string pr = std::to_string(b.getPrice());

        dataToTsv.push_back(pr);

        std::string am = std::to_string(_amounts[i]);

        dataToTsv.push_back(am);
        i++;

        write.writeToFile(dataToTsv);
        dataToTsv.clear();
    }

   /* for(int i =0; i < titleOfBooksInShop.size(); i++)
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

    }*/
}

///----------------------------------------------------------------------------------------------------------------------

void BookManager::editionStateOfBooks()
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
int BookManager::searchingBook()
{

    cout<<"Podaj litere, na ktora zaczyna sie tytul: "<<endl;

    while(!_kbhit())
    {
        //letter = getch();                //wyszukiwanie ksiazek po wcisnietym znaku
    }
    cin>>letter;

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

int BookManager :: chooseOfSearchedBook()
{
    cout<<"Wybierz z powyzszej listy interesujaca cie pozycje: "<<endl;
    choose = -1;
    choose = enteringTheNumber(1,currentSearchings.size());
    /*bool good,bad;
    do
    {
        cin>>choose;
        cout<<choose<<endl;
        good = cin.good();
        bad = cin.bad();//zabezbieczenie przed wprowadzeniem innegotypu danych jak int
        cin.clear();
        cin.sync();
    }while (choose <=0 || choose>currentSearchings.size()||good==0||bad==1);*/
    return choose;
}

//----------------------------------------------------------------------------------------------------------------------

int BookManager::getSizeOfCurrentSearchings()
{
    return currentSearchings.size();
}

void BookManager::addSearchedBooks(char letter_)
{
   /* for(int i = 0; i < titleOfBooksInShop.size(); i++)
    {
        if(titleOfBooksInShop[i][0] == letter_)
        {
            //currentSearchings.push_back(titleOfBooksInShop[i]);
        }

    }*/
    for(ConcreteBook  b : _books)
    {
        //TODO wyszukiwarke w kontenerze ksiazek
        if(b.getPairOfTitleAndAuthorBook().first[0] == letter_)
        {
            currentSearchings.push_back(b.getPairOfTitleAndAuthorBook().first);
        }
    }
}
int BookManager :: showSearchedBooks(std::vector<std::string>&searchedBooks)
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

bool BookManager ::checkAmountofBookInShop(const Ware &purchases)
{
    bool p;
    //this->amountOfBooksInShop[purchases.position]--;
    this->_amounts[purchases.position]--;
    int checker = 1;//ksiega->amountOfBooksInShop[purchases.position];

    if(this->_amounts[purchases.position]>0)
    {
        p = true;
    }
    else
    {
        cout << "Obecnie brak pozycji o tytule: " <<
        this->_books[purchases.position].getPairOfTitleAndAuthorBook().second << endl;
        p = false;
    }

    return p;
}


//----------------------------------------------------------------------------------------------------------------------

 int BookManager ::checkIfBookExist(std::string &title)
{
    int position = -1,position1 = -1;
   /* for(int i =0; i<this->titleOfBooksInShop.size(); i++)
    {
        if(this->titleOfBooksInShop[i] == title)
        {
            position = i;
            break;
        }
    }
*/
    for(auto & b : _books)
    {
        if(b.getPairOfTitleAndAuthorBook().second == title)
        {
            break;
        }
        position1++;
    }

    return position1;

}

std::string BookManager::getSearchedBook(int t)
{
    return currentSearchings[t];
}

//----------------------------------------------------------------------------------------------------------------------

void BookManager::addBookToShop(std::string &titleOfNewBook, ware_t &praisesOfNewBook, int amountOfNewBook)
{
    //automatyzacja uzupelniania zapasow sklepu
    this->titleOfBooksInShop.push_back(titleOfNewBook);
    this->pricesOfBooksInShop.push_back(praisesOfNewBook);
    this->amountOfBooksInShop.push_back(amountOfNewBook);
}

//----------------------------------------------------------------------------------------------------------------------

void BookManager:: addThingToShop()
{
    if(mode==CUSTOMER_MODE)
    {
        cout<<"Czynnosc niedozwolona ze wzgledu na brak uprawnien"<<endl;
    }
    else if(mode == SELLER_MODE)
    {
        cout<<"Podaj kolejno tytul ksiazki, cene za sztuke, ilosc ksiazek: ";
        std::string title_a;
        ware_t  pricesToAdd;
        int amountToAdd;
        cin>>title_a;
        cin>>pricesToAdd;
        cin>>amountToAdd;
        this->addBookToShop(title_a,pricesToAdd,amountToAdd);

    }
}

///----------------------------------------------------------------------------------------------------------------------

void BookManager ::removeThingFromShop()
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

void BookManager::toUpper()
{
    if(letter>95)
    {
        letter = (char)(letter-32); //ptzrsuniecie o 32 pozycje do tylu w kodzie ASCII do duzej litery
    }
}


void BookManager::toLower()
{
    if(letter<95)
    {
        letter = (char)(letter+32); //przrsuniecie o 32 pozycje do przodu w kodzie ASCII do malej litery
    }
}

void BookManager::searchInRemoved(Application &app)
{
    for(int i=0;i<app.removedThings.size();i++)
    {
        for(int j=0; j < titleOfBooksInShop.size(); j++)
        {
            std::pair<std::string, std::string> getP = _books[j].getPairOfTitleAndAuthorBook();
            std::string title = getP.first;
            if(app.removedThings[i] == title)
            {
                amountOfBooksInShop[j]++;

                _amounts[j] ++;
                //delete removedThings;
                app.removedThings.erase(app.removedThings.begin()+i);
                break;
            }
        }

    }

}

std::vector<std::string> BookManager::returnBookFromBasketToShop(std::vector<std::string> removed)
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

ConcreteBook BookManager::getBook(int index) {
    return _books[index];
}

std::vector<shop::ConcreteBook> BookManager::getBooks() {
    return this->_books;
}

std::string BookManager::getTitleOfConcreteBook(int index) {
    return getBook(index).getPairOfTitleAndAuthorBook().second;
}



//----------------------------------------------------------------------------------------------------------------------