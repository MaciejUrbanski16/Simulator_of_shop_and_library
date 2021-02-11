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
void testREMOVE()
{
    vector<int> liczby1 = {1,2,3,4,5,6,7,8};
    liczby1.erase(liczby1.begin());
 //   for(int i : liczby1)
    //{
   //     cout<<i<<endl;
    //}
}

void testConio()
{
    char letter;
    while (!_kbhit())
    {


        letter = getch();



    }
    cout<<"Wcisnieto: "<<letter<<endl;
}

void test()
{
    std::vector<int>t;
    for(std::vector<int>::iterator iter = t.begin(); iter<t.end();iter++)
    {
    }
    t.erase(t.begin()+2);
    for(std::vector<int>::iterator iter = t.begin(); iter!=t.end();iter++)
    {
        cout<<t[*iter]<<endl;
    }
}

