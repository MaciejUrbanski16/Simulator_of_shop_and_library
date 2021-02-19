//
// Created by Admin on 19.02.2021.
//

#include "ConcreteNotepad.h"

shop::ConcreteNotepad::ConcreteNotepad(std::string &format, int numberOfCards, shop::ware_t price) {
    this->format_ = format;
    this->numberOfCards_ = numberOfCards;
    this->price_ = price;
}

const std::string &shop::ConcreteNotepad::getFormat() const {
    return format_;
}

void shop::ConcreteNotepad::setFormat(const std::string &format) {
    format_ = format;
}

int shop::ConcreteNotepad::getNumberOfCards() const {
    return numberOfCards_;
}

void shop::ConcreteNotepad::setNumberOfCards(int numberOfCards) {
    numberOfCards_ = numberOfCards;
}

shop::ware_t shop::ConcreteNotepad::getPrice() const {
    return price_;
}

void shop::ConcreteNotepad::setPrice(shop::ware_t price) {
    price_ = price;
}



