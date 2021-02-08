//
// Created by Admin on 26.01.2021.
//

#ifndef MACHINEOFSTATE_ACCESORIES_H
#define MACHINEOFSTATE_ACCESORIES_H

#endif //MACHINEOFSTATE_ACCESORIES_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include <memory>

#include <map>


enum                        //enumeracja do poruszania sie w procesie zakupu
{
    START,
    INTRODUCTION,
    CHOOSE,
    CONFIRM,
    END
};

enum
{
    SELLER_MODE,                //tryb sprzedawcy
    CUSTOMER_MODE               //tryb klienta
};
enum
{
    KSIAZKI,
    ZESZYTY,
    TORNISTRY,
    PLECAKI,
    PIORNIKI,
    PRZYBORY,
    ZABAWKI,
    NOTESY
};


extern int stage;
extern int mode;

namespace shop {
    typedef double towar_int_t;

    ///OGÓLNA KLASA TOWARU
    class Ware
    {
    private:

    public:
        Ware(){}

        bool available;
        towar_int_t praise;
        int amount;
        std::string name;


        int paramOfChoosenThing;

        //funkcje odczytu i zapisu danych
        virtual void readItemsFromFile();
        virtual void saveItemsToFile();

        //kontenery do przechowywania wybranych przez klienta rzeczy ze sklepu
        std::vector<std::string> orderedPurchasesName;
        std::vector<towar_int_t> orderedPurchasesPrice;

        int position;


        static bool enterToShop();          //wejscie do sklepu jedynie po potweirzdzeniu checi wejscia

        void remove(std::vector<std::string> &removedThings,
                    std::vector<std::string> &dimensions,
                    std::vector<int> &amount);

        void showOrderedPurchases();        //wyswietla wszystkie rzeczy dodane do koszyka

        std::string removeThingFromPurchases();    //usuwa rzecz dodana do koszyka

        void addToPurchases();              //dodaje do koszyka wybrana rzecz

        int choosingFromList(int, int);

        int enteringTheNumber(int minValue, int maxValue);

        int changeModeToSellerMode(std::string password,
                                   int mode); //zmienia treyb z klienta na sprzedawce i na odwrót


        towar_int_t roundFloatToSecond(towar_int_t d);

    };
}