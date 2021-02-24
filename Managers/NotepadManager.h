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
#include "../ConcreteItems/ConcreteNotepad.h"
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


        std::vector<std::string>dimensions;
        std::vector<ware_t>price;
        std::vector<int>amount;

        std::string color;
        bool noteWithLines;
        int chooseOfColor(); //wybor koloru ->do zrobienia

        int chooseOfDimension(); //wybór konkretnego zeszytu przez uzytkownika


        bool checkIfNoteIsAvailable(int); //sprawdza dostępność wybranej przez użytkownika pozycji

        void saveItemsToFile() override;
        void readItemsFromFile()override;


        void editionStateOfNotes(); //pozwala dodawać/usuwac zeszyty (w trybie sprzedawcy)

        void addNotesToShop(int mode, int howMuch,int where); //pozwala edytować liczbę dostępnych zeszytów o danym rozmiarze

        std::vector<std::string> getFormats();

    private:

        int choose;

        void showResourcesOfNotes(); //show actual state of notes

        //allow add new (remove) note to list of notes (only in SELLER_MODE)
        void addingByOwnerNewNote();
        void removeByOwnerNote();


    };
}


#endif //MACHINEOFSTATE_NOTEPADMANAGER_H
