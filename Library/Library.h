//
// Created by Admin on 19.02.2021.
//

#ifndef MACHINEOFSTATE_LIBRARY_H
#define MACHINEOFSTATE_LIBRARY_H

#include "../BookManager.h"
#include "ClientInLibrary.h"

#include "../ReadCsvTsv.h"
#include "../WriteCsvTsv.h"

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
        Library(shop::BookManager &manageBooks);

        shop::BookManager getManageBooks();

        void setManageBooks(const shop::BookManager &manageBooks);

        bool loginToLibrary(int introYourID);
        void registerNewAccount(const std::string &name, const std::string &surname, const std::string &id);

        int enterIDtoLogin;
        std::string enterPasswordToLogin;
        int attemptsToLogin = 3;

        int currentIDloggedIn;

        int getIndexOfClientWithGivenID();

        virtual ~Library();

        void readUsersFromFile();

        void saveUsersToFile();

        char createNewAccount = 'n';
        bool validLogin = false; //checks if user is logged in

        std::string generateIDofNewClient();

        std::vector<ClientInLibrary> getClients();
        void setClients(const std::vector<ClientInLibrary> &clients);

        void addNewClient(const ClientInLibrary& client);


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



        void removeClient(std::string &clientID);


        int getIndexOfGivenBackBook(const std::string &title);
    };

}//end namespace library

#endif //MACHINEOFSTATE_LIBRARY_H
