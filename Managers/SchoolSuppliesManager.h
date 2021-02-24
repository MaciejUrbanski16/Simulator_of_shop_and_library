//
// Created by Admin on 15.09.2020.
//

#ifndef MACHINEOFSTATE_SCHOOLSUPPLIESMANAGER_H
#define MACHINEOFSTATE_SCHOOLSUPPLIESMANAGER_H


#include "../ConcreteItems/ConcreteSchoolSupply.h"
#include "BookManager.h"

namespace shop
{
    //forward declaration
    class ConcreteSchoolSupply;


    ///GENERAL CLASS TO MANAGE TO LIST OF AVAILABLE SCHOOL SUPPLIES
    class SchoolSuppliesManager: public Ware {
    public:
        std::string name;
        shop::ware_t price{};
        int amount{};

        SchoolSuppliesManager() = default;


        //containers to storage all of available school supplies and their amounts
        std::vector<ConcreteSchoolSupply> schoolSupplies;
        std::vector<int> amounts;

        //read/write data
        void readItemsFromFile()override ;
        void saveItemsToFile()override ;

        void presentationOfSupplies();  //show user all list of school supplies

        uint32_t getSize();

        void chooseSup(Ware &towar);  //choose of concrete school supply from list

        std::vector<std::string> getNames();    //returns table of school supply's names


        void editionState();          //edition state of school supplies --> available only in SELLER_MODE

    private:
        std::fstream fileWithSupplies;

        std::string line;

        //preparing date after loading from file so that storage in special container all of them
        void createObjectsFromDates(const std::string& line);


        //returns date in proper type
        template <typename dateType> dateType getDate(int &i, std::string line1);


        std::string nameOfSup;
        std::string priceOfSup;
        std::string amountOfSup;

        void addSuplies(); //add new school supply (SELLER MODE)

        void remSuplies(); //incrementAmountOfReturnedItem school supply from shop (SELLER_MODE)

        //list of school supplies is incremented using these parameters
        std::string name_ADD;
        ware_t price_ADD;
        int amount_ADD;

        //table to storage names of school supplies (useful when user removes thing from basket to shop)
        std::vector<std::string> names_;
    };

}


#endif //MACHINEOFSTATE_SCHOOLSUPPLIESMANAGER_H
