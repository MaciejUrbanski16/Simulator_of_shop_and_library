//
// Created by Admin on 04.09.2021.
//

#ifndef MACHINEOFSTATE_INPUTTER_H
#define MACHINEOFSTATE_INPUTTER_H


#include <cstdint>
#include <iostream>

class Inputter {
public:
    template<typename Items>
    static int inputNoToChooseConcreteItem(const Items& items);
};

template<typename Items>
int Inputter::inputNoToChooseConcreteItem(const Items &items) {
    bool good,bad;
    int choose{0};
    do{
        std::cin>>choose;
        good = std::cin.good();
        bad = std::cin.bad();
        std::cin.clear();
        std::cin.sync();
    }while(((choose<=0 )||choose>items.size()) || (good==0||bad==1));
    return choose;
}


#endif //MACHINEOFSTATE_INPUTTER_H
