//
// Created by Admin on 26.07.2020.
//
//#include "accesories.h"
#include "Book.h"
//#include "accesories.h"

//#include "accesories.h"

//#include "accesories.h"

#include <iostream>

using namespace shop;
using  namespace std;


void Towar::readItemsFromFile()
{

}

void Towar::saveItemsToFile()
{

}

bool Towar::enterToShop()
{
    bool pushButton;
    cout<<"Jesli chcesz wejsc do sklepu wcisnij znak 'y'"<<endl;
    char goShop;
    cin>>goShop;

    pushButton = goShop == 'Y' || goShop == 'y';
    return pushButton;
}

int Towar::changeModeToSellerMode( std::string password,int mode)
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
        //return mode;
    }
    return  mode;
}

void Towar :: presentationOfServices()
{

    if(mode == CUSTOMER_MODE)
    {
        cout<<"1. Ksiazki"<<endl;
        cout<<"2. Zeszyty"<<endl;
        cout<<"3. Tornistry"<<endl;
        cout<<"4. Przybory"<<endl;
        cout<<"5. USUNIECIE PRZEDMIOTU Z KOSZYKA"<<endl;
        cout<<"6. ZMIANA TRYBU - Obecny tryb CUSTOMER_MODE "<<endl;
        cout<<"7. Wyjscie"<<endl;
        //cout<<"8. USUNIECIE PRZEDMIOTU Z KOSZYKA"<<endl;
        //cout<<"9. ZMIANA TRYBU - Obecny tryb CUSTOMER_MODE "<<endl;
        //cout<<"10. Wyjscie"<<endl;
    }
    else if(mode == SELLER_MODE)
    {
        cout<<"1. Edycja ksiazek"<<endl;
        cout<<"2. Edycja zeszytow"<<endl;
        cout<<"3. Edycja tornistrow"<<endl;
        cout<<"4. Edycja przyborow"<<endl;
        cout<<"5. ZMIANA TRYBU - Obecny tryb SELLER_MODE "<<endl;
        //cout<<"6. Edycja przyborow"<<endl;
        //cout<<"7. ZMIANA TRYBU - Obecny tryb SELLER_MODE "<<endl;
    }
}

int Towar :: chooseOfService()
{
    int choose = 0;
    if(mode == CUSTOMER_MODE)
    {
        cout<<"Podaj cyfre 1-7, aby wybrac usługe"<<endl;
        cout<<"------------------"<<endl;


        choose = enteringTheNumber(1,7);
    }

    else if(mode == SELLER_MODE)
    {
        cout<<"Podaj cyfre 1-5 aby wybrac usługe"<<endl;
        cout<<"------------------"<<endl;

        choose  = enteringTheNumber(1,5);

    }
    return choose;
}

int Towar ::choosingFromList(int minRange, int maxRange)
{
    int choose1 = -1;
        cout<<"Podaj cyfre 1-3 aby wybrac usługe"<<endl;
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

int Towar :: enteringTheNumber(int minValue, int maxValue)
{
    //int howMuch = 0;

    int where = -1;
    //cout<<"Podaj cyfre z zakresu od "<<minValue<<" do"<<maxValue<<endl;

    bool good1,bad1;

    do{
        cin>>where;
        good1 = cin.good();
        bad1 = cin.bad();
        cin.clear();
        cin.sync();
    }while((where<minValue||where>maxValue)||(good1==0||bad1==1));
    //cin>>howMuch;
    return where;
}

std::string Towar::removeThingFromPurchases()
{
    showOrderedPurchases();
    int choose=-1;
    bool good, bad;
    if(!orderedPurchasesName.empty())
    {
        cout<<"Wybierz nr rzeczy ktora chcesz wyjac z koszyka zpowrotem do sklepu: "<<endl;

        choose = enteringTheNumber(1,orderedPurchasesName.size());

        choose--; //aby dostosowac sie do iteracji vectora od 0

        std::string removedName = orderedPurchasesName[choose];
        towar_int_t removedPrice = orderedPurchasesPrice[choose];

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

void Towar :: addToPurchases()
{

    orderedPurchasesName.push_back(name);
    orderedPurchasesPrice.push_back(praise);

    cout<<"Pomyslnie dodano "<<name<<" do koszyka, w cenie "<<praise<<endl;
}

void Towar::showOrderedPurchases()
{
    for(int i =0;i<orderedPurchasesName.size();i++)
    {
        cout<<i+1<<". Nazwa: "<<orderedPurchasesName[i]<<" w cenie: "<<orderedPurchasesPrice[i]<<endl;

    }
}

Towar::Towar(std::vector<shop::Towar>::iterator iterator) {
    iterator.base();
}

void Towar::saveRemovedToFile()
{

    fstream fileToSaveTitle("removedFromBasket.txt",ios::out);

    for(int i=0;i<removedThings.size();i++)
    {
        if(i+1==removedThings.size())
        {
            fileToSaveTitle << removedThings[i];
        }
        else
        {
            fileToSaveTitle << removedThings[i]<<endl;
        }
    }

}

void Towar::readRemoveFromFile()
{
        removedThings.clear();
        fstream f;
        f.open("removedFromBasket.txt");
        std::string str;

        while(getline(f,str))
        {
            removedThings.push_back(str);
        }

        f.close();
}

towar_int_t Towar::roundFloatToSecond(towar_int_t d)
{

    int y = d * 1000; // przesuwamy przecinek o 4 miejsca i pozbywamy sie reszty za przecinkiem - y jest calkowite
    //if (y % 10 >= 5)
    {
     //   y += 10; // jezeli cyfra jednosci >= 5
    }
    return (y / 10) * 0.01; // usuwamy ostatnia cyfre i zamieniamy na liczbe zmiennoprzecinkowa

}

void  Towar::remove(std::vector<std::string> &removedThings, std::vector<std::string> &dimensions,std::vector<int>&amount)
{
    //std::map<std::string, int> pairOfRemovedThingAndPosition;
    for(int i=0;i<removedThings.size();i++)
    {
        for(int j=0;j<dimensions.size();j++)
        {
            if(removedThings[i] == dimensions[j])
            {
                if(!removedThings.empty())
                {
                    removedThings.erase(removedThings.begin() + i);
                    amount[j]++;
                    //pairOfRemovedThingAndPosition[removedThings[i]] = j;
                }

            }
        }
    }

}



/*template<typename Type>
void Towar::removeThing(Type *obj) {
    int choose;
}

template<typename Type>
void Towar::removeThing(Type *obj, vector<Type> &things) {
    int choose = enteringTheNumber(1, things.size());
    things.erase(things.begin() + choose -1);
}*/

/*template<class type>
void Towar::remove<type>(type el) {
    //type el;
    el->titleOfBooksInShop;

}*/


