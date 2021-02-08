//
// Created by Admin on 20.09.2020.
//

#include "Bill.h"

shop::towar_int_t Bill::calculate(shop::Ware &towar)
{
    allGain = 0;
    for(int i=0;i<towar.orderedPurchasesPrice.size(); i++)
    {
        allGain  = allGain + towar.orderedPurchasesPrice[i];
    }
    
    return allGain;
}

void Bill::printBill(shop::Ware &towar, shop::towar_int_t toPay)
{
    std::cout<<std::endl<<std::endl<<std::endl;
    std::string sp;
    int longer = 0 ;

    time_t timeO; //give actual time
    time(&timeO);

    std::cout<<"PARAGON FISKALNY       "<<ctime(&timeO)<<std::endl;

    for(int i = 0 ; i< 56; i++)
    {
        std::cout<<'-';
    }
    std::cout<<std::endl;

    for(int i=0;i<towar.orderedPurchasesPrice.size()+1; i++)
    {

        if(i < towar.orderedPurchasesPrice.size())
        {
            longer = towar.orderedPurchasesName[i].size();

            std::cout<<towar.orderedPurchasesName[i];

            while(longer < 50)
            {
                std::cout<<' ';
                longer++;
            }
            std::cout<<towar.orderedPurchasesPrice[i]<<std::endl;
        } else if (i == towar.orderedPurchasesPrice.size())
        {

            for(int j = 0;j< 56;j++)
            {
                std::cout<<'-';
            }
            std::cout<<std::endl;

            std::cout<<"SUMA PTU:";
            for(int j=0;j<41;j++)
            {
                std::cout<<' ';
            }
            std::cout<<toPay;
        }

    }

}
