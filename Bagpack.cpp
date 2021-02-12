//
// Created by Admin on 12.09.2020.
//

#include "Bagpack.h"

#include <utility>



shop::Bagpack::Bagpack(std::string mark, std::string color, shop::towar_int_t price,int amount)
: mark(std::move(mark)),
  color(std::move(color)),
  price(price),
  amount(amount){}

shop::Bagpack::~Bagpack() {

}

void shop::Bagpack::readItemsFromFile()
{
    bags.clear();
    std::fstream readDateFromFile;
    readDateFromFile.open("bags.txt");


    while(getline(readDateFromFile,line))
    {
        prepareStrings(line);
    }

    readDateFromFile.close();
}

void shop::Bagpack::saveItemsToFile()
{
    bags[0].mark = "Olg";
    std::fstream fileToSaveBags("bags.txt",std::ios::out);
    for(int i=0; i < bags.size(); i++)
    {
        if(i+1 == bags.size())
        {
            fileToSaveBags << bags[i].price << " " << bags[i].color << " " << bags[i].amount << " " << bags[i].mark << " " << '_';
        }
        else
            {
            fileToSaveBags << bags[i].price << " " << bags[i].color << " " << bags[i].amount << " " << bags[i].mark << " " << 'k' << std::endl;
        }

    }
}

void shop::Bagpack::prepareStrings(std::string basicString)
{
    //std::string strToMark, strToColour,strToPrice,strToAmount,strTemp;
   // __gnu_cxx::__normal_iterator<const Bagpack *, std::vector<Bagpack>> strToMark;
    for(int i=0;i<basicString.length()-1;i++)
    {
        /*strTemp +=basicString[i];
        if(basicString[i] == ' ')
        {
            strToMark = strTemp;
            strTemp = "";
        }*/
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
        strToAmount = "";
        strToPrice = "";
        strToColour = "";
        strToMark = "";


    }
    //zmienne tymczasowe do konwersji ze stringa na liczbe
    //bags.emplace_back("y","e",1,1);


    int c =0;

}

void shop::Bagpack::presentationOfBags()
{
    for(int i=0; i < bags.size(); i++)
    {
        if(bags[i].amount > 0)
        {
            std::cout <<i+1 << ". " << bags[i].mark << " cena: " << bags[i].price << std::endl;
        }
    }

}

void shop::Bagpack::chooseBag(Ware &purchases)
{
    std::cout<<"Wybierz sposrod dostepnych plecakow "<<std::endl;
    int chooseB = enteringTheNumber(1, bags.size());

    if(bags[chooseB - 1].amount <= 0)
    {
        std::cout << "Brak plecakow marki " << bags[chooseB - 1].mark << std::endl;
    }
    else
    {
        bags[chooseB - 1].amount--;

        purchases.name = bags[chooseB - 1].mark;
        purchases.praise = bags[chooseB - 1].price;


        purchases.addToPurchases();
    }

}

void shop::Bagpack::getMarksAndAmounts()
{

    for(int i=0; i < bags.size(); i++)
    {
        allMarks.push_back(bags[i].mark);
        allAmounts.push_back(bags[i].amount);
    }
}

void  shop::Bagpack::getAmounts()
{

}

void shop::Bagpack::refreshObjectsAfterRemoving(std::vector<shop::Bagpack> &bags) {

    for(int i=0;i<allMarks.size();i++)
    {
        bags[i].amount = allAmounts[i];
    }

}

void shop::Bagpack::editionStateOfBags()
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

void shop::Bagpack::addBags()
{
    presentationOfBags();
    std::cout<<"Podaj kolejno marke, kolor, cene, ilosc"<<std::endl;
    std::string addMark, addColor;
    shop::towar_int_t addPrice;
    int addAmount;

    std::cin>>addMark>>addColor>>addPrice>>addAmount;
    bags.emplace_back(addMark, addColor, addPrice, addAmount);

}

void shop::Bagpack::removeBags()
{
    presentationOfBags();
    int chooseRemove = enteringTheNumber(1, bags.size());
    bags.erase(bags.begin() + chooseRemove);

}







