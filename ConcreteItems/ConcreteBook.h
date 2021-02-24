//
// Created by Admin on 16.02.2021.
//

#ifndef MACHINEOFSTATE_CONCRETEBOOK_H
#define MACHINEOFSTATE_CONCRETEBOOK_H

#include "../Managers/BookManager.h"

#include <map>

namespace shop {

    class ConcreteBook {
    public:
        ConcreteBook(){}
        ConcreteBook(std::pair<std::string,std::string> &book, ware_t price);

        //getters
        std::pair<std::string,std::string> getPairOfTitleAndAuthorBook();
        ware_t getPrice();

        //setters
        void setPairOfTitleAndAuthorBook(std::pair<std::string,std::string> &book);
        void setPrice(ware_t price);

        bool operator == (ConcreteBook &c);
        friend std::ostream & operator << (std::ostream &out, ConcreteBook &book);

    private:
        std::pair<std::string, std::string> _book;  //storages key:AUTHOR with value:TITLE
        ware_t _price;
    };
}//end namespace shop

#endif //MACHINEOFSTATE_CONCRETEBOOK_H
