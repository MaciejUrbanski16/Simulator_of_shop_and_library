//

//
#include "tests.h"

int enteringTheNumber(int minValue, int maxValue)
{
    int howMuch = 0;
    if(minValue > maxValue)
    {
        int temp = maxValue;
        minValue = maxValue;
        maxValue = temp;
    }

    int where = -1;

    cout<<"Podaj cyfre z zakresu od "<<minValue<<" do "<<maxValue<<" aby wybrac usluge"<<endl;

    where = 4;

    bool good1,bad1;


    do{

        cin>>where;

        good1 = cin.good();
        bad1 = cin.bad();
        cin.clear();
        cin.sync();
    }while((where<minValue||where>maxValue)||(good1==0||bad1==1));
    //cin>>howMuch;

    return where;
}

