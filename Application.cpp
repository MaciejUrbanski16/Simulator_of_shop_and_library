//
// Created by Admin on 04.01.2021.
//

#include "Application.h"
#include "ShopWare.h"
#include "tests.h"

bool Application::enterToShop()
{
    bool pushButton;
    cout<<"If you want to go into shop press 'y', or if you want to go into librbary press 'g'(give back book) or 'b'(borrow book)"<<endl;

    cin >> enteredChar;

    if(enteredChar == 'y') {
        pushButton = enteredChar == 'Y' || enteredChar == 'y';
        return pushButton;
    }
    else if(enteredChar == 'b'){
        pushButton = enteredChar == 'B' || enteredChar == 'b';
        return pushButton;
    }
    else if(enteredChar == 'g'){
        pushButton = enteredChar == 'G' || enteredChar == 'g';
        return pushButton;
    }
    return false;
}

void Application :: presentationOfServices()
{

    if(mode == CLIENT_MODE)
    {
        std::cout<<"MOZLIWY WYBOR USLUG: "<<std::endl;
        std::cout<<"---------------------"<<std::endl;
        std::cout<<"1. Ksiazki"<<std::endl;
        std::cout<<"2. Zeszyty"<<std::endl;
        std::cout<<"3. Tornistry"<<std::endl;
        std::cout<<"4. Przybory"<<std::endl;
        std::cout<<"5. USUNIECIE PRZEDMIOTU Z KOSZYKA"<<std::endl;
        std::cout<<"6. ZMIANA TRYBU - Obecny tryb CLIENT_MODE "<<std::endl;
        std::cout<<"7. Wyjscie"<<std::endl;
        std::cout<<"---------------------"<<std::endl;
        std::cout<<std::endl;

    }
    else if(mode == SELLER_MODE)
    {
        std::cout<<"1. Edycja ksiazek"<<std::endl;
        std::cout<<"2. Edycja zeszytow"<<std::endl;
        std::cout<<"3. Edycja tornistrow"<<std::endl;
        std::cout<<"4. Edycja przyborow"<<std::endl;
        std::cout<<"5. ZMIANA TRYBU - Obecny tryb SELLER_MODE "<<std::endl;
    }
}

void Application::saveRemovedToFile()
{

    std::fstream fileToSaveTitle("removedFromBasket.txt",std::ios::out);

    for(int i=0;i<removedThings.size();i++)
    {
        if(i+1==removedThings.size())
        {
            fileToSaveTitle << removedThings[i];
        }
        else
        {
            fileToSaveTitle << removedThings[i]<<std::endl;
        }
    }

}

void Application::readRemovedFromFile()
{
    removedThings.clear();

    std::fstream f;
    f.open("removedFromBasket.txt");
    std::string str;

    while(getline(f,str))
    {
        removedThings.push_back(str);
    }

    f.close();
}

int Application :: chooseOfService()
{
    int choose = 0;
    if(mode == CLIENT_MODE)
    {
        choose = enteringTheNumber(1,7);
    }

    else if(mode == SELLER_MODE)
    {
        choose  = enteringTheNumber(1,5);
    }
    return choose;
}

void Application::setKindOfService() {
    if(enterToShop())
    {
        stage = INTRODUCTION;
        if(enteredChar == 'y'){
            kindOfService_ = static_cast<int>(Application::kindOfService::SHOP);
        }
        else if(enteredChar == 'b'){
            kindOfService_ = static_cast<int>(Application::kindOfService::LIBRARY_BORROW);
        }
        else if (enteredChar == 'g'){
            kindOfService_ = static_cast<int>(Application::kindOfService::LIBRARY_GIVE_BACK);
        }
    }
    else{
        cout<<"Invalid input: "<<endl;
        exit(0);
    }
}
