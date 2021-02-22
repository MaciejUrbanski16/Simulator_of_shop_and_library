//
// Created by Admin on 19.02.2021.
//

#ifndef MACHINEOFSTATE_CLIENTINLIBRARY_H
#define MACHINEOFSTATE_CLIENTINLIBRARY_H

#include <string>
#include <vector>
#include "../ConcreteBook.h"



namespace library {


    class ClientInLibrary {
    public:
        ClientInLibrary() = default;

        ClientInLibrary(const std::string &nameOfClient, const std::string &surnameOfClient,
                        const std::string &numberIDofClient);

        //setters
        void setNameOfClient(const std::string &nameOfClient);
        void setSurnameOfClient(const std::string &surnameOfClient);
        void setNumberIDofClient(const std::string &numberIDofClient);

        void setBorrowedByClient(std::vector<shop::ConcreteBook> &borrowed);

        //getters
        const std::string &getNameOfClient() const;
        const std::string &getSurnameOfClient() const;
        const std::string &getNumberIDofClient() const;

        std::vector<shop::ConcreteBook> getBorrowedByClient();

        int getIDasInteger() const;

        int getIndexOfBorrowedBookWithTitle(const std::string &title);

        bool operator () (ClientInLibrary &c) const;


        //every client has his own list of borrowed books
        std::vector<shop::ConcreteBook> borrowedByClient;

        virtual ~ClientInLibrary();

    private:
        std::string nameOfClient_;
        std::string surnameOfClient_;
        std::string numberIDofClient_;//five-digit

    };

}//end namespace library


#endif //MACHINEOFSTATE_CLIENTINLIBRARY_H
