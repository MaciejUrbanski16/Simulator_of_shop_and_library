//
// Created by Admin on 12.09.2020.
//

#include "BagpackManager.h"

#include <utility>



shop::BagpackManager::BagpackManager(std::string mark, std::string color, shop::towar_t price, int amount)
: mark(std::move(mark)),
  color(std::move(color)),
  price(price),
  amount(amount){}

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
    std::string m = "Olg";
    bagsFromFile[0].setMark(m);
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

        //dodanie do vectora plecakow kolejnego obiektu powstałego z odczytanych danych z pliku
        bags.emplace_back(strToMark, strToColour, pr, am);

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

void shop::BagpackManager::chooseBag(Ware &purchases)
{
    std::cout<<"Wybierz sposrod dostepnych plecakow "<<std::endl;
    int chooseB = enteringTheNumber(1, bags.size());

    if(amountsOfBags[chooseB - 1] <= 0)
    {
        std::cout << "Brak plecakow marki " << bagsFromFile[chooseB - 1].getMark() << std::endl;
    }
    else
    {
        amountsOfBags[chooseB - 1]--;

        purchases.name = bagsFromFile[chooseB - 1].getMark();
        purchases.praise = bagsFromFile[chooseB - 1].getPrice();


        purchases.addToPurchases();
    }

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

void  shop::BagpackManager::getAmounts()
{

}

void shop::BagpackManager::refreshObjectsAfterRemoving(std::vector<shop::BagpackManager> &bags) {

    for(int i=0;i<allMarks.size();i++)
    {
        bags[i].amount = allAmounts[i];

        amountsOfBags[i] = allAmounts[i];
    }

}

void shop::BagpackManager::editionStateOfBags()
{
    std::cout<<"1. Dodanie/ 2.Usuniecie"<<std::endl;

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
    std::cout<<"Podaj kolejno marke, kolor, cene, ilosc"<<std::endl;
    std::string addMark, addColor;
    shop::towar_t addPrice;
    int addAmount;

    std::cin>>addMark>>addColor>>addPrice>>addAmount;
    bags.emplace_back(addMark, addColor, addPrice, addAmount);

}

void shop::BagpackManager::removeBags()
{
    presentationOfBags();
    int chooseRemove = enteringTheNumber(1, bags.size());
    bags.erase(bags.begin() + chooseRemove);

}







