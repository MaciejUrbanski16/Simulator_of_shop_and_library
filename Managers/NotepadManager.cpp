//
// Created by Admin on 13.08.2020.
//

#include "NotepadManager.h"
#include "../WriteCsvTsv.h"
#include "../ReadCsvTsv.h"

using namespace std;
using namespace shop;
using namespace base;


int NotepadManager::chooseOfDimension()
{
    for(int i=0;i<notepads.size();i++)
    {
        cout<<i+1<<". "<<notepads[i].getFormat()<<endl;
    }
    cout<<"Podaj cyfre 1-"<<notepads.size()<< ", aby wybrac rozmiar zeszytu"<<endl;
    cout<<"------------------"<<endl;


    bool good,bad;

    do{
        cin>>choose;
        good = cin.good();
        bad = cin.bad();
        cin.clear();
        cin.sync();
    }while(((choose<=0 )||choose>notepads.size()) || (good==0||bad==1));

    return choose;
}

int NotepadManager :: chooseOfColor()
{
    int choose = 0;

    cout<<"Kolory okladek"<<endl;
    cout<<"--------------"<<endl;
    cout<<"1.Czerwona"<<endl;
    cout<<"2.Niebieska"<<endl;
    cout<<"3.Zolta"<<endl;


    cin>>choose;
    if(choose==1||choose==2||choose==3)
    {
        return choose;
    }
    else return 0;
}

void NotepadManager::saveItemsToFile()
{

    std::vector<std::string>headerOfNotes = {"SIZE","PRICE","AMOUNT","AMOUNT_OF_CARDS"};
    std::vector<std::string>dataToTsv;
    std::string readyData;

    WriteCsvTsv writeNotes("notes.tsv");
    writeNotes.addHeader(headerOfNotes);


    for(int i=0;i<notepads.size();i++)
    {
        //save actual state of notes to file with .tsv extension
        dataToTsv.push_back(notepads[i].getFormat());

        readyData = to_string(notepads[i].getPrice());
        dataToTsv.push_back(readyData);

        readyData = to_string(amounts[i]);
        dataToTsv.push_back(readyData);

        readyData = to_string(notepads[i].getNumberOfCards());
        dataToTsv.push_back(readyData);

        writeNotes.writeToFile(dataToTsv);
        dataToTsv.clear();

    }

}


void NotepadManager::readItemsFromFile()
{

    notepads.clear();
    amounts.clear();


    ReadCsvTsv readNotes("notes.tsv");
    readNotes.readFromFile(notepads,amounts);

}

bool NotepadManager::checkIfNoteIsAvailable(int noteChoose)
{
    return amounts[noteChoose-1]>0;                      //return true if there is available any notepad of given format
}

///--------------------------------------------------------------------------------------------------------------------

void NotepadManager :: addNotesToShop(int mode, int howMuch, int where)
{
    if(mode == CLIENT_MODE)
    {
        cout<<"CLIENT_MODE do not allow to edit state of shop "<<endl;
    }
    else if(mode == SELLER_MODE)
    {
        amounts[where-1] = amounts[where-1] + howMuch;
    }
}
void NotepadManager ::showResourcesOfNotes()
{
    cout<<"The notepads that are available: "<<endl;
    for(int i = 0;i<notepads.size();i++)
    {
        cout<<i+1<<". "<<notepads[i].getFormat()<<endl;
    }

}

void NotepadManager ::addingByOwnerNewNote()
{
    if(application_.mode == SELLER_MODE)
    {
        int howMuch = 0, where =-1;
        showResourcesOfNotes();

        cout<<"Choose note from list and give amount to change its amount "<<endl;

        where = enteringTheNumber(1,notepads.size());

        howMuch = enteringTheNumber(0,10000);

        addNotesToShop(application_.mode,howMuch,where);
    }
    else if(application_.mode == CLIENT_MODE)
    {
        cout<<"There is not allowed to edit state of shop in CLIENT_MODE "<<endl;
        cout<<"If you want you can now change mode to SELLER_MODE"<<endl;

        changeModeToSellerMode("password",application_.mode);

    }

}


void NotepadManager::editionStateOfNotes()
{
    cout<<"1. Add notes to shop "<<endl;
    cout<<"2. Remove note from shop "<<endl;

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

void NotepadManager::removeByOwnerNote()
{
    showResourcesOfNotes();
    int choose = enteringTheNumber(1, dimensions.size());
    std::string removedN = notepads[choose -1].getFormat();

    notepads.erase(notepads.begin() + choose - 1);
    amounts.erase(amounts.begin() + choose - 1 );

    cout<<"The notepad with "<< removedN <<"size was removed successfully!" <<endl;

}

std::vector<std::string> NotepadManager::getFormats() {
    std::vector<std::string> formats;
    for(const auto & n : notepads)
    {
        formats.push_back(n.getFormat());
    }
    return formats;
}
