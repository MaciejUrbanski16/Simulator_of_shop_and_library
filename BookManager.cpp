//
// Created by Admin on 06.08.2020.
//

#include "BookManager.h"

#include<string>

using namespace std;
using namespace shop;
using namespace base;

void BookManager :: readItemsFromFile()
{

    books_.clear();
    amounts_.clear();


    ReadCsvTsv read("book.tsv");
    read.readFromFile(books_, amounts_);

}

void BookManager:: saveItemsToFile()
{

    WriteCsvTsv write("book.tsv");

    std::vector<std::string>header{"AUTHOR","TITLE","PRICE","AMOUNT"};
    write.addHeader(header);

    std::vector<std::string> dataToTsv;
    std::string readyData;

    int i = 0 ;
    for(auto & b : books_)
    {
        dataToTsv.push_back(b.getPairOfTitleAndAuthorBook().first);
        dataToTsv.push_back(b.getPairOfTitleAndAuthorBook().second);

        std::string pr = std::to_string(b.getPrice());

        dataToTsv.push_back(pr);

        std::string am = std::to_string(amounts_[i]);

        dataToTsv.push_back(am);
        i++;

        write.writeToFile(dataToTsv);
        dataToTsv.clear();
    }
}

///----------------------------------------------------------------------------------------------------------------------

void BookManager::editionStateOfBooks()
{
    cout<<"CHOOSE: "<<endl;
    cout<<"1. Add new book to shop"<<endl;
    cout<<"2. Remove chosen book from shop"<<endl;

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

    cout<<"Enter letter that a title of book begin"<<endl;

    cin>>letter;                //searching titles after presses button

    cout<<"Letter: "<<letter<<endl;

    toUpper();                              //change letter to capital

    addSearchedBooks(letter);                     //add to set of searched book titles begining capital letter

    toLower();                              //change letter to small

    addSearchedBooks(letter);                     //add to set of searched book titles begining small letter

    currentSearchings.push_back("NONE OF ABOVE");

    if(showSearchedBooks(currentSearchings)==NOT_FOUND) //show found books
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
    cout<<"Choose the book you are looking for: "<<endl;
    choose = -1;
    choose = enteringTheNumber(1,currentSearchings.size());

    return choose;
}

//----------------------------------------------------------------------------------------------------------------------

int BookManager::getSizeOfCurrentSearchings()
{
    return currentSearchings.size();
}

void BookManager::addSearchedBooks(char letter_)
{
    for(ConcreteBook  b : books_)
    {
        if(b.getPairOfTitleAndAuthorBook().second[0] == letter_)
        {
            currentSearchings.push_back(b.getPairOfTitleAndAuthorBook().second);
        }
    }
}
int BookManager :: showSearchedBooks(std::vector<std::string>&searchedBooks)
{
    if(searchedBooks.empty()||searchedBooks[0]=="NONE OF THE ABOVE")
    {
        cout<<"There is no title which begin entered letter! "<<endl;

       return NOT_FOUND;
    }
    else
    {
        cout<<"Found books in shop: "<<endl;

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

    this->amounts_[purchases.position]--;


    if(this->amounts_[purchases.position] > 0)
    {
        p = true;
    }
    else
    {
        cout << "There is no book with this title currently!" <<
             this->books_[purchases.position].getPairOfTitleAndAuthorBook().second << endl;
        p = false;
    }

    return p;
}


//----------------------------------------------------------------------------------------------------------------------

 int BookManager ::checkIfBookExist(std::string &title)
{
    int position = -1;
    for(int i =0; i<this->amounts_.size(); i++)
    {
        if(this->books_[i].getPairOfTitleAndAuthorBook().second == title)
        {
            position = i;
            break;
        }
    }

    return position;
}

std::string BookManager::getSearchedBook(int t)
{
    return currentSearchings[t];
}

//----------------------------------------------------------------------------------------------------------------------

void BookManager::addBookToShop(std::string &authorOfNewBook,std::string &titleOfNewBook, ware_t &praisesOfNewBook, int amountOfNewBook)
{
    //automatic adding new resources of books to shop
    std::pair<std::string, std::string> authorAnTitleToAdd(authorOfNewBook,titleOfNewBook);
    this->books_.emplace_back(authorAnTitleToAdd, praisesOfNewBook);
    this->amounts_.push_back(amountOfNewBook);


}

//----------------------------------------------------------------------------------------------------------------------

void BookManager:: addThingToShop()
{
    if(Ware::application_.mode==CUSTOMER_MODE)
    {
        cout<<"You are not owner of shop - you can not edit state of shop!"<<endl;
    }
    else if(Ware::application_.mode == SELLER_MODE)
    {
        cout<<"Enter: author, title, price, amount in this order ";
        std::string authorToAdd;
        std::string titleToAdd;
        ware_t  priceToAdd;
        int amountToAdd;
        cin>>authorToAdd;
        cin>>titleToAdd;
        cin>>priceToAdd;
        cin>>amountToAdd;
        this->addBookToShop(authorToAdd,titleToAdd, priceToAdd,amountToAdd);

    }
}

///----------------------------------------------------------------------------------------------------------------------

void BookManager ::removeThingFromShop()
{

    if(Ware::application_.mode==CUSTOMER_MODE)
    {
        cout<<"You are not owner of shop - you can not edit state of shop!"<<endl;
    }
    else if(Ware::application_.mode == SELLER_MODE)
    {
        cout<<"Enter title of book you want to incrementAmountOfReturnedItem from shop: "<<endl;
        cin>>titleToRemove;
        position_b = checkIfBookExist(titleToRemove);

        if(position_b>=0)
        {
            this->books_.erase(this->books_.begin() + position_b);
            this->amounts_.erase(this->amounts_.begin() + position_b);

        }
        else
        {
            cout<<"The book to incrementAmountOfReturnedItem was not found!"<<endl;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------

void BookManager::toUpper()
{
    if(letter>95)
    {
        letter = (char)(letter-32); //shift by 32 position in ASCII code to obtain capital letter
    }
}


void BookManager::toLower()
{
    if(letter<95)
    {
        letter = (char)(letter+32); //shift by 32 position in ASCII code to obtain small letter
    }
}

void BookManager::searchInRemoved(Application &app)
{
    for(int i=0;i<app.removedThings.size();i++)
    {
        for(int j=0; j < titleOfBooksInShop.size(); j++)
        {
            std::pair<std::string, std::string> getP = books_[j].getPairOfTitleAndAuthorBook();
            std::string title = getP.first;
            if(app.removedThings[i] == title)
            {
                amounts_[j] ++;

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
    return books_[index];
}

std::vector<shop::ConcreteBook> BookManager::getBooks() {
    return this->books_;
}

std::string BookManager::getTitleOfConcreteBook(int index) {
    return getBook(index).getPairOfTitleAndAuthorBook().second;
}



//----------------------------------------------------------------------------------------------------------------------