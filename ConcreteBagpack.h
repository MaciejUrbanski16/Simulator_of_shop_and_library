//
// Created by Admin on 12.02.2021.
//

#ifndef MACHINEOFSTATE_CONCRETEBAGPACK_H
#define MACHINEOFSTATE_CONCRETEBAGPACK_H

#include "BagpackManager.h"

#include <string>
namespace shop {
    class ConcreteBagpack;
}

template<>
struct std::less<shop::ConcreteBagpack>;

namespace shop {
    //class ConcreteBagpack;

    ///TODO ilosc ConcreteBagpack'ow przetrzymywac w mapie
    //typedef double ware_t;
    class ConcreteBagpack {
    public:
        ConcreteBagpack() = default;
        ConcreteBagpack(std::string &mark, std::string &color, double price);

        //getters
        std::string getMark() const;
        std::string getColor() const;
        double getPrice() const;

        //setters
        void setMark(std::string &mark);
        void setColor(std::string &color);
        void setPrice(shop::ware_t price);


        //overloaded operators
        bool operator()(const ConcreteBagpack &other1, const ConcreteBagpack &other2) const {
            return other1.getPrice() < other2.getPrice();
        }

        bool operator !=( const ConcreteBagpack &other2) const {
            return (this->getPrice() != other2.getPrice()) || (this->getMark() != other2.getMark())
                   || (this->getColor() != other2.getColor());
        }

        friend std::ostream& operator <<(std::ostream& out, const ConcreteBagpack &bag);



    private:
        std::string _mark;
        std::string _color;
        double _price;
    };
}


namespace std {

    template<>
    struct less<shop::ConcreteBagpack> {
        bool operator()(const shop::ConcreteBagpack &lhs, const shop::ConcreteBagpack &rhs)const {
            return lhs.getPrice() < rhs.getPrice();
        }
    };

}



#endif //MACHINEOFSTATE_CONCRETEBAGPACK_H
