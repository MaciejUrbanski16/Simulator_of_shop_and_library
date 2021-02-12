//
// Created by Admin on 12.02.2021.
//

#ifndef MACHINEOFSTATE_CONCRETEBAG_H
#define MACHINEOFSTATE_CONCRETEBAG_H

//#include "ShopWare.h"

#include <string>

namespace shop {

    ///TODO ilosc ConcreteBag przetrzymywac w mapie
    class ConcreteBag {
    public:
        ConcreteBag() = default;
        ConcreteBag(std::string mark,std::string color,double price):mark(mark), color(color), price(price){}
        std::string getMark();
        std::string getColor();
        double getPrice();

    private:
        std::string mark;
        std::string color;
        double price;
    };
}


#endif //MACHINEOFSTATE_CONCRETEBAG_H
