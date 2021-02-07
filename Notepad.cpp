//
// Created by Admin on 13.08.2020.
//

#include "Notepad.h"
#include "WriteCsvTsv.h"
#include "ReadCsvTsv.h"

using namespace std;
using namespace shop;

void Notepad :: setDimensionsOfNote()
{
    //dim = {"A3","A4","A5","B3","B4","B5","B6"};
    //dimensions.push_back("A3");
    //dimensions.push_back("A4");
   // dimensions.push_back("A5");
   // dimensions.push_back("B2");
   // dimensions.push_back("B3");
   // dimensions.push_back("B4");
   // dimensions.push_back("B5");
   // dimensions.push_back("B6");


    //cin>>dim;
    //dimensions.push_back(dim);

}

int Notepad::chooseOfDimension()
{
    for(int i=0;i<dimensions.size();i++)
    {
        cout<<i+1<<". "<<dimensions[i]<<endl;
    }
    cout<<"Podaj cyfre 1-"<<dimensions.size()<< ", aby wybrac rozmiar zeszytu"<<endl;
    cout<<"------------------"<<endl;


    bool good,bad;

    do{
        cin>>choose;
        good = cin.good();
        bad = cin.bad();
        cin.clear();
        cin.sync();
    }while(((choose<=0 )||choose>dimensions.size()) || (good==0||bad==1));

    return choose;
}

int Notepad :: chooseOfColor()
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

void Notepad::saveItemsToFile()
{

    std::vector<std::string>headerOfNotes = {"ROZMIAR","ILOŚC","CENA"};
    std::vector<std::string>dataToTsv;
    std::string readyData;

    WriteCsvTsv writeNotes("notes.tsv");
    writeNotes.addHeader(headerOfNotes);


    for(int i=0;i<dimensions.size();i++)
    {
        //zapisanie aktualnego stanu zeszytow w vectorach do pliku tsv
        dataToTsv.push_back(dimensions[i]);

        readyData = to_string(amount[i]);
        dataToTsv.push_back(readyData);

        readyData = to_string(price[i]);
        dataToTsv.push_back(readyData);

        writeNotes.writeToFile(dataToTsv);
        dataToTsv.clear();

    }

}


void Notepad::readItemsFromFile()
{
    dimensions.clear();
    price.clear();
    amount.clear();


    ReadCsvTsv readNotes("notes.tsv");
    readNotes.readFromFile(dimensions,amount,price);

}

bool Notepad::checkIfNoteIsAvailable(int noteChoose)
{
    return amount[noteChoose-1]>0;                      //zwraca prawde gdy jest jescze dostepny jakikolwiek zeszyt o podanym rozmiarze
}

void Notepad::returnNoteFromBasketToShop(std::vector<std::string> removedThings, std::vector<std::string> dimensions, std::vector<int>amount)
{
    for(int i=0;i<removedThings.size();i++)
    {
        for(int j=0;j<dimensions.size();j++)
        {
            if(removedThings[i] == dimensions[j])
            {
                removedThings.erase(removedThings.begin() + i);
                amount[j]++;
            }
        }
    }
}

///--------------------------------------------------------------------------------------------------------------------

void Notepad :: addNotesToShop(int mode, int howMuch,int where)
{
    if(mode == CUSTOMER_MODE)
    {
        cout<<"W trybie klienta nie mozna modyfikowac zasobow sklepu "<<endl;
    }
    else if(mode == SELLER_MODE)
    {
        amount[where-1] = amount[where-1] + howMuch;
    }
}
void Notepad ::showResourcesOfNotes()
{
    for(int i = 0;i<dimensions.size();i++)
    {
        cout<<i+1<<". "<<dimensions[i]<<endl;
    }

}

void Notepad ::addingByOwnerNewNote()
{
    if(mode == SELLER_MODE)
    {
        int howMuch = 0, where =-1;
        showResourcesOfNotes();
        cout<<"Wybierz numer z listy ktorego ilosc chcesz modyfikowac i wpisz o ile zmenic ilosc: "<<endl;
        where = enteringTheNumber(1,dimensions.size());
        //cin>>howMuch;
        howMuch = enteringTheNumber(0,10000);

        addNotesToShop(mode,howMuch,where);
    }
    else if(mode == CUSTOMER_MODE)
    {
        cout<<"W trybie klienta nie mozna modyfikowac zasobow sklepu "<<endl;
        cout<<"Jesli chcesz mozesz zmienic teraz tryb z trybu CUSTOMER_MODE na tryb SELLER_MODE"<<endl;
        changeModeToSellerMode("12trempki",mode);
        //presentationOfServices();
    }

}

void Notepad::addThingFromRemovedToShop(std::map<std::string, int> mapa) {
    mapa["4"] = 1;
    //string d = mapa.key_comp();

}

vector<int>
Notepad::incrementAmountofRemovedThing(std::map<std::string, int> incrementAmountOfNotesAfterRemovingFromBaskte) {
    return std::vector<int>();
}

vector<int>
Notepad::incrementAmountOfNotesAfterReturnedToShop(Application &app) {
     for(int i=0;i<app.removedThings.size();i++) //co to jest??? czemu nie daje rady tego oddzielic do osobnej funkcji??
 {
     for(int j=0;j<dimensions.size();j++)
     {
         if(app.removedThings[i] == dimensions[j])
         {
             //removedThings.erase(removedThings.begin() + i);
             amount[j]++;
         }
     }
 }
     return amount;
}

void Notepad::editionStateOfNotes()
{
    cout<<"1. Dodaj zeszyt do sklepu "<<endl;
    cout<<"2. Usun zeszyt ze sklepu "<<endl;
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

void Notepad::removeByOwnerNote()
{
    showResourcesOfNotes();
    int choose = enteringTheNumber(1, dimensions.size());
    std::string removedN = dimensions[choose -1];

    dimensions.erase(dimensions.begin() + choose - 1);
    price.erase(price.begin() + choose - 1 );
    amount.erase(amount.begin() + choose - 1 );

    cout<<"Pomyslnie usunieto ze sklepu zeszyt o wymiarze: "<< removedN <<endl;

}
