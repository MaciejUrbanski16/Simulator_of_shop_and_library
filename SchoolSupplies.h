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

        void readItemsFromFile(std::vector<SchoolSupplies> &supplies);
        void saveItemsToFile();

        void presentationOfSupplies();

        void getSize();

        void chooseSup(Towar &towar);

        void getNamesAndAmounts();

        std::vector<int> amounts;
        std::vector<std::string> names;

        //void refreshAmount();

        void refreshAmount(std::vector<SchoolSupplies> &schoolSupplies1);

        void editionState();

    private:
        std::fstream fileWithSupplies;

        std::string line;

        void createObjectsFromDates(std::vector<SchoolSupplies> &supplies,const std::string& line);

        template <typename dateType> dateType getDate(int &i, std::string line1);

        std::string nameOfSup;
        std::string priceOfSup;
        std::string amountOfSup;

    };

}


#endif //MACHINEOFSTATE_SCHOOLSUPPLIES_H
