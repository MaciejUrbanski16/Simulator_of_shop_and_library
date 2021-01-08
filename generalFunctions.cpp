//
// Created by Admin on 12.09.2020.
//
#include "generalFunctions.h"
template <class typ, std::size_t s>
typ fun(typ param)
{
    return param;
}

void  remove(std::vector<std::string> &removedThings, std::vector<std::string> &dimensions,std::vector<int>&amount)
{
    //std::map<std::string, int> pairOfRemovedThingAndPosition;
    for(int i=0;i<removedThings.size();i++)
    {
        for(int j=0;j<dimensions.size();j++)
        {
            if(removedThings[i] == dimensions[j])
            {
                removedThings.erase(removedThings.begin() + i);
                amount[j]++;
                //pairOfRemovedThingAndPosition[removedThings[i]] = j;
            }
        }
    }

}
std::vector<int> incrementAmountOfNoteAfterReturnedItToShop(std::vector<std::string> removedThings, std::vector<std::string> dimensions, std::vector<int>amount)
{
    bool been = false;
    for(int i=0;i<removedThings.size();i++)
    {
        if(been)
        {
            break;
        }
        for(int j=0;j<dimensions.size();j++)
        {
            if(removedThings[i] == dimensions[j])
            {
                //removedThings.erase(removedThings.begin() + i);
                amount[j]++;
                //pairOfRemovedThingAndPosition[removedThings[i]] = j;
                been = true;
                break;
            }
        }
    }
    return amount;
}


/*template <typename T> void getBackToShop(T *k,shop::Ware t)
{
    for(int i=0;i<t.removedThings.size();i++)
    {
        for(int j=0;j<k->titleOfBooksInShop.size();j++)
        {
            if(t.removedThings[i] == k->titleOfBooksInShop[j])
            {
                t.removedThings.erase(t.removedThings.begin() + i);
                k->amountOfBooksInShop[j]++;
            }
        }
    }
}*/


//int presentationOfServices(int);

//std::vector<shop::Ware>towary;
