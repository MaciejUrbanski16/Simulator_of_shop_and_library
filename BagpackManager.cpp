//
// Created by Admin on 12.09.2020.
//

#include "BagpackManager.h"

#include <utility>

shop::BagpackManager::~BagpackManager() {
    //delete b;
}

void shop::BagpackManager::readItemsFromFile()
{
    this->listOfBagpacks.clear();
    this->bags.clear();
    this->bagsFromFile.clear();
    std::fstream readDateFromFile;
    readDateFromFile.open("bags.txt");


    while(getline(readDateFromFile,line))
    {
        prepareStrings(line);
    }

    readDateFromFile.close();
}

void shop::BagpackManager::saveItemsToFile()
{
    std::fstream fileToSaveBags("bags.txt",std::ios::out);
    for(int i=0; i < bagsFromFile.size(); i++)
    {
        if(i+1 == bagsFromFile.size())
        {
            fileToSaveBags << bagsFromFile[i].getPrice() << " " << bagsFromFile[i].getColor() << " "
            << amountsOfBags[i] << " " << bagsFromFile[i].getMark() << " " << '_';
        }
        else
            {
            fileToSaveBags << bagsFromFile[i].getPrice() << " " << bagsFromFile[i].getColor() << " "
            << amountsOfBags[i] << " " << bagsFromFile[i].getMark() << " " << 'k' << std::endl;
        }

    }
}

void shop::BagpackManager::prepareStrings(std::string basicString)
{

    for(int i=0;i<basicString.length()-1;i++)
    {

        while(basicString[i] != ' ')
        {
            strToPrice = strToPrice + basicString[i];
            i++;
        }
        i++;
        while(basicString[i] != ' ')
        {
            strToColour = strToColour + basicString[i];
            i++;
        }
        i++;
        while(basicString[i] !=' ')
        {
            strToAmount = strToAmount + basicString[i];
            i++;
        }
        i++;
        while(basicString[i] !=' ')
        {
            strToMark+=basicString[i];
            i++;
            std::string r = strToAmount;
        }

        am= atoi(strToAmount.c_str());
        pr = atof(strToPrice.c_str());

        //add prepared objects created from read strings to tables which storage concrete bagpacks and their amounts
        bagsFromFile.emplace_back(strToMark,strToColour,pr);
        amountsOfBags.push_back(am);

        strToAmount = "";
        strToPrice = "";
        strToColour = "";
        strToMark = "";
    }
}

void shop::BagpackManager::presentationOfBags()
{
    int i = 0 ;
    for(const auto& element : bagsFromFile)
    {
        i++;
        std::cout<<i<<". "<<element;
    }

}

void shop::BagpackManager::chooseBagToPurchases(Ware &purchases)
{
#ifndef TESTING
    std::cout<<"Choose bag you want "<<std::endl;
    _chooseBag = enteringTheNumber(1, amountsOfBags.size());

    if(amountsOfBags[_chooseBag - 1] <= 0)
    {
        std::cout << "There is no " << bagsFromFile[_chooseBag - 1].getMark() << "mark"<<std::endl;
    }
    else
    {
        amountsOfBags[_chooseBag - 1]--;

        purchases.name = bagsFromFile[_chooseBag - 1].getMark();
        purchases.praise = bagsFromFile[_chooseBag - 1].getPrice();


        purchases.addToPurchases();
    }
#else
    if(amountsOfBags[_chooseBag - 1] <= 0)
    {
        std::cout << "Brak plecakow marki " << bagsFromFile[_chooseBag - 1].getMark() << std::endl;
    }
    else
    {
        amountsOfBags[_chooseBag - 1]--;

        purchases.name = bagsFromFile[_chooseBag - 1].getMark();
        purchases.praise = bagsFromFile[_chooseBag - 1].getPrice();


        purchases.addToPurchases();
    }
#endif

}

void shop::BagpackManager::getMarks()
{
    std::string _m;

    for(int i=0; i < bagsFromFile.size(); i++)
    {
        _m = bagsFromFile[i].getMark();
        allMarks.push_back(_m);
    }
}


void shop::BagpackManager::editionStateOfBags()
{
    std::cout<<"1. Add bag/ 2.Remove bag"<<std::endl;

    int addRem = enteringTheNumber(1,2);

    switch(addRem)
    {
        case 1:
            addBags();
            break;
        case 2:
            removeBags();
            break;
        default:
            break;
    }
}

void shop::BagpackManager::addBags()
{
    presentationOfBags();
    std::cout<<"Enter mark, color, price, amount of concrete bagpack in this order"<<std::endl;
    std::string addMark, addColor;
    shop::ware_t addPrice;
    int addAmount;

    std::cin>>addMark>>addColor>>addPrice>>addAmount;
    shop::ConcreteBagpack addBag(addMark,addColor,addPrice);
    bagsFromFile.push_back(addBag);
    amountsOfBags.push_back(addAmount);

}

void shop::BagpackManager::removeBags()
{
    presentationOfBags();
    int chooseRemove = enteringTheNumber(1, bags.size());
    bagsFromFile.erase(bagsFromFile.begin() + chooseRemove);
    amountsOfBags.erase(amountsOfBags.begin() + chooseRemove);

}







