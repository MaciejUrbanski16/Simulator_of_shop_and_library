//
// Created by Admin on 15.09.2020.
//

#include "SchoolSuppliesManager.h"
#include "ReadCsvTsv.h"
#include "WriteCsvTsv.h"
#include "tests.h"



void shop::SchoolSuppliesManager::readItemsFromFile()
{
    fileWithSupplies.open("supplies.txt");


    if(fileWithSupplies.good())
    {
        while(getline(fileWithSupplies,line))
        {
            createObjectsFromDates(line);
        }
    }

}

void shop::SchoolSuppliesManager::saveItemsToFile()
{
        std::fstream saveDate("supplies.txt",std::ios::out);

        for(int i=0;i<schoolSupplies.size();i++)
        {
            if(i+1 == schoolSupplies.size())
            {
                saveDate<< schoolSupplies[i].getName() <<' '<<schoolSupplies[i].getPrice()<<' '<<amounts[i]<<" _";
            }
            else
                saveDate<< schoolSupplies[i].getName() <<' '<<schoolSupplies[i].getPrice()<<' '<<amounts[i]<<" _" <<std::endl;
        }
}

void shop::SchoolSuppliesManager::createObjectsFromDates(const std::string& line1)
{
    int iter = 0;

    nameOfSup = getDate<std::string>(iter,line1);
    priceOfSup = getDate<std::string>(iter,line1);
    amountOfSup = getDate<std::string>(iter,line1);

    price = atof(priceOfSup.c_str());
    amount = atoi(amountOfSup.c_str());

    ConcreteSchoolSupply s;
    s.setPrice(price);
    s.setName(nameOfSup);

    schoolSupplies.push_back(s);
    this->amounts.push_back(amount);

}

template<typename dateType>
dateType shop::SchoolSuppliesManager::getDate(int &it, std::string line1) {
    std::string getStr;
    for(int i =it;i< line1.length();i++)
    {
        while(line1[i] != ' ')
        {
            getStr +=line1[i];
            it++;
            i++;
        }
        it++;
        i++;
        break;
    }

    return getStr;
}

void shop::SchoolSuppliesManager::presentationOfSupplies()
{
    cout<<"List of available school supplies: "<<endl;

    for(int i=0;i<schoolSupplies.size(); i++)
    {
        std::cout<<i+1<<". "<<schoolSupplies[i].getName()<<std::endl;
    }

}

uint32_t shop::SchoolSuppliesManager::getSize()
{
    return schoolSupplies.size();
}

void shop::SchoolSuppliesManager::chooseSup(shop::Ware &towar)
{
    int c = towar.enteringTheNumber(1,schoolSupplies.size());

    if(amounts[c-1] > 0)
    {
        towar.name = schoolSupplies[c-1].getName();
        towar.praise = schoolSupplies[c-1].getPrice();

        amounts[c-1]--;

        towar.addToPurchases();
    }
    else
    {
        std::cout<<"There is no "<<schoolSupplies[c-1].getName()<<std::endl;
    }
}

std::vector<std::string> shop::SchoolSuppliesManager::getNames()
{
    std::string name_;

    for(auto & schoolSupplie : schoolSupplies)
    {
        name_ = schoolSupplie.getName();
        names_.push_back(name_);
    }

    return names_;

}


void shop::SchoolSuppliesManager::editionState()
{
   int choose = enteringTheNumber(1,2);

   switch(choose)
   {
       case 1:
           addSuplies();
           break;
       case 2:
           remSuplies();
       default: break;
   }
}

void shop::SchoolSuppliesManager::remSuplies()
{
    std::cout<<"Choose thing you want to incrementAmountOfReturnedItem: "<<std::endl;

    int c = enteringTheNumber(1,schoolSupplies.size());

    schoolSupplies.erase(schoolSupplies.begin()+c -1);
    amounts.erase(amounts.begin() + c - 1 );
}

void shop::SchoolSuppliesManager::addSuplies()
{
    std::cout<<"Enter name, price, amount of concrete school supply"<<std::endl;
    cin>>name_ADD;
    cin>>price_ADD;
    cin>>amount_ADD;

    ConcreteSchoolSupply s;
    s.setPrice(price_ADD);
    s.setName(name_ADD);

    schoolSupplies.push_back(s);
    amounts.push_back(amount_ADD);
}

