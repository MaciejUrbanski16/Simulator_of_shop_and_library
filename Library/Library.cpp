//
// Created by Admin on 19.02.2021.
//

#include "Library.h"

library::Library::Library(shop::BookManager &manageBooks) : manageBooks_(manageBooks) {

    srand(time(nullptr));

    ClientInLibrary c("Maciej","Urbanski","12345");
    std::pair<std::string, std::string> p ("Jan","Book");
    shop::ConcreteBook c1(p,12.87);
    this->borrowedBooks_.push_back(c1);
    clientAndBorrowedBook[c] = borrowedBooks_;
}

library::Library::~Library() {

}

shop::BookManager library::Library::getManageBooks()  {
    return manageBooks_;
}

void library::Library::setManageBooks(const shop::BookManager &manageBooks) {
    manageBooks_ = manageBooks;
}



void library::Library::readUsersFromFile() {

    //to avoid strange bugs
    this->clients_.clear();


    base::ReadCsvTsv read("users.tsv");
    read.readFromFile( this->clients_ );
}

void library::Library::saveUsersToFile() {

    base::WriteCsvTsv write("users.tsv");

    //preparing header for file
    std::vector<std::string>header{"NAME", "SURNAME", "ID",  "AUTHOR",	"TITLE","LEFT_TIME ", "//NEXT BORROWED BOOKS ------>"};
    write.addHeader(header);

    std::vector<std::string> dataToTsv;
    std::string readyData;


    for(auto & cl : clients_)
    {
        //saving data of client
        dataToTsv.push_back(cl.getNameOfClient());
        dataToTsv.push_back(cl.getSurnameOfClient());
        dataToTsv.push_back(cl.getNumberIDofClient());


        //saving borrowed books by client
        std::vector<shop::ConcreteBook> tempBooks = cl.getBorrowedByClient();

        int i = 0 ;
        for(shop::ConcreteBook &book : tempBooks){
            //assert(tempBooks.size() == cl.termToGiveBackBorrowedBooks.size());
            dataToTsv.push_back(book.getPairOfTitleAndAuthorBook().first);
            dataToTsv.push_back(book.getPairOfTitleAndAuthorBook().second);

            dataToTsv.push_back(cl.termToGiveBackBorrowedBooks[i]);

            i++;
        }



        write.writeToFile(dataToTsv);
        dataToTsv.clear();
    }
}

std::string library::Library::generateIDofNewClient() {
    uint16_t part1 = 0,part2 = 0;
    bool correctID = false;
    bool existTheSame = false;

    //generating five digit ID number
    while(!correctID) {
        while (part1 <= 100) {
            part1 = rand() % 1000;
        }

        part2 = rand() % 100;

        //to compare with integers in clients_ container
        std::string temp = std::to_string(part1) + std::to_string(part2);
        int tempIDint = std::atoi(temp.c_str());

        //check if the same id exists
        for (auto const &cl : this->clients_) {
            if (cl.getIDasInteger() == tempIDint) {
                existTheSame = true;
                break;
            }
        }

        if(!existTheSame) {
            correctID = true;
        }
    }

    return std::to_string(part1) + std::to_string(part2);
}

void library::Library::registerNewAccount(const std::string &name, const std::string &surname, const std::string &id) {
    std::vector<shop::ConcreteBook> temp;

    this->clients_.emplace_back(ClientInLibrary(name,surname,id));
    this->clients_.back().setBorrowedByClient(temp);
}

void library::Library::addNewClient(const ClientInLibrary& client) {
    this->clients_.push_back(client);
}

std::vector<library::ClientInLibrary> library::Library::getClients() {
    return this->clients_;
}

bool library::Library::loginToLibrary(int introYourID) {

        for(const ClientInLibrary&  cl : clients_){
            if(cl.getIDasInteger() == introYourID){

                this->currentIDloggedIn = introYourID;

                return true;
            }
        }
        return false;
}

void library::Library::borrowBook(int position,const std::string &title) {

    //get time when user has to give back book
    TimeOfBorrowing time;  //actual time
    TimeLeft timeLeft(time);

    //decrements amount of available books
    this->getManageBooks().amounts_[position] --;

    //add chosen book to container with borrowed book of this particular client
    this->clients_[getIndexOfClientWithGivenID()].borrowedByClient.push_back(this->manageBooks_.getBook(position));

    //save term of borrowing book
    this->clients_[getIndexOfClientWithGivenID()].termToGiveBackBorrowedBooks.push_back(timeLeft.getTimeToGiveBack());
}

int library::Library::getIndexOfClientWithGivenID() {
    int i = 0;
    for(auto const &cl : this->clients_){
        if(this->currentIDloggedIn == cl.getIDasInteger()){
            break;
        }
        i++;
    }
    return i;
}

void library::Library::giveBackBook(const std::string &title, ClientInLibrary &client) {

    for(shop::ConcreteBook book : client.borrowedByClient){

        //compare title from given pair and title as parameter
        if(book.getPairOfTitleAndAuthorBook().second == title){

            //returns index of client's vector where this particular book is situated
            int index = client.getIndexOfBorrowedBookWithTitle(title);

            //it should remove book with given index
            client.borrowedByClient.erase(client.borrowedByClient.begin(), client.borrowedByClient.begin() + index - 1);

            //and returns it to library
            this->manageBooks_.amounts_[1]++;
            break;
        }
    }

}

void library::Library::showBorrowedBooksByUser() {
    int i = 0;
    for(shop::ConcreteBook  borrowed : this->clients_[getIndexOfClientWithGivenID()].borrowedByClient){

        std::cout<<i+1<<". "<<borrowed.getPairOfTitleAndAuthorBook().second<<std::endl;
        i++;
    }
}

std::vector<shop::ConcreteBook> library::Library::giveBackBook(int choose, library::ClientInLibrary &client) {

    for(shop::ConcreteBook &book : client.borrowedByClient){

        //compare book
        if(book == client.borrowedByClient[choose]){


            //remove book with given index
            client.borrowedByClient.erase(client.borrowedByClient.begin() + choose);

            //remove term of this particular book
            client.termToGiveBackBorrowedBooks.erase(client.termToGiveBackBorrowedBooks.begin() + choose);


            //return given back book to library
            int currIndexOfGivenBackBook = getIndexOfGivenBackBook(book.getPairOfTitleAndAuthorBook().second);
            this->manageBooks_.amounts_[currIndexOfGivenBackBook]++;

            break;
        }
    }
    return client.borrowedByClient;
}

void library::Library::setClients(const std::vector<ClientInLibrary> &clients) {
    this->clients_ = clients;
}

int library::Library::getIndexOfGivenBackBook(const std::string &title) {

    for(int i = 0 ; i < manageBooks_.books_.size(); i++){
        if(manageBooks_.books_[i].getPairOfTitleAndAuthorBook().second == title){
            return i;
        }
    }
    return -1;
}

void library::Library::removeClient(std::string &clientID) {

    for(int i = 0 ; i < this->clients_.size(); i++){
        if(this->clients_[i].getNumberIDofClient() == clientID){
            this->clients_.erase( this->clients_.begin() + i);
        }
    }
}



