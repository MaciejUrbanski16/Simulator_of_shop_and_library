//
// Created by Admin on 06.08.2020.
//

#ifndef MACHINEOFSTATE_ACCESORIES_H
#define MACHINEOFSTATE_ACCESORIES_H

#endif //MACHINEOFSTATE_ACCESORIES_H

#include "Application.h"

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include <memory>

#include <map>


enum                        //all process of shopping
{
    START,
    INTRODUCTION,
    CHOOSE,
    CONFIRM,
    END
};

enum
{
    SELLER_MODE,                //seller mode
    CLIENT_MODE               //customer mode
};

namespace shop {

    //forward declaration
    class ConcreteBook;
    typedef double ware_t;

    ///GENERAL CLASS OF WARE
    class Ware
    {
    protected:
        Application application_;
    public:
        Ware()= default;

        //make available all configuration of program during shopping
        explicit Ware(Application &application);

        bool available{};
        ware_t praise{};
        int amount{};
        std::string name;


        int indexOfChoosenThing{};

        //READ AND WRITE DATA TO PROPER FILES
        virtual void readItemsFromFile();
        virtual void saveItemsToFile();

        //containers to storage chosen things by customers
        std::vector<std::string> orderedPurchasesName;
        std::vector<ware_t> orderedPurchasesPrice;

        int position{};  //assign position of concrete thing in list

        bool inSellerMode = false;  //seller do not need buy anything in his own shop


        static bool enterToShop();

        //things which were removed from basket are returned to shop
        void incrementAmountOfReturnedItem(std::vector<std::string> &removedThings,
                                           std::vector<std::string> &dimensions,
                                           std::vector<int> &amount);

        //void  incrementAmountOfReturnedItem(std::vector<std::string> &removedThings, std::vector<shop::ConcreteBook> &books,std::vector<int>&amount);


        void showOrderedPurchases();

        std::string removeThingFromPurchases();    //incrementAmountOfReturnedItem thing from basket

        void addToPurchases();              //add chosen thing to basket

        int enteringTheNumber(int minValue, int maxValue);

        int changeModeToSellerMode(std::string password,
                                   int mode); //change mode (CLIENT_MODE --> SELLER_MODE (required password),
                                                            // SELLER_MODE --> CLIENT_MODE (without password))


        ware_t roundFloatToSecond(ware_t d);

    };
}