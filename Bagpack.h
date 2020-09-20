//
// Created by Admin on 12.09.2020.
//

#ifndef MACHINEOFSTATE_BAGPACK_H
#define MACHINEOFSTATE_BAGPACK_H
//#pragma once
#include <string>
#include "Book.h"
//#include <map>


#include <fstream>

namespace shop
{
    class Bagpack : public Towar {    //atrybuty: marka kolor cena
    public:
        std::string mark;
        std::string color;
        towar_int_t price;
        int amount;
        Bagpack() = default;

        Bagpack(std::string mark, std::string color, towar_int_t price,int amount);

        std::vector<shop::Bagpack> bags;

        void readBagpacksFromFile();

        void saveBagpacksToFile();

        void addBagpackToPurchases();

        bool areThereAnyBagpacks(); // zwroci falsz gdy nie ma danego plecaka w zasobach sklepu

        ///mozna by sprobowac cos z tym gitem teraz !!!

        ~Bagpack();

        std::vector<std::string> allMarks;
        std::vector<int> allAmounts;

        void getMarksAndAmounts();          //przepisuje wartosci pol mark amount kazdego obiektu do osobnych vectorów
        void getAmounts();

        void readItemsFromFile() override ;

        void saveItemsToFile() override ;

        void presentationOfBags();

        void chooseBag(Towar &purchases);

        void refreshObjectsAfterRemoving(std::vector<shop::Bagpack> &bags);

        void editionStateOfBags();

    private:
        std::string line;
        std::string marka = "Tgt";
        std::string colour = "red";
        shop::towar_int_t cena = 10;
        int amount_ = 5;

        std::string strToMark, strToColour,strToPrice,strToAmount,strTemp;

        int am;
        float pr;



        void prepareStrings(std::string basicString);


        void addBags();

        void removeBags();
    };
}



#endif //MACHINEOFSTATE_BAGPACK_H
