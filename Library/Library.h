//
// Created by Admin on 19.02.2021.
//

#ifndef MACHINEOFSTATE_LIBRARY_H
#define MACHINEOFSTATE_LIBRARY_H

#include "../Managers/BookManager.h"
#include "ClientInLibrary.h"

#include "../ReadCsvTsv.h"
#include "../WriteCsvTsv.h"
#include "TimeOfBorrowing.h"

#include <ctime>

namespace library{
    class ClientInLibrary;
}

//specialize template class less to compare objects of type library::ClientInLibrary in my map
namespace std{

    template<> struct less<library::ClientInLibrary>{

        bool operator() (const library::ClientInLibrary& lhs, const library::ClientInLibrary& rhs) const{
            return lhs.getIDasInteger() < rhs.getIDasInteger();
        }
    };
}

namespace library {

    class Library {
    public:
        //
        Library(shop::BookManager &manageBooks);

        shop::BookManager getManageBooks();

        void setManageBooks(const shop::BookManager &manageBooks);

        bool loginToLibrary(int introYourID);
        void registerNewAccount(const std::string &name, const std::string &surname, const std::string &id);

        int enterIDtoLogin;

        int attemptsToLogin = 3;

        //storage id of logged client as integer
        int currentIDloggedIn;



        //return client's index from list of all clients
        int getIndexOfClientWithGivenID();

        virtual ~Library();

        //read/save clients and his borrowed books to *.tsv file
        void readUsersFromFile();

        void saveUsersToFile();

        char createNewAccount = 'n';
        bool validLogin = false; //checks if user is logged in

        std::string generateIDofNewClient();

        std::vector<ClientInLibrary> getClients();
        void setClients(const std::vector<ClientInLibrary> &clients);

        //add created client to list of all clients
        void addNewClient(const ClientInLibrary& client);


        bool canBorrow = true;
        void borrowBook(int position, const std::string &title);
        void giveBackBook(const std::string &title, ClientInLibrary &client);
        std::vector<shop::ConcreteBook> giveBackBook(int choose, ClientInLibrary &client);


        void showBorrowedBooksByUser();


    private:
        //instance to manage list of books
        shop::BookManager manageBooks_;

        //library has list of all clients
        std::vector<ClientInLibrary> clients_;
        std::vector<shop::ConcreteBook> borrowedBooks_;

        std::map<ClientInLibrary, std::vector<shop::ConcreteBook>> clientAndBorrowedBook;

        //remove client from list of all clients throughout given id
        void removeClient(std::string &clientID);


        int getIndexOfGivenBackBook(const std::string &title);
    };

}//end namespace library

#endif //MACHINEOFSTATE_LIBRARY_H
