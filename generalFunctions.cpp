//
// Created by Admin on 12.09.2020.
//
#include "generalFunctions.h"


void  remove(std::vector<std::string> &removedThings, std::vector<std::string> &dimensions,std::vector<int>&amount)
{
    for(int i=0;i<removedThings.size();i++)
    {
        for(int j=0;j<dimensions.size();j++)
        {
            if(removedThings[i] == dimensions[j])
            {
                removedThings.erase(removedThings.begin() + i);
                amount[j]++;
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
                amount[j]++;
                been = true;

                break;
            }
        }
    }
    return amount;
}

