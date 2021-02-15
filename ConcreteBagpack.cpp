//
// Created by Admin on 12.02.2021.
//

#include "ConcreteBagpack.h"

std::string shop::ConcreteBagpack::getMark() const {
    return this->_mark;
}

std::string shop::ConcreteBagpack::getColor() const {
    return this->_color;
}

double shop::ConcreteBagpack::getPrice() const {
    return this->_price;
}

shop::ConcreteBagpack::ConcreteBagpack(std::string &mark, std::string &color, double price) {
    this->_mark = mark;
    this->_color = color;
    this->_price = price;
}

void shop::ConcreteBagpack::setMark(std::string &mark) {
    this->_mark = mark;
}

void shop::ConcreteBagpack::setColor(std::string &color) {
    this->_color = color;
}

void shop::ConcreteBagpack::setPrice(shop::towar_t price) {
    this->_price = price;
}

std::ostream &shop::operator<<(std::ostream &out, const ConcreteBagpack &b) {
    return out << "Mark of bagpack: " << b.getMark() <<", color: " << b.getColor() <<", price: " <<b.getPrice() <<std::endl;
}
