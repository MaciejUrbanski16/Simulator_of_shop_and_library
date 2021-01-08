//
// Created by Admin on 15.09.2020.
//

#ifndef MACHINEOFSTATE_SCHOOLSUPPLIES_H
#define MACHINEOFSTATE_SCHOOLSUPPLIES_H

#include "Book.h"

namespace shop
{

    class SchoolSupplies {
    public:
        std::string name;
        shop::towar_int_t price{};
        int amount{};

        SchoolSupplies() = default;
        SchoolSupplies(std::string name,towar_int_t price, int amount);

        std::vector<SchoolSupplies> schoolSupplies;

        void readItemsFromFile();
        void saveItemsToFile();

        void presentationOfSupplies();

        void getSize();

        void chooseSup(Ware &towar);

        void getNamesAndAmounts();

        std::vector<int> amounts;
        std::vector<std::string> names;

        //void refreshAmount();

        void refreshAmount();

        void editionState();

    private:
        std::fstream fileWithSupplies;

        std::string line;

        void createObjectsFromDates(std::vector<SchoolSupplies> &supplies,const std::string& line);

        template <typename dateType> dateType getDate(int &i, std::string line1);

        std::string nameOfSup;
        std::string priceOfSup;
        std::string amountOfSup;

        void addSuplies();

        void remSuplies();

        std::string name_ADD;
        towar_int_t price_ADD;
        int amount_ADD;
    };

}


#endif //MACHINEOFSTATE_SCHOOLSUPPLIES_H
