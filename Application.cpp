//
// Created by Admin on 04.01.2021.
//

#include "Application.h"
#include "ShopWare.h"


bool Application::enterToShop()
{
    bool pushButton;
    std::cout<<"If you want to go into shop press 'y', or if you want to go into librbary press 'g'(give back book) or 'b'(borrow book)"<<std::endl;

    std::cin >> enteredChar;

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
        std::cout<<"AVAILABLE TO CHOOSE: "<<std::endl;
        std::cout<<"---------------------"<<std::endl;
        std::cout<<"1. Books"<<std::endl;
        std::cout<<"2. Notepads"<<std::endl;
        std::cout<<"3. Bagpacks"<<std::endl;
        std::cout<<"4. School supplies"<<std::endl;
        std::cout<<"5. REMOVE ITEM FROM BASKET"<<std::endl;
        std::cout<<"6. CHANGE MODE - current mode: CLIENT_MODE "<<std::endl;
        std::cout<<"7. Exit"<<std::endl;
        std::cout<<"---------------------"<<std::endl;
        std::cout<<std::endl;

    }
    else if(mode == SELLER_MODE)
    {
        std::cout<<"1. Edition of books"<<std::endl;
        std::cout<<"2. Eition of notes"<<std::endl;
        std::cout<<"3. Edition of backpacks"<<std::endl;
        std::cout<<"4. Edition of school supplies"<<std::endl;
        std::cout<<"5. CHANGE MODE - current mode: SELLER_MODE "<<std::endl;
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
        std::cout<<"Invalid input: "<<std::endl;
        exit(0);
    }
}

int Application::enteringTheNumber(int minValue, int maxValue) {

        int howMuch = 0;
        if(minValue > maxValue)
        {
            int temp = maxValue;
            minValue = maxValue;
            maxValue = temp;
        }

        int where = -1;

        std::cout<<"Give number in range "<<minValue<<" - "<<maxValue<<" to choose service"<<std::endl;

        where = 4;

        bool good1,bad1;


        do{

            std::cin>>where;

            good1 = std::cin.good();
            bad1 = std::cin.bad();
            std::cin.clear();
            std::cin.sync();
        }while((where<minValue||where>maxValue)||(good1==0||bad1==1));

        return where;

}
