//
// Created by Admin on 12.09.2020.
//

#ifndef MACHINEOFSTATE_BAGPACKMANAGER_H
#define MACHINEOFSTATE_BAGPACKMANAGER_H

#include "BookManager.h"
#include "ConcreteBagpack.h"

#include <string>
#include <map>


#include <fstream>
namespace shop {
    class ConcreteBagpack;
}

template<>
struct std::less<shop::ConcreteBagpack>;

namespace shop
{


    ///OGÓLNA KLASA DO ZARZĄDZANIA ZBIOREM PLECAKÓW
    class BagpackManager : public Ware {    //atrybuty: marka kolor cena
    public:


        int amount;
        BagpackManager() {}

        //BagpackManager(std::string mark, std::string color, ware_t price, int amount);


        std::string mark;
        std::string color;
        ware_t price;

        std::vector<BagpackManager> bags;

        std::map<ConcreteBagpack*, int> listOfBagpacks;
        std::vector<ConcreteBagpack> bagsFromFile;
        std::vector<int> amountsOfBags;


        ~BagpackManager();

        std::vector<std::string> allMarks;
        std::vector<int> allAmounts;

        void getMarks();       //przepisuje wartosci pol _mark kazdego obiektu do osobnego vectora
        void getAmounts();

        void readItemsFromFile() override ;
        void saveItemsToFile() override ;

        void presentationOfBags();

        void chooseBagToPurchases(Ware &purchases);

        void refreshObjectsAfterRemoving();

        void editionStateOfBags();

        void setChooseBag(int choose);

    private:
        std::string line;

        ConcreteBagpack *buffor = nullptr;



        std::string strToMark, strToColour,strToPrice,strToAmount,strTemp;

        int am;
        float pr;
        int _chooseBag;


        void prepareStrings(std::string basicString);


        void addBags();

        void removeBags();
    };
}

//to compare objects of ConcreteBagpack type



#endif //MACHINEOFSTATE_BAGPACKMANAGER_H
