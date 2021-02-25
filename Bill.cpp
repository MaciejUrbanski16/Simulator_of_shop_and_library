//
// Created by Admin on 20.09.2020.
//

#include "Bill.h"

shop::ware_t Bill::calculate()
{
    allGain = 0;
    for(int i=0;i<this->ware.orderedPurchasesPrice.size(); i++)
    {
        allGain  = allGain + this->ware.orderedPurchasesPrice[i];
    }
    
    return allGain;
}

void Bill::printBill(shop::ware_t toPay)
{
    std::cout<<std::endl<<std::endl<<std::endl;
    std::string sp;
    int longer = 0 ;

    time_t timeO; //give actual time
    time(&timeO);

    std::cout<<"SUM UP:      "<<ctime(&timeO)<<std::endl;

    for(int i = 0 ; i< 56; i++)
    {
        std::cout<<'-';
    }
    std::cout<<std::endl;

    for(int i=0;i<this->ware.orderedPurchasesPrice.size()+1; i++)
    {

        if(i < this->ware.orderedPurchasesPrice.size())
        {
            longer = this->ware.orderedPurchasesName[i].size();

            std::cout<<this->ware.orderedPurchasesName[i];

            while(longer < 50)
            {
                std::cout<<' ';
                longer++;
            }
            std::cout<<this->ware.orderedPurchasesPrice[i]<<std::endl;
        } else if (i == this->ware.orderedPurchasesPrice.size())
        {

            for(int j = 0;j< 56;j++)
            {
                std::cout<<'-';
            }
            std::cout<<std::endl;

            std::cout<<"SUM:";
            for(int j=0;j<41;j++)
            {
                std::cout<<' ';
            }
            std::cout<<toPay;
        }

    }

}

Bill::Bill(Ware &ware) {
    this->ware = ware;
}
