//
// Created by Admin on 15.09.2020.
//

#include "SchoolSupplies.h"
#include "ReadCsvTsv.h"
#include "WriteCsvTsv.h"
#include "tests.h"

#include <utility>

shop::SchoolSupplies::SchoolSupplies(std::string name, towar_int_t price, int amount)
{
    this->name = std::move(name);
    this->price = price;
    this->amount = amount;
}

void shop::SchoolSupplies::readItemsFromFile()
{
    fileWithSupplies.open("supplies.txt");


    if(fileWithSupplies.good())
    {
        while(getline(fileWithSupplies,line))
        {
            createObjectsFromDates(this->schoolSupplies, line);
        }
    }

}

void shop::SchoolSupplies::saveItemsToFile()
{
        std::fstream saveDate("supplies.txt",std::ios::out);

        WriteCsvTsv writeSupplies("supplies.tsv");

        std::vector<std::string> header = {"NAZWA","ILOSC","CENA"};
        writeSupplies.addHeader(header);

        std::string readyData;
        std::vector<std::string> dataToTsv;


        for(int i=0;i<schoolSupplies.size();i++)
        {
            readyData = schoolSupplies[i].name;
            dataToTsv.push_back(readyData);

            readyData = to_string(schoolSupplies[i].amount);
            dataToTsv.push_back(readyData);

            readyData = to_string(schoolSupplies[i].price);
            dataToTsv.push_back(readyData);

            writeSupplies.writeToFile(dataToTsv);

            dataToTsv.clear();
            /*if(i+1 == schoolSupplies.size())
            {
                saveDate<< schoolSupplies[i].name <<' '<<schoolSupplies[i].price<<' '<<schoolSupplies[i].amount<<" _";
            }
            else
                saveDate<< schoolSupplies[i].name <<' '<<schoolSupplies[i].price<<' '<<schoolSupplies[i].amount<<" _" <<std::endl;*/
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

void shop::SchoolSupplies::chooseSup(shop::Ware &towar)
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

void shop::SchoolSupplies::refreshAmount()
{
    for(int i=0;i<names.size();i++)
    {
        this->schoolSupplies[i].amount = amounts[i];
    }
}

void shop::SchoolSupplies::editionState()
{
   //shop::Ware::removeThing<SchoolSupplies>(suppliesEdition,suppliesEdition->schoolSupplies);
   int choose = enteringTheNumber(1,2);
   switch(choose)
   {
       case 1:
           addSuplies();
           break;
       case 2:
           remSuplies();
   }
}

void shop::SchoolSupplies::remSuplies()
{
    std::cout<<"Wybierz ktora rzecz usunac"<<std::endl;
    int c = enteringTheNumber(1,schoolSupplies.size());
    schoolSupplies.erase(schoolSupplies.begin()+c -1);
}

void shop::SchoolSupplies::addSuplies()
{
    std::cout<<"Podaj kolejno nazwe, cene i ilosc rzeczy"<<std::endl;
    cin>>name_ADD;
    cin>>price_ADD;
    cin>>amount_ADD;

    schoolSupplies.emplace_back(name_ADD,price_ADD,amount_ADD);
}

/*void shop::SchoolSupplies::refreshAmount() {
    for(int i=0;i<schoolSupplies.size();i++)
    {
        schoolSupplies[i].amount = amounts[i];
    }
}*/

