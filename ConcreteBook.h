//
// Created by Admin on 26.01.2021.
//

#ifndef MACHINEOFSTATE_CONCRETEBOOK_H
#define MACHINEOFSTATE_CONCRETEBOOK_H

#include "Book.h"

class ConcreteBook :public shop::Book {
public:
    ConcreteBook(std::string title){
        this->title = title;
    }
private:
    std::string title;
};


#endif //MACHINEOFSTATE_CONCRETEBOOK_H
