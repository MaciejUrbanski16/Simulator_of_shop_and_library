//
// Created by Admin on 26.07.2020.
//

#ifndef MACHINEOFSTATE_ACCESORIES_H
#define MACHINEOFSTATE_ACCESORIES_H

#endif //MACHINEOFSTATE_ACCESORIES_H

#include <iostream>
#include <string>
#include <vector>



#include <map>
//#include "Book.h"
//#include "Book.h"

//class Towar;



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

namespace shop
{


    typedef float towar_int_t ;
    class Towar                     //ogolna klasa towaru sklepu
    {
    public:
        Towar(std::vector<shop::Towar>::iterator iterator);

        bool available;
        towar_int_t praise;
        int amount;
        std::string name;
        int etap;
        int mode;
        int paramOfChoosenThing;

        virtual void readItemsFromFile() ;
        virtual void saveItemsToFile() ;

        std::vector<std::string>orderedPurchasesName;
        std::vector<towar_int_t>orderedPurchasesPrice;

        std::vector<std::string>removedThings;              //kontener do przechowywania rzeczy usunietych przez
                                                            //kupujacego z koszyka jeszcze w trakcie zakupow
        std::map<std::string, int> pairOfRemovedAndItsPosition ;

        enum                        //enumeracja do poruszania sie w procesie zakupu
        {
            START,
            CHOOSE,
            INTRODUCTION,
            CONFIRM,
            END
        };

        template <typename T> void  addThing(T *obj, std::vector<std::string> names,std::vector<towar_int_t> prices, std::vector<int> amounts);

        //template <typename Type> void removeThing(Type *obj, std::vector<Type> &things);

    public:
        Towar()
        {
            praise = 0;
            amount = 0;
            available = true;

        }
        int position;


        static bool enterToShop();          //wejscie do sklepu jedynie po potweirzdzeniu checi wejscia

        void showOrderedPurchases();        //wyswietla wszystkie rzeczy dodane do koszyka

        std::string removeThingFromPurchases();    //usuwa rzecz dodana do koszyka

        void addToPurchases();              //dodaje do koszyka wybrana rzecz

        void presentationOfServices();      //przedstawuienie uslug

        int chooseOfService();              //wybor kategorii

        void addThingToShop(int mode);      //dodanie przedmiotu do sklepu -mozliwe jedynie w trybie sprzedawcy

        int choosingFromList(int, int);

        int enteringTheNumber(int minValue, int maxValue);

        int changeModeToSellerMode(std::string password,int mode); //zmienia treyb z klienta na sprzedawce i z spr na klienta

        void saveRemovedToFile();

        void readRemoveFromFile();


        template<class type>
        void remove1(type el);

        template<typename Type>
        void removeThing(Type *obj,std::vector<Type> &things);
    };

    //std::vector<Towar> towaryZakupione;




/*
    class Tornister : public Towar
    {
    public:
        towar_int_t rozmiar;
        std::vector<Tornister> bookedBagpack;

    };

    class Piornik : public Towar
    {
    public:
        bool pencilCase;
        std::vector<Piornik> bookedPencilCases;
        template<typename T > func(T wyrazwnie){return wyrazenie;}
    };*/

 /*   class Przybory : public Towar
    {
    public:
        std::string type;
        towar_int_t amount;
        std::string possibleTypes[7] = {"linijka","ekierka","cyrkiel","katomierz","olowek","dlugopis","gumka"};
        int ilosci[7] =                 {1,          5,       4,         12,         32,     23,         17};
        float cena[7]   =               {1.12,      2.79,    1.90,      2.09,     1.12,     4.79,      3.59};
        Przybory(std::string type, towar_int_t amount)
        {
            this->type = type;
            this->amount = amount;
        }
        std::vector<Przybory> bookedPrzybory;            //kontener  na wykonane zakupy
    };*/

}
