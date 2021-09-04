//
// Created by Admin on 04.09.2021.
//

#ifndef MACHINEOFSTATE_OUTPUTTER_H
#define MACHINEOFSTATE_OUTPUTTER_H


#include <iostream>

class Outputter {
public:
    template <typename Items>
    static void logConcreteItems(const Items& items);
    static void logRemovingOfItem(const std::string& item);
    static void logWarningIfClientWantsToChangeStateOfShop();
    static void logInfoAboutChoosingItemFromList();

    static void logChooseOfPerformanceInItems();
};

template<typename Items>
void Outputter::logConcreteItems(const Items &items) {
    std::cout<<"The notepads that are available: "<<std::endl;
    for(int i = 0;i<items.size();i++)
    {
        std::cout<<i+1<<". "<<items.at(i).getFormat()<<std::endl;
    }
}

void Outputter::logWarningIfClientWantsToChangeStateOfShop(){
std::cout<<"There is not allowed to edit state of shop in CLIENT_MODE "<<std::endl;
std::cout<<"If you want you can now change mode to SELLER_MODE"<<std::endl;
}

void Outputter::logRemovingOfItem(const std::string& nameOfItem) {
    std::cout<<"The notepad with "<< nameOfItem <<"size was removed successfully!" <<std::endl;
}

void Outputter::logInfoAboutChoosingItemFromList() {
    std::cout<<"Choose note from list and give amount to change its amount "<<std::endl;
}

void Outputter::logChooseOfPerformanceInItems() {
    std::cout<<"1. Add notes to shop "<<std::endl;
    std::cout<<"2. Remove note from shop "<<std::endl;
}


#endif //MACHINEOFSTATE_OUTPUTTER_H
