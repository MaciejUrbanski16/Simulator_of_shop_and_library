//
// Created by Admin on 15.09.2020.
//

#ifndef MACHINEOFSTATE_SCHOOLSUPPLIES_H
#define MACHINEOFSTATE_SCHOOLSUPPLIES_H

#include "BookManager.h"

namespace shop
{

    ///OgÓLNA KLASA DO ZARZĄDZANIA LISTĄ DOSTĘPNYCH PRZYBORÓW SZKOLNYCH
    class SchoolSupplies: public Ware {
    public:
        std::string name;
        shop::ware_t price{};
        int amount{};

        SchoolSupplies() = default;
        SchoolSupplies(std::string name, ware_t price, int amount);

        //kontener do rpzechowywania wszystkich przyborów
        std::vector<SchoolSupplies> schoolSupplies;

        void readItemsFromFile()override ;
        void saveItemsToFile()override ;

        void presentationOfSupplies();

        void getSize();

        void chooseSup(Ware &towar);  //wybor przez uzytkownika przyborów z listy

        void getNamesAndAmounts();    //wyswietla nazwy przyborow i ich aktualną liczbę

        std::vector<int> amounts;
        std::vector<std::string> names;


        void refreshAmount();         //odswieża liczbe dostępnych przyborów po wyjęciu z bufora rzeczy odłożonych z koszyka z powrotem do sklepu

        void editionState();          //edycja stanu przyborów -> wybor dodania / usunięcia

    private:
        std::fstream fileWithSupplies;

        std::string line;

        //przygotowuje odczytane dane z pliku tak, aby możliwe było ich załadowanie do jednego kontenera
        //przechowujacego informacje o przyborach
        void createObjectsFromDates(std::vector<SchoolSupplies> &supplies,const std::string& line);


        //zwraca odpowiednie dane odpowiedniego typu
        template <typename dateType> dateType getDate(int &i, std::string line1);


        std::string nameOfSup;
        std::string priceOfSup;
        std::string amountOfSup;

        void addSuplies(); //dodanie nowego przyboru do listy dostepnych

        void remSuplies(); //usuniecie przyboru z listy dostępnych

        //parametry o które zwiększamy liste przyborów przy dodawaniu nowego przyboru
        std::string name_ADD;
        ware_t price_ADD;
        int amount_ADD;
    };

}


#endif //MACHINEOFSTATE_SCHOOLSUPPLIES_H
