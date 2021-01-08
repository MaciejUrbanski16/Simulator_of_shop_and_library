//
// Created by Admin on 13.08.2020.
//

#ifndef MACHINEOFSTATE_NOTEPAD_H
#define MACHINEOFSTATE_NOTEPAD_H

#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
//#include "accesories.h"
#include "Book.h"
#include "Application.h"
//#include <map>



namespace shop
{
    class Notepad : public shop::Ware
    {
    public:
        std::string color;
        //std::vector<std::string> dimension;
        std::vector<std::string>dimensions;
        std::vector<float>price;
        std::vector<int>amount;
        bool noteWithLines;
        int chooseOfColor();
        int chooseOfDimension();


        void setDimensionsOfNote();  //dostepne rozmiary zesytow

        bool checkIfNoteIsAvailable(int);

        void saveItemsToFile() override;
        void readItemsFromFile();

        std::vector<Notepad> bookedNotes;

        void returnNoteFromBasketToShop(std::vector<std::string> removedThings, std::vector<std::string> dimensions, std::vector<int>amount);



        void addThingFromRemovedToShop(std::map<std::string, int> map);

        std::vector<int>
        incrementAmountofRemovedThing(std::map<std::string, int> incrementAmountOfNotesAfterRemovingFromBaskte);

        std::vector<int>incrementAmountOfNotesAfterReturnedToShop(Application &app);

        void editionStateOfNotes();

    private:
        std::string dim;
        int choose;
        int dimensionsSize; //ilosc elementow vectora dimension

        std::fstream readDimensions;
        std::fstream readAmount;
        std::fstream readPrice;

        void addNotesToShop(int mode, int howMuch,int where);
        void showResourcesOfNotes();

        std::string dimen,pr,am;
        //float pr;
        //int am;

        void addingByOwnerNewNote();
        void removeByOwnerNote();


    };
}


#endif //MACHINEOFSTATE_NOTEPAD_H
