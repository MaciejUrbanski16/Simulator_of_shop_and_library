//
// Created by Admin on 04.01.2021.
//

#include "Application.h"
#include "ShopWare.h"
#include "tests.h"

Application *Application::getInstance() {
    if(app == nullptr){
        app = new Application();
    }
    return app;
}

void Application :: presentationOfServices()
{

    if(mode == CUSTOMER_MODE)
    {
        std::cout<<"MOZLIWY WYBOR USLUG: "<<std::endl;
        std::cout<<"---------------------"<<std::endl;
        std::cout<<"1. Ksiazki"<<std::endl;
        std::cout<<"2. Zeszyty"<<std::endl;
        std::cout<<"3. Tornistry"<<std::endl;
        std::cout<<"4. Przybory"<<std::endl;
        std::cout<<"5. USUNIECIE PRZEDMIOTU Z KOSZYKA"<<std::endl;
        std::cout<<"6. ZMIANA TRYBU - Obecny tryb CUSTOMER_MODE "<<std::endl;
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

void Application::readRemoveFromFile()
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
    if(mode == CUSTOMER_MODE)
    {
        choose = enteringTheNumber(1,7);
    }

    else if(mode == SELLER_MODE)
    {
        choose  = enteringTheNumber(1,5);
    }
    return choose;
}
