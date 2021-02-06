//
// Created by Admin on 26.07.2020.
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


//class Ware;

enum                        //enumeracja do poruszania sie w procesie zakupu
{
    START,
    CHOOSE,
    INTRODUCTION,
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

    class Ware                     //ogolna klasa towaru sklepu
    {
    public:
        Ware(std::vector<shop::Ware>::iterator iterator);

        bool available;
        towar_int_t praise;
        int amount;
        std::string name;


        int paramOfChoosenThing;

        virtual void readItemsFromFile();

        virtual void saveItemsToFile();

        std::vector<std::string> orderedPurchasesName;
        std::vector<towar_int_t> orderedPurchasesPrice;



    public:
        Ware() {
            praise = 0;
            amount = 0;
            available = true;

        }

        int position;


        static bool enterToShop();          //wejscie do sklepu jedynie po potweirzdzeniu checi wejscia

        void
        remove(std::vector<std::string> &removedThings, std::vector<std::string> &dimensions, std::vector<int> &amount);

        void showOrderedPurchases();        //wyswietla wszystkie rzeczy dodane do koszyka

        std::string removeThingFromPurchases();    //usuwa rzecz dodana do koszyka

        void addToPurchases();              //dodaje do koszyka wybrana rzecz





        //virtual void addThingToShop(int stage);      //dodanie przedmiotu do sklepu -mozliwe jedynie w trybie sprzedawcy

        int choosingFromList(int, int);

        int enteringTheNumber(int minValue, int maxValue);

        int changeModeToSellerMode(std::string password,
                                   int mode); //zmienia treyb z klienta na sprzedawce i z spr na klienta




        template<class type>
        void remove1(type el);

        template<typename Type>
        void removeThing(Type *obj, std::vector<Type> &things);

        towar_int_t roundFloatToSecond(towar_int_t d);
    };
}