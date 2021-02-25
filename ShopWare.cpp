//
// Created by Admin on 06.08.2020.
//

#include "ShopWare.h"

namespace shop {


    Ware::Ware(Application &application) : application_(application) {

    }

    void Ware::readItemsFromFile() {

    }

    void Ware::saveItemsToFile() {

    }


    int Ware::changeModeToSellerMode(std::string password, int mode) {
        std::string givenPassword;
        int attemp = 3;
        if (!(mode == SELLER_MODE)) {
            if (mode == CLIENT_MODE) {
                std::cout << "To go to seller mode you have to provide password: " << std::endl;
                std::cin >> givenPassword;


                for (int i = 0; i < 3; i++) {
                    if (password == givenPassword && attemp > 0) {
                        mode = SELLER_MODE;
                        attemp = 3;
                        this->inSellerMode = true;
                        std::cout << "The mode was changed successfully. Now you can edit state of shop" << std::endl;
                        break;
                    } else {
                        attemp--;
                        std::cout << "Provided password is incorrect. There left: " << attemp << " attempts "
                                  << std::endl;
                        std::cin >> givenPassword;
                    }
                }
            }
        } else {
            mode = CLIENT_MODE;
            std::cout << "The mode was changed. Actual mode is CLIENT_MODE" << std::endl;

        }
        return mode;
    }


    int Ware::enteringTheNumber(int minValue, int maxValue) {
        int where = -1;

#ifndef TESTING
        bool good1, bad1;

        do {
            std::cin >> where;
            good1 = std::cin.good();
            bad1 = std::cin.bad();
            std::cin.clear();
            std::cin.sync();
        } while ((where < minValue || where > maxValue) || (good1 == 0 || bad1 == 1));

#else
        where = 4;
#endif
        return where;
    }

    std::string Ware::removeThingFromPurchases() {
        showOrderedPurchases();
        int choose = -1;

        if (!orderedPurchasesName.empty()) {
            std::cout << "Choose number of thing you want to incrementAmountOfReturnedItem: " << std::endl;

            choose = enteringTheNumber(1, orderedPurchasesName.size());

            choose--; //vector is iterated from zero

            std::string removedName = orderedPurchasesName[choose];
            ware_t removedPrice = orderedPurchasesPrice[choose];

            orderedPurchasesName.erase(orderedPurchasesName.begin() + choose);
            orderedPurchasesPrice.erase(orderedPurchasesPrice.begin() + choose);

            std::cout << "The: " << removedName << " was removed successfully! " << std::endl;

            showOrderedPurchases();
            return removedName;
        } else {
            std::cout << "There is no thing to incrementAmountOfReturnedItem!!!" << std::endl;
            return "";
        }
    }

    void Ware::addToPurchases() {

        orderedPurchasesName.push_back(name);
        orderedPurchasesPrice.push_back(praise);

        std::cout << "The " << name << " was added to basket and it costs " << praise << std::endl;
    }

    void Ware::showOrderedPurchases() {
        std::cout << "Actual state of your basket: " << std::endl;

        for (int i = 0; i < orderedPurchasesName.size(); i++) {
            std::cout << i + 1 << ". Name: " << orderedPurchasesName[i] << " costs: " << orderedPurchasesPrice[i]
                      << std::endl;

        }
    }


    ware_t Ware::roundFloatToSecond(ware_t d) {

        int y = d * 1000; // shift comma four position

        return (y / 10) * 0.01; //incrementAmountOfReturnedItem last part of number and change to floating point number
    }

    void
    Ware::incrementAmountOfReturnedItem(std::vector<std::string> &removedThings, std::vector<std::string> &dimensions,
                                        std::vector<int> &_amount) {
        for (int i = 0; i < removedThings.size(); i++) {
            for (int j = 0; j < dimensions.size(); j++) {
                if (removedThings[i] == dimensions[j]) {
                    if (!removedThings.empty()) {
                        removedThings.erase(removedThings.begin() + i);
                        _amount[j]++;
                    }

                }
            }
        }

    }
}//end namespace shop






