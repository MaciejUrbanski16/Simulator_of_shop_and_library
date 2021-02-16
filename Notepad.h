//
// Created by Admin on 13.08.2020.
//

#ifndef MACHINEOFSTATE_NOTEPAD_H
#define MACHINEOFSTATE_NOTEPAD_H

#include <iostream>
#include <cassert>
#include <string>
#include <fstream>

#include "BookManager.h"
#include "Application.h"
//#include <map>



namespace shop
{

    ///OGÓLNA KLASA DO ZARZĄDZANIA LISTĄ DOSTĘPNYCH ZESZYTÓW
    class Notepad : public shop::Ware
    {
    public:
        std::string color;
        std::vector<std::string>dimensions;
        std::vector<ware_t>price;
        std::vector<int>amount;
        bool noteWithLines;
        int chooseOfColor(); //wybor koloru ->do zrobienia

        int chooseOfDimension(); //wybór konkretnego zeszytu przez uzytkownika


        void setDimensionsOfNote();  //dostepne rozmiary zesytow

        bool checkIfNoteIsAvailable(int); //sprawdza dostępność wybranej przez użytkownika pozycji

        void saveItemsToFile() override;
        void readItemsFromFile()override;

        void returnNoteFromBasketToShop(std::vector<std::string> removedThings, std::vector<std::string> dimensions, std::vector<int>amount);



        void addThingFromRemovedToShop(std::map<std::string, int> map);

        std::vector<int>
        incrementAmountofRemovedThing(std::map<std::string, int> incrementAmountOfNotesAfterRemovingFromBaskte);

        std::vector<int>incrementAmountOfNotesAfterReturnedToShop(Application &app);

        void editionStateOfNotes(); //pozwala dodawać/usuwac zeszyty (w trybie sprzedawcy)

        void addNotesToShop(int mode, int howMuch,int where); //pozwala edytować liczbę dostępnych zeszytów o danym rozmiarze

    private:
        std::string dim;
        int choose;
        int dimensionsSize; //ilosc elementow vectora dimension


        void showResourcesOfNotes(); //pokazuje aktualny stan zeszytów w sklepie


        void addingByOwnerNewNote(); //pozwala dodawac zeszyt do sklepu (w trybie sprzedawcy)
        void removeByOwnerNote();


    };
}


#endif //MACHINEOFSTATE_NOTEPAD_H
