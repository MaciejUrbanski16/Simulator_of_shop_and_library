//
// Created by Admin on 20.09.2020.
//

#include "Bill.h"

shop::towar_int_t Bill::calculate(shop::Towar &towar)
{
    allGain = 0;
    for(int i=0;i<towar.orderedPurchasesPrice.size(); i++)
    {
        allGain  = allGain + towar.orderedPurchasesPrice[i];
    }
    return allGain;
}

void Bill::printBill(shop::Towar &towar)
{
    int longer = 0;
    //std::vector<char>spaces;
    std::string sp = "";
    for(int i=0;i<towar.orderedPurchasesPrice.size(); i++)
    {
        longer = orderedPurchasesName[i].size();
        while(longer <40)
        {
            longer++;
            //spaces.push_back(' ');
            sp +=' ';
        }
        longer =0;
        std::cout<<towar.orderedPurchasesName[i]<<sp<<towar.orderedPurchasesPrice[i]<<std::endl;
    }

    while(longer <40)
    {
        std::cout<<' ';
        longer++;
    }
    longer =0;
    std::cout<<calculate(towar);
}
