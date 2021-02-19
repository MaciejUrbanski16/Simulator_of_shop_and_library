//
// Created by Admin on 13.08.2020.
//

#ifndef MACHINEOFSTATE_NOTEPADMANAGER_H
#define MACHINEOFSTATE_NOTEPADMANAGER_H

#include <iostream>
#include <cassert>
#include <string>
#include <fstream>

#include "BookManager.h"
#include "ConcreteNotepad.h"
//#include "Application.h"

namespace shop
{

    //forward declaration
    class ConcreteNotepad;

    ///GENERAL CLASS TO MANAGE TO LIST OF NOTEPADS
    class NotepadManager : public Ware
    {
    public:

        std::vector<ConcreteNotepad> notepads;
        std::vector<int> amounts;

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

        std::vector<std::string> getFormats();

    private:
        std::string dim;
        int choose;
        int dimensionsSize; //ilosc elementow vectora dimension


        void showResourcesOfNotes(); //pokazuje aktualny stan zeszytów w sklepie


        void addingByOwnerNewNote(); //pozwala dodawac zeszyt do sklepu (w trybie sprzedawcy)
        void removeByOwnerNote();


    };
}


#endif //MACHINEOFSTATE_NOTEPADMANAGER_H
