//
// Created by Admin on 06.08.2020.
//

#include "Book.h"

#include <iostream>

using namespace shop;
using  namespace std;


void Ware::readItemsFromFile()
{

}

void Ware::saveItemsToFile()
{

}

bool Ware::enterToShop()
{
    bool pushButton;
    cout<<"Jesli chcesz wejsc do sklepu wcisnij znak 'y'"<<endl;
    char goShop;
    cin>>goShop;

    pushButton = goShop == 'Y' || goShop == 'y';
    return pushButton;
}

int Ware::changeModeToSellerMode(std::string password, int mode)
{
    std::string givenPassword;
    int attemp = 3;
    if (!(mode == SELLER_MODE)) {
        if (mode == CUSTOMER_MODE) {
            cout << "Aby przejsc do trybu sprzedawcy nalezy podac haslo, wprowadz je: " << endl;
            cin >> givenPassword;


            for (int i = 0; i < 3; i++) {
                if (password == givenPassword && attemp > 0) {
                    mode = SELLER_MODE;
                    attemp = 3;
                    this->inSellerMode = true;
                    cout << "Pomyslnie zmieniono tryb, teraz mozna edytowac zasoby sklepu" << endl;
                    break;
                }
                else {
                    attemp--;
                    cout << "Podano nieprawidlowe haslo. Pozostalo prob: " << attemp << endl;
                    cin >> givenPassword;
                }
            }
        }
    }
    else {
        mode = CUSTOMER_MODE;
        cout << "Zmieniono tryb na tryb klienta" << endl;

    }
    return  mode;
}



int Ware ::choosingFromList(int minRange, int maxRange)
{
    int choose1 = -1;
        cout<<"Podaj cyfre "<<minRange<<"-"<<maxRange<<" aby wybrac usługe"<<endl;
        cout<<"------------------"<<endl;



        bool good1,bad1;

        do{
            cin>>choose1;
            good1 = cin.good();
            bad1 = cin.bad();
            cin.clear();
            cin.sync();
        }while((choose1<minRange&&choose1>maxRange)||(good1==0||bad1==1));


    return choose1;
}

int Ware :: enteringTheNumber(int minValue, int maxValue)
{
    int where = -1;

#ifndef TESTING
    bool good1,bad1;

    do{
        cin>>where;
        good1 = cin.good();
        bad1 = cin.bad();
        cin.clear();
        cin.sync();
    }while((where<minValue||where>maxValue)||(good1==0||bad1==1));
    //cin>>howMuch;
#else
    where = 4;
#endif
    return where;
}

std::string Ware::removeThingFromPurchases()
{
    showOrderedPurchases();
    int choose=-1;

    if(!orderedPurchasesName.empty())
    {
        cout<<"Wybierz nr rzeczy ktora chcesz wyjac z koszyka zpowrotem do sklepu: "<<endl;

        choose = enteringTheNumber(1,orderedPurchasesName.size());

        choose--; //aby dostosowac sie do iteracji vectora od 0

        std::string removedName = orderedPurchasesName[choose];
        towar_t removedPrice = orderedPurchasesPrice[choose];

        orderedPurchasesName.erase(orderedPurchasesName.begin() + choose);
        orderedPurchasesPrice.erase(orderedPurchasesPrice.begin() + choose);

        cout<<"Pomyslnie usunieto: "<<removedName<<" w cenie "<<removedPrice<<endl;

        showOrderedPurchases();
        return removedName;
    }
    else
        {
        cout<<"Nie ma nic do usuniecia!!!"<<endl;
        return "";
    }
}

void Ware :: addToPurchases()
{

    orderedPurchasesName.push_back(name);
    orderedPurchasesPrice.push_back(praise);

    cout<<"Pomyslnie dodano "<<name<<" do koszyka, w cenie "<<praise<<endl;
}

void Ware::showOrderedPurchases()
{
    cout<<"Aktualny stan koszyka to: "<<endl;

    for(int i =0;i<orderedPurchasesName.size();i++)
    {
        cout<<i+1<<". Nazwa: "<<orderedPurchasesName[i]<<" w cenie: "<<orderedPurchasesPrice[i]<<endl;

    }
}


towar_t Ware::roundFloatToSecond(towar_t d)
{

    int y = d * 1000; // przesuwamy przecinek o 4 miejsca i pozbywamy sie reszty za przecinkiem - y jest calkowite

    return (y / 10) * 0.01; // usuwamy ostatnia cyfre i zamieniamy na liczbe zmiennoprzecinkowa
}

void  Ware::remove(std::vector<std::string> &removedThings, std::vector<std::string> &dimensions, std::vector<int>& _amount)
{
    for(int i=0;i<removedThings.size();i++)
    {
        for(int j=0;j<dimensions.size();j++)
        {
            if(removedThings[i] == dimensions[j])
            {
                if(!removedThings.empty())
                {
                    removedThings.erase(removedThings.begin() + i);
                    _amount[j]++;
                }

            }
        }
    }

}

char Ware::enterTheLetter() {
    char letter = 'c';
    while(!_kbhit())
    {
        letter = getch();                //wyszukiwanie ksiazek po wcisnietym znaku
    }
    return letter;
}

