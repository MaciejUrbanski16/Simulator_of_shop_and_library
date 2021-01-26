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

#include "Bill.h"

#include <gtest/gtest.h>

#include <map>
#include <gmock/gmock.h>




//#define CATCH_CONFIG_MAIN

using namespace std;

Application* Application::app = nullptr;

int mode;
int stage;

int main(int argc, char *argv[]) {


    Application application;
    testREMOVE();

    testing::InitGoogleTest(&argc,argv);
    int  p = RUN_ALL_TESTS();


    shop::Ware purchases;

    application.mode = CUSTOMER_MODE;

    application.presentationOfServices();
    std::unique_ptr<shop::Ware>purch_ptr;


    application.stage = START;                //odwołania do enuma z deklaracji klasy Ware

    if(purchases.enterToShop())
    {
        application.stage = INTRODUCTION;
    }


    application.readRemoveFromFile(); //wczytanie usunietych przedmiotow z bufora
    while(application.stage != CONFIRM)
    {
        //stage = SELLER_MODE;

        //OPISAC WYBORTRYBOW I FUNKCJI DLaUZytkownika

        if(application.mode == CUSTOMER_MODE)
        {
            std::string title;
            int choose;
            choose = application.chooseOfService();

            if(choose == 1)
            {
                unique_ptr<shop::Book> ksiega;
                ksiega->readItemsFromFile();                      //odczyt musi nastąpić zaraz po deklaracji
                application.readRemoveFromFile();
                ksiega->searchInRemoved(application);                      //sprawdza czy element z kontenera jest w ogolnym spisie elementow tytulow ksiazek
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

                            purchases.name = ksiega->titleOfBooksInShop[purchases.position];        //zapisanie nazwy biezacej ksiazki do zmiennej titleOfBooksInShop klasy Ware
                            purchases.praise = ksiega->praisesOfBooksInShop[purchases.position];    //zapisanie ceny biezacej ksiazki do zmiennj klasy Ware
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


                remove(application.removedThings,
                                                 ksiega->titleOfBooksInShop,
                                                 ksiega->amountOfBooksInShop); // zwrot niechcianych ksiazek z koszyka powrotemo do sklepu

                ///zapisuje vector - ze zwróconymi nazwami rzeczy przez kupującego jeszcze w trakcie wykonywania zakupów - do pliku .txt
                application.saveRemovedToFile();

                ///zapisuje aktualny stan - nazwy wszystkich rzeczy, ich aktualną liczebnosc i ceny do plików .txt
                ksiega->saveItemsToFile();  //zapisanie biezacego stanu sklepu

            }

            else if(choose==2)
            {
                unique_ptr<shop::Notepad> notes;
               // notes->dimensions.clear();
                notes->readItemsFromFile(); // wczytanie danych
                application.readRemoveFromFile();

                cout << "Size dimension notes: " << notes->dimensions.size() << endl;
                //y
                // assert(notes->dimensions.size()==3);
                //notes->setDimensionsOfNote();
                int c;
                c=notes->chooseOfDimension();
                cout<<"c: "<<c<<endl;

                //notes->chooseOfColor();
                purchases.name = notes->dimensions[c - 1];
                purchases.praise = notes->price[c - 1];
                if(notes->checkIfNoteIsAvailable(c)) // sprawdfzenie czy notes o wybranej pozycji jest nadal dostepny
                {
                    notes->amount[c - 1]--;    //sprawdzenie czy jest jeszcze dostepny towar danego rodzaju

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
                    for(int j=0;j<notes->dimensions.size();j++)
                    {
                        if(purchases.removedThings[i] == notes->dimensions[j])
                        {
                            purchases.removedThings.erase(purchases.removedThings.begin() + i);
                            //notes->amount[j]++;
                        }
                    }
                }*/

                //notes->amount = incrementAmountOfNoteAfterReturnedItToShop(purchases.removedThings, notes->dimensions,
                //                                                            notes->amount);
                purchases.remove(application.removedThings, notes->dimensions, notes->amount);

                //purchases.pairOfRemovedAndItsPosition = remove(purchases.removedThings,notes->dimensions,notes->amount); //TO jest to
                //notes->addThingFromRemovedToShop(purchases.pairOfRemovedAndItsPosition)
                //notes->amount = notes->incrementAmountofRemovedThing(purchases.pairOfRemovedAndItsPosition);
                //getBackToShop<shop::Notepad>(notes,purchases);
                //purchases.removedThings.erase(purchases.removedThings.begin());

                //notes->returnNoteFromBasketToShop(purchases.removedThings, notes->dimensions, notes->amount); //zwraca rzecxz do sklepu(nie wiem dlaczego
                // musiałem tu jeszcze raz przekazywac
                // obiekt tego samego typu co klasa z której pochodzi ta funkcja
                notes->saveItemsToFile(); //zapis na koncu!!!
                application.saveRemovedToFile();

            }

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////

            else if(choose == 3)
            {

                unique_ptr<shop::Bagpack> bags;

                //b1.bags.emplace_back("Pumaa","Blue",10,6);//zrobic tak: robic odczyty z plikow i na tej podstawie tworzyc obiekty i zapisywac je do vectora bags
                //b1.bags.emplace_back("Nike","Black",24,3);
                                                            //i z danych w vectorze przeprowadzac operacje obsługi, dodawania, usuwania itp..
                bags->readItemsFromFile();
                application.readRemoveFromFile();
                bags->presentationOfBags();

                bags->getMarksAndAmounts();
                purchases.remove(application.removedThings,bags->allMarks,bags->allAmounts);
                bags->refreshObjectsAfterRemoving(bags->bags);

                bags->chooseBag(purchases);             //przekazanie całego obiektu przez referencje aby była mozliwosc jego modyfikacji w funkcji
                purchases.showOrderedPurchases();


                bags->saveItemsToFile();
                application.saveRemovedToFile();
            }

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////

            else if(choose == 4)
            {
                unique_ptr<shop::SchoolSupplies> supplies;


                supplies->readItemsFromFile();
                application.readRemoveFromFile();

                supplies->presentationOfSupplies();
                supplies->chooseSup(purchases);

                supplies->getSize();

                purchases.showOrderedPurchases();

                supplies->getNamesAndAmounts();
                purchases.remove(application.removedThings,supplies->names,supplies->amounts);
                supplies->refreshAmount();

                supplies->saveItemsToFile();
                application.saveRemovedToFile();
            }

            else if(choose == 5)
            {
                ///logika usuniecia przedmiiotu z koszyka uzytkownika
                application.readRemoveFromFile();
               application.removedThings.push_back(purchases.removeThingFromPurchases()) ;

               for(int i=0;i<application.removedThings.size();i++)
               {
                   cout<<"Usuniete: "<<application.removedThings[i]<<endl;
               }
               application.saveRemovedToFile();
            }

            else if(choose == 6)
            {
                application.mode = purchases.changeModeToSellerMode("12trempki",application.mode);
            }
            else if(choose == 7)
            {
                cout<<"Tu"<<endl;
                application.stage = CONFIRM;
            }

            else
            {
                application.chooseOfService();
            }

            //sprawdzic czy klient juz konczy zakupy i wystawuc mu rachunek po przerwaniu petli...


        }

        else if(application.mode == SELLER_MODE)//TRZEBA ZROBIC OBSLUGE WSZYSTKICH RZECZ -NIE TYLKO KSIAZEK!!!
        {
            std::string title;
            cout<<"ELO"<<endl;
            application.presentationOfServices();
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
                        application.mode = purchases.changeModeToSellerMode("12trempki",application.mode);
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




