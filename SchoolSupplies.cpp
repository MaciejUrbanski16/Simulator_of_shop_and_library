//
// Created by Admin on 15.09.2020.
//

#include "SchoolSupplies.h"

#include <utility>

shop::SchoolSupplies::SchoolSupplies(std::string name, towar_int_t price, int amount)
{
    this->name = std::move(name);
    this->price = price;
    this->amount = amount;
}

void shop::SchoolSupplies::readItemsFromFile(std::vector<SchoolSupplies> &supplies)
{
    fileWithSupplies.open("supplies.txt");

    if(fileWithSupplies.good())
    {
        while(getline(fileWithSupplies,line))
        {
            createObjectsFromDates(supplies, line);
        }
    }

}

void shop::SchoolSupplies::saveItemsToFile()
{
        std::fstream saveDate("supplies.txt",std::ios::out);

        for(int i=0;i<schoolSupplies.size();i++)
        {
            if(i+1 == schoolSupplies.max_size())
            {
                saveDate<< schoolSupplies[i].name <<' '<<schoolSupplies[i].price<<' '<<schoolSupplies[i].amount<<" _";
            }
            else
                saveDate<< schoolSupplies[i].name <<' '<<schoolSupplies[i].price<<' '<<schoolSupplies[i].amount<<" _" <<std::endl;
        }
}

void shop::SchoolSupplies::createObjectsFromDates(std::vector<SchoolSupplies> &supplies,const std::string& line1)
{
    int iter = 0;

    nameOfSup = getDate<std::string>(iter,line1);
    priceOfSup = getDate<std::string>(iter,line1);
    amountOfSup = getDate<std::string>(iter,line1);

    price = atof(priceOfSup.c_str());
    amount = atoi(amountOfSup.c_str());

    supplies.emplace_back(nameOfSup, price, amount);

}

template<typename dateType>
dateType shop::SchoolSupplies::getDate(int &it, std::string line1) {
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

void shop::SchoolSupplies::presentationOfSupplies()
{
    for(int i=0;i<schoolSupplies.size(); i++)
    {
        std::cout<<i+1<<". "<<schoolSupplies[i].name<<std::endl;
    }

}

void shop::SchoolSupplies::getSize()
{

}

void shop::SchoolSupplies::chooseSup(shop::Towar &towar)
{
    int c = towar.enteringTheNumber(1,schoolSupplies.size());

    if(schoolSupplies[c-1].amount>0)
    {
        towar.name = schoolSupplies[c-1].name;
        towar.praise = schoolSupplies[c-1].price;

        schoolSupplies[c-1].amount--;

        towar.addToPurchases();
    }
    else
    {
        std::cout<<"Nie ma juz zadnej "<<schoolSupplies[c-1].name<<std::endl;
    }
}

void shop::SchoolSupplies::getNamesAndAmounts()
{


    for(auto & schoolSupplie : schoolSupplies)
    {
        names.push_back(schoolSupplie.name);
        amounts.push_back(schoolSupplie.amount);
    }

}

void shop::SchoolSupplies::refreshAmount(std::vector<SchoolSupplies> &schoolSupplies1)
{
    for(int i=0;i<names.size();i++)
    {
        schoolSupplies1[i].amount = amounts[i];
    }
}

void shop::SchoolSupplies::editionState()
{
   //shop::Towar::removeThing<SchoolSupplies>(suppliesEdition,suppliesEdition->schoolSupplies);
}

/*void shop::SchoolSupplies::refreshAmount() {
    for(int i=0;i<schoolSupplies.size();i++)
    {
        schoolSupplies[i].amount = amounts[i];
    }
}*/

