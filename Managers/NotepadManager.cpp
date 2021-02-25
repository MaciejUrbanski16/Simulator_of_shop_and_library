//
// Created by Admin on 13.08.2020.
//

#include "NotepadManager.h"
#include "../WriteCsvTsv.h"
#include "../ReadCsvTsv.h"






int shop::NotepadManager::chooseOfDimension()
{
    for(int i=0;i<notepads.size();i++)
    {
        std::cout<<i+1<<". "<<notepads[i].getFormat()<<std::endl;
    }
    std::cout<<"Podaj cyfre 1-"<<notepads.size()<< ", aby wybrac rozmiar zeszytu"<<std::endl;
    std::cout<<"------------------"<<std::endl;


    bool good,bad;

    do{
        std::cin>>choose;
        good = std::cin.good();
        bad = std::cin.bad();
        std::cin.clear();
        std::cin.sync();
    }while(((choose<=0 )||choose>notepads.size()) || (good==0||bad==1));

    return choose;
}

int shop::NotepadManager :: chooseOfColor()
{
    int choose = 0;

    std::cout<<"Kolory okladek"<<std::endl;
    std::cout<<"--------------"<<std::endl;
    std::cout<<"1.Czerwona"<<std::endl;
    std::cout<<"2.Niebieska"<<std::endl;
    std:: cout<<"3.Zolta"<<std::endl;


    std::cin>>choose;
    if(choose==1||choose==2||choose==3)
    {
        return choose;
    }
    else return 0;
}

void shop::NotepadManager::saveItemsToFile()
{

    std::vector<std::string>headerOfNotes = {"SIZE","PRICE","AMOUNT","AMOUNT_OF_CARDS"};
    std::vector<std::string>dataToTsv;
    std::string readyData;

    base::WriteCsvTsv writeNotes("notes.tsv");
    writeNotes.addHeader(headerOfNotes);


    for(int i=0;i<notepads.size();i++)
    {
        //save actual state of notes to file with .tsv extension
        dataToTsv.push_back(notepads[i].getFormat());

        readyData = std::to_string(notepads[i].getPrice());
        dataToTsv.push_back(readyData);

        readyData = std::to_string(amounts[i]);
        dataToTsv.push_back(readyData);

        readyData = std::to_string(notepads[i].getNumberOfCards());
        dataToTsv.push_back(readyData);

        writeNotes.writeToFile(dataToTsv);
        dataToTsv.clear();

    }

}


void shop::NotepadManager::readItemsFromFile()
{

    notepads.clear();
    amounts.clear();


    base::ReadCsvTsv readNotes("notes.tsv");
    readNotes.readFromFile(notepads,amounts);

}

bool shop::NotepadManager::checkIfNoteIsAvailable(int noteChoose)
{
    return amounts[noteChoose-1]>0;                      //return true if there is available any notepad of given format
}

///--------------------------------------------------------------------------------------------------------------------

void shop::NotepadManager :: addNotesToShop(int mode, int howMuch, int where)
{
    if(mode == CLIENT_MODE)
    {
        std::cout<<"CLIENT_MODE do not allow to edit state of shop "<<std::endl;
    }
    else if(mode == SELLER_MODE)
    {
        amounts[where-1] = amounts[where-1] + howMuch;
    }
}
void shop::NotepadManager ::showResourcesOfNotes()
{
    std::cout<<"The notepads that are available: "<<std::endl;
    for(int i = 0;i<notepads.size();i++)
    {
        std::cout<<i+1<<". "<<notepads[i].getFormat()<<std::endl;
    }

}

void shop::NotepadManager ::addingByOwnerNewNote()
{
    if(application_.mode == SELLER_MODE)
    {
        int howMuch = 0, where =-1;
        showResourcesOfNotes();

        std::cout<<"Choose note from list and give amount to change its amount "<<std::endl;

        where = enteringTheNumber(1,notepads.size());

        howMuch = enteringTheNumber(0,10000);

        addNotesToShop(application_.mode,howMuch,where);
    }
    else if(application_.mode == CLIENT_MODE)
    {
        std::cout<<"There is not allowed to edit state of shop in CLIENT_MODE "<<std::endl;
        std::cout<<"If you want you can now change mode to SELLER_MODE"<<std::endl;

        changeModeToSellerMode("password",application_.mode);

    }

}


void shop::NotepadManager::editionStateOfNotes()
{
    std::cout<<"1. Add notes to shop "<<std::endl;
    std::cout<<"2. Remove note from shop "<<std::endl;

    int choose = enteringTheNumber(1,2);

    switch(choose)
    {
        case 1:
            addingByOwnerNewNote();
            break;

        case 2:
            removeByOwnerNote();
            break;

        default:
            break;
    }
}

void shop::NotepadManager::removeByOwnerNote()
{
    showResourcesOfNotes();
    int choose = enteringTheNumber(1, dimensions.size());
    std::string removedN = notepads[choose -1].getFormat();

    notepads.erase(notepads.begin() + choose - 1);
    amounts.erase(amounts.begin() + choose - 1 );

    std::cout<<"The notepad with "<< removedN <<"size was removed successfully!" <<std::endl;

}

std::vector<std::string> shop::NotepadManager::getFormats() {
    std::vector<std::string> formats;
    for(const auto & n : notepads)
    {
        formats.push_back(n.getFormat());
    }
    return formats;
}
