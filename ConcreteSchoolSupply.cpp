//
// Created by Admin on 18.02.2021.
//

#include "ConcreteSchoolSupply.h"

shop::ConcreteSchoolSupply::ConcreteSchoolSupply(std::string name, shop::ware_t price)
:name_(name), price_(price)
{
}

shop::ConcreteSchoolSupply::~ConcreteSchoolSupply() {

}

const std::string shop::ConcreteSchoolSupply::getName() const {
    return name_;
}

shop::ware_t shop::ConcreteSchoolSupply::getPrice() const {
    return price_;
}

void shop::ConcreteSchoolSupply::setName(const std::string &name) {
    name_ = name;
}

void shop::ConcreteSchoolSupply::setPrice(shop::ware_t price) {
    price_ = price;
}

