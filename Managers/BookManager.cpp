//
// Created by Admin on 06.08.2020.
//

#include "BookManager.h"

#include<string>




void shop::BookManager :: readItemsFromFile()
{

    books_.clear();
    amounts_.clear();


    base::ReadCsvTsv read("book.tsv");
    read.readFromFile(books_, amounts_);

}

void shop::BookManager:: saveItemsToFile()
{

    base::WriteCsvTsv write("book.tsv");

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

void shop::BookManager::editionStateOfBooks()
{
    std::cout<<"CHOOSE: "<<std::endl;
    std::cout<<"1. Add new book to shop"<<std::endl;
    std::cout<<"2. Remove chosen book from shop"<<std::endl;

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
int shop::BookManager::searchingBook()
{

    std::cout<<"Enter letter that a title of book begin"<<std::endl;

    std::cin>>letter;                //searching titles after presses button


    toUpper();                              //change letter to capital

    addSearchedBooks(letter);                     //add to set of searched book titles begining capital letter

    toLower();                              //change letter to small

    addSearchedBooks(letter);                     //add to set of searched book titles begining small letter

    currentSearchings.push_back("NONE OF ABOVE");

    if(showSearchedBooks(this->currentSearchings)==NOT_FOUND) //show found books
    {
        return NOT_FOUND;
    } else
    {
        return FOUND;
    }
}

//----------------------------------------------------------------------------------------------------------------------

int shop::BookManager :: chooseOfSearchedBook()
{
    std::cout<<"Choose the book you are looking for: "<<std::endl;
    choose = -1;
    choose = enteringTheNumber(1,this->currentSearchings.size());

    return choose;
}

//----------------------------------------------------------------------------------------------------------------------

int shop::BookManager::getSizeOfCurrentSearchings()
{
    return currentSearchings.size();
}

void shop::BookManager::addSearchedBooks(char letter_)
{
    for(ConcreteBook  b : this->books_)
    {
        if(b.getPairOfTitleAndAuthorBook().second[0] == letter_)
        {
            this->currentSearchings.push_back(b.getPairOfTitleAndAuthorBook().second);
        }
    }
}
int shop::BookManager :: showSearchedBooks(std::vector<std::string>&searchedBooks)
{
    if(searchedBooks.empty()||searchedBooks[0]=="NONE OF THE ABOVE")
    {
        std::cout<<"There is no title which begin entered letter! "<<std::endl;

       return NOT_FOUND;
    }
    else
    {
        std::cout<<"Found books in shop: "<<std::endl;

        for(int i = 0 ; i<searchedBooks.size();i++)
        {
            std::cout<<i+1<<". "<<searchedBooks[i]<<std::endl;
        }
        return FOUND;
    }
}

bool shop::BookManager ::checkAmountofBookInShop(const Ware &purchases)
{
    bool p;

    this->amounts_[purchases.position]--;


    if(this->amounts_[purchases.position] > 0)
    {
        this->tempAuthor = this->books_[purchases.position].getPairOfTitleAndAuthorBook().first;
        p = true;
    }
    else
    {
        std::cout << "There is no book with this title currently!" <<
             this->books_[purchases.position].getPairOfTitleAndAuthorBook().second << std::endl;
        p = false;
    }

    return p;
}


//----------------------------------------------------------------------------------------------------------------------

 int shop::BookManager ::checkIfBookExist(std::string &title)
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

std::string shop::BookManager::getTitleOfSearchedBook(int t)
{
    return currentSearchings[t];
}

//----------------------------------------------------------------------------------------------------------------------

void shop::BookManager::addBookToShop(std::string &authorOfNewBook,std::string &titleOfNewBook, ware_t &praisesOfNewBook, int amountOfNewBook)
{
    //automatic adding new resources of books to shop
    std::pair<std::string, std::string> authorAnTitleToAdd(authorOfNewBook,titleOfNewBook);
    this->books_.emplace_back(authorAnTitleToAdd, praisesOfNewBook);
    this->amounts_.push_back(amountOfNewBook);


}

//----------------------------------------------------------------------------------------------------------------------

void shop::BookManager:: addThingToShop()
{
    if(Ware::application_.mode == CLIENT_MODE)
    {
        std::cout<<"You are not owner of shop - you can not edit state of shop!"<<std::endl;
    }
    else if(Ware::application_.mode == SELLER_MODE)
    {
        std::cout<<"Enter: author, title, price, amount in this order ";
        std::string authorToAdd;
        std::string titleToAdd;
        ware_t  priceToAdd;
        int amountToAdd;
        std::cin>>authorToAdd;
        std::cin>>titleToAdd;
        std::cin>>priceToAdd;
        std::cin>>amountToAdd;
        this->addBookToShop(authorToAdd,titleToAdd, priceToAdd,amountToAdd);

    }
}

///----------------------------------------------------------------------------------------------------------------------

void shop::BookManager ::removeThingFromShop()
{

    if(Ware::application_.mode == CLIENT_MODE)
    {
        std::cout<<"You are not owner of shop - you can not edit state of shop!"<<std::endl;
    }
    else if(Ware::application_.mode == SELLER_MODE)
    {
        std::cout<<"Enter title of book you want to incrementAmountOfReturnedItem from shop: "<<std::endl;
        std::cin>>titleToRemove;
        position_b = checkIfBookExist(titleToRemove);

        if(position_b>=0)
        {
            this->books_.erase(this->books_.begin() + position_b);
            this->amounts_.erase(this->amounts_.begin() + position_b);

        }
        else
        {
            std::cout<<"The book to incrementAmountOfReturnedItem was not found!"<<std::endl;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------

void shop::BookManager::toUpper()
{
    if(letter>95)
    {
        letter = (char)(letter-32); //shift by 32 position in ASCII code to obtain capital letter
    }
}


void shop::BookManager::toLower()
{
    if(letter<95)
    {
        letter = (char)(letter+32); //shift by 32 position in ASCII code to obtain small letter
    }
}

void shop::BookManager::searchInRemoved(Application &app)
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

std::vector<std::string> shop::BookManager::returnBookFromBasketToShop(std::vector<std::string> removed)
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

shop::ConcreteBook shop::BookManager::getBook(int index) {
    return books_[index];
}

std::vector<shop::ConcreteBook> shop::BookManager::getBooks() {
    return this->books_;
}

std::string shop::BookManager::getTitleOfConcreteBook(int index) {
    return getBook(index).getPairOfTitleAndAuthorBook().second;
}

int shop::BookManager::getCurrentSearchingSize() {
    return this->currentSearchings.size();
}

shop::BookManager::~BookManager() {
    //this->saveItemsToFile();
}

void shop::BookManager::incrementAmountOfBook( ConcreteBook &book) {

    for(int i = 0 ; i < this->books_.size(); i++){

        //finding proper book in all collection
        if(this->books_[i].getPairOfTitleAndAuthorBook() == book.getPairOfTitleAndAuthorBook()){

            this->amounts_[i]++;
            break;
        }
    }
}



//----------------------------------------------------------------------------------------------------------------------