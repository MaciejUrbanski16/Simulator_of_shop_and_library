//

//

#ifndef MACHINEOFSTATE_ACCESSORIESFACTORY_H
#define MACHINEOFSTATE_ACCESSORIESFACTORY_H


#include "SchoolSupplies.h"
#include "Bagpack.h"


class AccessoriesFactory {
public:
    virtual shop::Ware * getConcreteTowar() const  = 0 ;
    virtual ~AccessoriesFactory() = default;
};

class SchoolSupliesFactory : public AccessoriesFactory{
public:
    shop::Ware *getConcreteTowar() const override  {
        shop::SchoolSupplies *s;
        s = new shop::SchoolSupplies;
        return nullptr; //TODO trzeba zmienic cały interface klasy Ware!!!zrobic ją klasą abstrakcyjną
    }
};

class BagpackFactory : public AccessoriesFactory{
public:
    shop::Bagpack *getConcreteTowar() const {
        return new shop::Bagpack();
    }
};


#endif //MACHINEOFSTATE_ACCESSORIESFACTORY_H
