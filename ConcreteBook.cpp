//
// Created by Admin on 16.02.2021.
//

#include "ConcreteBook.h"

shop::ConcreteBook::ConcreteBook(std::pair<std::string, std::string> &book, shop::ware_t price) {
    this->_book = book;
    this->_price = price;
}

std::pair<std::string, std::string> shop::ConcreteBook::getPairOfTitleAndAuthorBook() {
    return this->_book;
}

shop::ware_t shop::ConcreteBook::getPrice() {
    return this->_price;
}

void shop::ConcreteBook::setPairOfTitleAndAuthorBook(std::pair<std::string, std::string> &book) {
    this->_book = book;
}

void shop::ConcreteBook::setPrice(shop::ware_t price) {
    this->_price = price;
}
