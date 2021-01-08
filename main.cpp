#include <iostream>

#include <memory>

#include "generalFunctions.h"
#include "AccessoriesFactory.h"

//#include "accesories.h

#include <cassert>
#include <vector>
#include "tests.h"

#include "Application.h"
#include "Book.h"
#include "Notepad.h"
#include "Bagpack.h"
#include "SchoolSupplies.h"

#include "ServiceCsvTsv.h"

#include "Bill.h"

#include <gtest/gtest.h>

#include <map>
#include <gmock/gmock.h>
//#define CATCH_CONFIG_MAIN
//#include "Catch_tests/catch.hpp"



//#define CATCH_CONFIG_MAIN

using namespace std;

Application* Application::app = nullptr;

int main(int argc, char *argv[]) {

    Application::getInstance()->mode = CUSTOMER_MODE;

    testREMOVE();

    std::vector<std::string> t{"a","b","c"};
    ServiceCsvTsv s;
    std::string p1 = s.join(t,",");

    testing::InitGoogleTest(&argc,argv);
    int  p = RUN_ALL_TESTS();

    //testConio();
    //int c = 0;
    shop::Towar purchases;
    //purchases.readItemsFromFile();
    //int mode;
    purchases.mode = CUSTOMER_MODE;

    purchases.presentationOfServices();
    std::unique_ptr<shop::Towar>purch_ptr;
    //purch_ptr->presentationOfServices();

   // shop::Towar zakup;
    //zakup.readItemsFromFile();
    //zakup.changeModeToSellerMode(mode,"12trempki");





   // k1.titleOfBooksInShop.push_back("Hobbit");
   shop:: Book k1;
    for(int i =0;i<k1.titleOfBooksInShop.size(); i++)
    {
        cout << "Tytuly: " << k1.titleOfBooksInShop[i] << endl;
        cout<<k1.praisesOfBooksInShop[i]<<endl;
    }
//    shop::Przybory ol("Olowek",5);
  //  ol.bookedPrzybory.push_back(ol);

    //int s = ol.bookedPrzybory.size();
   // cout<<s<<endl;



   purchases.etap = START;                //odwołania do enuma z deklaracji klasy Towar
    assert(purchases.etap==START);
    if(purchases.enterToShop())
    {
        purchases.etap = INTRODUCTION;
       // zakup.presentationOfServices();
    }

    //std::vector<shop::Book> ksiazki;

    //shop::Towar t1(std::vector<shop::Towar>);

    purchases.readRemoveFromFile();
    while(purchases.etap!=CONFIRM)
    {
        //mode = SELLER_MODE;

        //OPISAC WYBORTRYBOW I FUNKCJI DLaUZytkownika

        if(purchases.mode == CUSTOMER_MODE)
        {
            std::string title;
            int choose;
            choose = purchases.chooseOfService();

            if(choose == 1)
            {
                shop::Book *ksiega = new shop::Book(title);
                ksiega->readItemsFromFile();                      //odczyt musi nastąpić zaraz po deklaracji
                purchases.readRemoveFromFile();
                ksiega->searchInRemoved();                      //sprawdza czy element z kontenera jest w ogolnym spisie elementow tytulow ksiazek
                                                                //i oddaje ten element na swoje miejsce "polke"
                if (ksiega->searchingBook() == shop::Book::FOUND)
                {
                    purchases.paramOfChoosenThing = ksiega->chooseOfSearchedBook();    //t - parametr okreslajacy wybrana pozycje ks w currentSearching
                    if (purchases.paramOfChoosenThing == ksiega->getSizeOfCurrentSearchings())
                    {
                        cout << "wybrano zadna z pow" << endl;
                    }
                    else
                        {
                        cout << "T: " << purchases.paramOfChoosenThing << endl;
                        ksiega->choosenTitle = ksiega->getSearchedBook(purchases.paramOfChoosenThing - 1);
                        //int t = ksiega->checkIfBookExist(ksiega,ksiega->choosenTitle);
                        cout << "Tytul: " << ksiega->choosenTitle << endl;
                        purchases.position = ksiega->checkIfBookExist(ksiega->choosenTitle);

                        cout << "Ilosc; " << ksiega->amountOfBooksInShop[purchases.paramOfChoosenThing - 1] << endl;
                        if (ksiega->checkAmountofBookInShop(purchases))
                        {

                            purchases.name = ksiega->titleOfBooksInShop[purchases.position];        //zapisanie nazwy biezacej ksiazki do zmiennej titleOfBooksInShop klasy Towar
                            purchases.praise = ksiega->praisesOfBooksInShop[purchases.position];    //zapisanie ceny biezacej ksiazki do zmiennj klasy Towar
                            cout << "Wybr. tyt: " << purchases.name << endl;
                            purchases.addToPurchases();//dodanie do koszyka

                            cout << "Param: " << purchases.position << endl;

                            purchases.showOrderedPurchases();
                        }
                    }
                }
                else
                {
                    purchases.showOrderedPurchases();
                }

                ///oddaje pozycje umieszczone w buforze zwrotnym, w którym umieszczone są rzeczy zwrocone przez kupujacego
                ///spowrotem do sklepu, do odpowiednich rodzajów rzeczy zwiekszając przy tym liczebność danej rzeczy o jeden
                //ksiega->amountOfBooksInShop = incrementAmountOfNoteAfterReturnedItToShop(purchases.removedThings,
                //                                                                         ksiega->titleOfBooksInShop,
                //                                                                         ksiega->amountOfBooksInShop);

                remove(purchases.removedThings,
                                                 ksiega->titleOfBooksInShop,
                                                 ksiega->amountOfBooksInShop); // zwrot niechcianych ksiazek z koszyka powrotemo do sklepu
                //getBackToShop<shop::Book>(ksiega,purchases);

                ///zapisuje vector - ze zwróconymi nazwami rzeczy przez kupującego jeszcze w trakcie wykonywania zakupów - do pliku .txt
                purchases.saveRemovedToFile();

                ///zapisuje aktualny stan - nazwy wszystkich rzeczy, ich aktualną liczebnosc i ceny do plików .txt
                ksiega->saveItemsToFile();  //zapisanie biezacego stanu sklepu
                delete ksiega;
            }

            else if(choose==2)
            {
                shop::Notepad *zeszyt = new shop::Notepad();
               // zeszyt->dimensions.clear();
                zeszyt->readItemsFromFile(); // wczytanie danych
                purchases.readRemoveFromFile();

                cout<<"Size dimension notes: "<<zeszyt->dimensions.size()<<endl;
                //y
                // assert(zeszyt->dimensions.size()==3);
                //zeszyt->setDimensionsOfNote();
                int c;
                c=zeszyt->chooseOfDimension();
                cout<<"c: "<<c<<endl;

                //zeszyt->chooseOfColor();
                purchases.name = zeszyt->dimensions[c-1];
                purchases.praise = zeszyt->price[c-1];
                if(zeszyt->checkIfNoteIsAvailable(c)) // sprawdfzenie czy zeszyt o wybranej pozycji jest nadal dostepny
                {
                    zeszyt->amount[c-1]--;    //sprawdzenie czy jest jeszcze dostepny towar danego rodzaju

                    purchases.addToPurchases();
                    purchases.showOrderedPurchases();
                }
                else
                {
                    cout<<"BRAK ZESZYTOW O ROZMIARZE: "<<purchases.name<<endl;
                    purchases.showOrderedPurchases();
                }


               /* for(int i=0;i<purchases.removedThings.size();i++) //co to jest??? czemu nie daje rady tego oddzielic do osobnej funkcji??
                {
                    for(int j=0;j<zeszyt->dimensions.size();j++)
                    {
                        if(purchases.removedThings[i] == zeszyt->dimensions[j])
                        {
                            purchases.removedThings.erase(purchases.removedThings.begin() + i);
                            //zeszyt->amount[j]++;
                        }
                    }
                }*/

                //zeszyt->amount = incrementAmountOfNoteAfterReturnedItToShop(purchases.removedThings, zeszyt->dimensions,
                //                                                            zeszyt->amount);
                purchases.remove(purchases.removedThings,zeszyt->dimensions,zeszyt->amount);

                //purchases.pairOfRemovedAndItsPosition = remove(purchases.removedThings,zeszyt->dimensions,zeszyt->amount); //TO jest to
                //zeszyt->addThingFromRemovedToShop(purchases.pairOfRemovedAndItsPosition)
                //zeszyt->amount = zeszyt->incrementAmountofRemovedThing(purchases.pairOfRemovedAndItsPosition);
                //getBackToShop<shop::Notepad>(zeszyt,purchases);
                //purchases.removedThings.erase(purchases.removedThings.begin());

                //zeszyt->returnNoteFromBasketToShop(purchases.removedThings, zeszyt->dimensions, zeszyt->amount); //zwraca rzecxz do sklepu(nie wiem dlaczego
                // musiałem tu jeszcze raz przekazywac
                // obiekt tego samego typu co klasa z której pochodzi ta funkcja
                zeszyt->saveItemsToFile(); //zapis na koncu!!!
                purchases.saveRemovedToFile();

                delete zeszyt;

            }

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////

            else if(choose == 3)
            {

                shop::Bagpack b1;

                //b1.bags.emplace_back("Pumaa","Blue",10,6);//zrobic tak: robic odczyty z plikow i na tej podstawie tworzyc obiekty i zapisywac je do vectora bags
                //b1.bags.emplace_back("Nike","Black",24,3);
                                                            //i z danych w vectorze przeprowadzac operacje obsługi, dodawania, usuwania itp..
                b1.readItemsFromFile();
                purchases.readRemoveFromFile();
                b1.presentationOfBags();

                b1.getMarksAndAmounts();
                purchases.remove(purchases.removedThings,b1.allMarks,b1.allAmounts);
                b1.refreshObjectsAfterRemoving(b1.bags);

                b1.chooseBag(purchases);             //przekazanie całego obiektu przez referencje aby była mozliwosc jego modyfikacji w funkcji
                purchases.showOrderedPurchases();


                //b1.allAmounts = b1.getAmounts();

                b1.saveItemsToFile();
                purchases.saveRemovedToFile();
            }

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////

            else if(choose == 4)
            {
                shop::SchoolSupplies supplies;


                supplies.readItemsFromFile();
                purchases.readRemoveFromFile();

                supplies.presentationOfSupplies();
                supplies.chooseSup(purchases);

                supplies.getSize();

                purchases.showOrderedPurchases();

                supplies.getNamesAndAmounts();
                purchases.remove(purchases.removedThings,supplies.names,supplies.amounts);
                supplies.refreshAmount();

                supplies.saveItemsToFile();
                purchases.saveRemovedToFile();
            }

            else if(choose == 5)
            {
                ///logika usuniecia przedmiiotu z koszyka uzytkownika
                purchases.readRemoveFromFile();
               purchases.removedThings.push_back(purchases.removeThingFromPurchases()) ;

               for(int i=0;i<purchases.removedThings.size();i++)
               {
                   cout<<"Usuniete: "<<purchases.removedThings[i]<<endl;
               }
               purchases.saveRemovedToFile();
            }

            else if(choose == 6)
            {
                purchases.mode = purchases.changeModeToSellerMode("12trempki",purchases.mode);
            }
            else if(choose == 7)
            {
                cout<<"Tu"<<endl;
                purchases.etap = CONFIRM;
            }

            else
            {
                purchases.chooseOfService();
            }

            //sprawdzic czy klient juz konczy zakupy i wystawuc mu rachunek po przerwaniu petli...


        }

        else if(purchases.mode == SELLER_MODE)//TRZEBA ZROBIC OBSLUGE WSZYSTKICH RZECZ -NIE TYLKO KSIAZEK!!!
        {
            std::string title;
            cout<<"ELO"<<endl;
            purchases.presentationOfServices();
            //choose = purchases.chooseOfService();
            //cout<<"Choose: "<<choose<<endl;
            //if(choose==1||choose ==2)
            {

                cout<<"Tu jestem"<<endl;
                auto *bookEdition = new shop::Book(title);
                auto *noteEdition = new shop::Notepad;
                auto *bagEdition = new shop::Bagpack();
                auto *suppliesEdition = new shop::SchoolSupplies;
                int chooseOfEdition = enteringTheNumber(1,7);
                switch(chooseOfEdition)
                {
                    case 1:
                        bookEdition->readItemsFromFile();
                        bookEdition->editionStateOfBooks();
                        bookEdition->saveItemsToFile();

                        delete bookEdition;

                        break;

                    case 2:
                        noteEdition->readItemsFromFile();
                        noteEdition->editionStateOfNotes();
                        noteEdition->saveItemsToFile();

                        delete noteEdition;

                        break;

                    case 3:
                        bagEdition->readItemsFromFile();
                        bagEdition->editionStateOfBags();
                        bagEdition->saveItemsToFile();

                        delete bagEdition;
                        break;

                    case 4:
                        suppliesEdition->readItemsFromFile();
                        suppliesEdition->editionState();
                        suppliesEdition->saveItemsToFile();

                        delete suppliesEdition;
                        break;

                    case 5:
                        purchases.mode = purchases.changeModeToSellerMode("12trempki",purchases.mode);
                        break;

                    default:
                        break;
                }

            }

        }


    }
   // placenie

    Bill bill;
    shop::towar_int_t toPay = bill.calculate(purchases);
    shop::towar_int_t wynik_x =( shop::towar_int_t )(( int )( toPay * 100 ) ) / 100;
    wynik_x = purchases.roundFloatToSecond(wynik_x);
    assert(purchases.orderedPurchasesName.size() == purchases.orderedPurchasesPrice.size());


    bill.printBill(purchases, toPay);
   /* shop::towar_int_t zaok2 = zaok*10000000;
    //dynamic_cast<long long unsigned int>zaok2;

    int zaok3 = 0;
    zaok3 = static_cast<long long int>(zaok2);

    if(zaok3%1000 == 0)
    {
        std::cout<<"oooo"<<std::endl;
        zaok2 = static_cast<shop::towar_int_t >(zaok3);
        zaok2 =zaok2/10000000;
    }*/



        // bill.printBill(purchases); //???

    int c1 = 10;

        return 0;
    //else {

        // bill.printBill(purchases);

        return 0;

   // }
}




