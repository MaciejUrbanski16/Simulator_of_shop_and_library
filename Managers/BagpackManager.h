//
// Created by Admin on 12.09.2020.
//

#ifndef MACHINEOFSTATE_BAGPACKMANAGER_H
#define MACHINEOFSTATE_BAGPACKMANAGER_H

#include "BookManager.h"
#include "../ConcreteItems/ConcreteBagpack.h"

#include <string>
#include <map>


#include <fstream>
namespace shop {

    //forward declaration
    class ConcreteBagpack;
}

//forward declaration to compare my own object in map
template<>
struct std::less<shop::ConcreteBagpack>;

namespace shop {


    ///OGÓLNA KLASA DO ZARZĄDZANIA ZBIOREM PLECAKÓW
    class BagpackManager : public Ware {    //atrybuty: marka kolor cena
    public:


        int amount;

        BagpackManager() {}

        ware_t price;

        std::vector<BagpackManager> bags;

        std::map<ConcreteBagpack *, int> listOfBagpacks;
        std::vector<ConcreteBagpack> bagsFromFile;
        std::vector<int> amountsOfBags;


        ~BagpackManager();

        std::vector<std::string> allMarks;

        void getMarks();


        void readItemsFromFile() override;

        void saveItemsToFile() override;

        void presentationOfBags();

        void chooseBagToPurchases(Ware &purchases);


        void editionStateOfBags(); //adding/removing concrete bags -->only in SELLER_MODE

    private:
        std::string line;

        std::string strToMark, strToColour, strToPrice, strToAmount;

        int am;
        float pr;
        int _chooseBag;

        //prepare string read from file and after that create new object of ConcreteBagpack type
        void prepareStrings(std::string basicString);


        void addBags(); //add bag to shop (only in SELLER_MODE)

        void removeBags(); //incrementAmountOfReturnedItem bag from shop (only in SELLER_MODE)
    };
}

#endif //MACHINEOFSTATE_BAGPACKMANAGER_H
