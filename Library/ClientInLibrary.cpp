//
// Created by Admin on 19.02.2021.
//

#include "ClientInLibrary.h"


library::ClientInLibrary::ClientInLibrary(const std::string &nameOfClient,
                                          const std::string &surnameOfClient,
                                          const std::string &numberIDofClient) : nameOfClient_(nameOfClient),
                                                                                 surnameOfClient_(surnameOfClient),
                                                                                 numberIDofClient_(numberIDofClient) {

    this->borrowedByClient = std::vector<shop::ConcreteBook>();
}

library::ClientInLibrary::~ClientInLibrary() {

}

const std::string &library::ClientInLibrary::getNameOfClient() const {
    return nameOfClient_;
}

const std::string &library::ClientInLibrary::getSurnameOfClient() const {
    return surnameOfClient_;
}

const std::string &library::ClientInLibrary::getNumberIDofClient() const {
    return numberIDofClient_;
}

void library::ClientInLibrary::setNameOfClient(const std::string &nameOfClient) {
    nameOfClient_ = nameOfClient;
}

void library::ClientInLibrary::setSurnameOfClient(const std::string &surnameOfClient) {
    surnameOfClient_ = surnameOfClient;
}

void library::ClientInLibrary::setNumberIDofClient(const std::string &numberIDofClient) {
    numberIDofClient_ = numberIDofClient;
}

int library::ClientInLibrary::getIDasInteger() const {
    return std::atoi(this->numberIDofClient_.c_str());
}

bool library::ClientInLibrary::operator()(library::ClientInLibrary &c) const {
    return this->getIDasInteger() < c.getIDasInteger();
}

void library::ClientInLibrary::setBorrowedByClient(std::vector<shop::ConcreteBook> &borrowed) {
    this->borrowedByClient = borrowed;

}

std::vector<shop::ConcreteBook> library::ClientInLibrary::getBorrowedByClient() {
    return this->borrowedByClient;
}

int library::ClientInLibrary::getIndexOfBorrowedBookWithTitle(const std::string &title) {

    int ret = 0;

    for(int i = 0 ; i < borrowedByClient.size(); i++){
        if(borrowedByClient[i].getPairOfTitleAndAuthorBook().second == title){
            ret = i;
            break;
        }
    }

    return ret;
}

void library::ClientInLibrary::setTermToGiveBack(std::vector<std::string> &termsToGiveBack) {
    this->termToGiveBackBorrowedBooks = termsToGiveBack;
}

std::pair<int, library::TimeLeft> library::ClientInLibrary::getTheShortestDeadline() {

    exchangeTerms();

    std::vector<int> indexes;

    for(int i = 0; i <terms.size(); i++){
        indexes.push_back(i);
    }


    for(int i = 0 ; i < this->terms.size(); i++){
        for(int j = 0 ; j < this->terms.size()-1; j++){
            if(terms[j] > terms[j + 1]){
                auto temp = terms[j+1];
                terms[j+1] = terms[j];
                terms[j] = temp;
                int tempIndex = indexes[j+1];
                indexes[j+1] = indexes[j];
                indexes[j] = tempIndex;
            }
            else{
                int p = 0;
                p++;
            }
        }
    }

    std::pair<int, library::TimeLeft> deadline(indexes.back(),terms.back());
    return deadline;
}

void library::ClientInLibrary::exchangeTerms() {

    for(int i = 0 ; i < this->termToGiveBackBorrowedBooks.size(); i++){

        this->terms.emplace_back(termToGiveBackBorrowedBooks[i]);
    }

}




