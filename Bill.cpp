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

void Bill::printBill(shop::Towar &towar, shop::towar_int_t toPay)
{
    std::cout<<std::endl<<std::endl<<std::endl;
    //int longer = 0;
    int space = 50;
    //std::vector<char>spaces;
    std::string sp;
    int longer = 0 ;

    time_t timeO; // pobranie aktualnej daty i godziny
    time(&timeO);

    std::cout<<"PARAGON FISKALNY       "<<ctime(&timeO)<<std::endl;

    for(int i = 0 ; i< 56; i++)
    {
        std::cout<<'-';
    }
    std::cout<<std::endl;

    for(int i=0;i<towar.orderedPurchasesPrice.size()+1; i++)
    {
        //longer = orderedPurchasesName[i].size();
       // int freeArea  = space - longer;
       // while(freeArea <space)

           //freeArea++;
            //spaces.push_back(' ');
           //sp +=" ";

        //longer =0;
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
    //sp = "";
    //std::cout<<std::endl;
    //while(longer <40)

    //    std::cout<<' ';
     //   longer++;


}
