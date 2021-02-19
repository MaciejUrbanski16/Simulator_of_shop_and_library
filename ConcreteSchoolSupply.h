//
// Created by Admin on 18.02.2021.
//

#ifndef MACHINEOFSTATE_CONCRETESCHOOLSUPPLY_H
#define MACHINEOFSTATE_CONCRETESCHOOLSUPPLY_H

#include "SchoolSuppliesManager.h"
#include "BookManager.h"

#include <string>



namespace shop {
    class ConcreteSchoolSupply {
    public:
        ConcreteSchoolSupply() = default;

        ConcreteSchoolSupply(std::string name, ware_t price);

        virtual ~ConcreteSchoolSupply();

        void setName(const std::string &name);

        void setPrice(ware_t price);


        const std::string getName() const;

        ware_t getPrice() const;

    private:
        std::string name_;
        ware_t price_;
    };
}//end namespace shop

#endif //MACHINEOFSTATE_CONCRETESCHOOLSUPPLY_H
