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

    //instancja klasy zawierajacej konfiguracje programu
    Application application;
    testREMOVE();

    testing::InitGoogleTest(&argc,argv);
    int  p = RUN_ALL_TESTS();


    shop::Ware purchases;

    application.mode = CUSTOMER_MODE;

    application.presentationOfServices();


    application.stage = START;          //odwołania do enuma z deklaracji klasy Ware

    if(purchases.enterToShop())
    {
        application.stage = INTRODUCTION;

    }
    application.readRemoveFromFile(); //wczytanie usunietych przedmiotow z bufora


    while(application.stage != CONFIRM) {

        //OPISAC WYBORTRYBOW I FUNKCJI DLaUZytkownika

        if (application.mode == CUSTOMER_MODE) {
            std::string title;
            int choose;
            choose = application.chooseOfService();

            if (choose == 1) {

                shop::Book ksiega;
                ksiega.readItemsFromFile();                      //odczyt musi nastąpić zaraz po deklaracji
                application.readRemoveFromFile();
                ksiega.searchInRemoved(application);             //sprawdza czy element z kontenera jest w ogolnym spisie elementow tytulow ksiazek
                                                                    //i oddaje ten element na swoje miejsce "polke"
                if (ksiega.searchingBook() == shop::Book::FOUND) {
                    purchases.paramOfChoosenThing = ksiega.chooseOfSearchedBook();    //t - parametr okreslajacy wybrana pozycje ks w currentSearching
                    if (purchases.paramOfChoosenThing == ksiega.getSizeOfCurrentSearchings()) {
                        cout << "Nie wybrano zadnej z powyzszych" << endl;
                    } else {

                        ksiega.choosenTitle = ksiega.getSearchedBook(purchases.paramOfChoosenThing - 1);

                        purchases.position = ksiega.checkIfBookExist(ksiega.choosenTitle);

                        if (ksiega.checkAmountofBookInShop(purchases)) {

                            purchases.name = ksiega.titleOfBooksInShop[purchases.position];        //zapisanie nazwy biezacej ksiazki do zmiennej titleOfBooksInShop klasy Ware
                            purchases.praise = ksiega.praisesOfBooksInShop[purchases.position];    //zapisanie ceny biezacej ksiazki do zmiennj klasy Ware

                            purchases.addToPurchases();//dodanie do koszyka

                            purchases.showOrderedPurchases();
                        }
                    }
                } else {
                    purchases.showOrderedPurchases();
                }

                ///oddaje pozycje umieszczone w buforze zwrotnym, w którym umieszczone są rzeczy zwrocone przez kupujacego
                ///spowrotem do sklepu, do odpowiednich rodzajów rzeczy zwiekszając przy tym liczebność danej rzeczy o jeden


                remove(application.removedThings,
                       ksiega.titleOfBooksInShop,
                       ksiega.amountOfBooksInShop); // zwrot niechcianych ksiazek z koszyka powrotemo do sklepu

                ///zapisuje vector - ze zwróconymi nazwami rzeczy przez kupującego jeszcze w trakcie wykonywania zakupów - do pliku .txt
                application.saveRemovedToFile();

                ///zapisuje aktualny stan - nazwy wszystkich rzeczy, ich aktualną liczebnosc i ceny do plików .txt
                ksiega.saveItemsToFile();  //zapisanie biezacego stanu sklepu

            } else if (choose == 2) {
                shop::Notepad notes;

                notes.readItemsFromFile(); // wczytanie danych
                application.readRemoveFromFile();

                cout << "Size dimension notes: " << notes.dimensions.size() << endl;

                assert(notes.dimensions.size() == notes.amount.size()); //asercja po odczycie danych

                int c;
                c = notes.chooseOfDimension();

                //notes->chooseOfColor();

                purchases.name = notes.dimensions[c - 1];
                purchases.praise = notes.price[c - 1];
                if (notes.checkIfNoteIsAvailable(c)) // sprawdzenie czy notes o wybranej pozycji jest nadal dostepny
                {
                    notes.amount[c - 1]--;    //sprawdzenie czy jest jeszcze dostepny towar danego rodzaju

                    purchases.addToPurchases();
                    purchases.showOrderedPurchases();
                } else {
                    cout << "BRAK ZESZYTOW O ROZMIARZE: " << purchases.name << endl;
                    purchases.showOrderedPurchases();
                }

                purchases.remove(application.removedThings, notes.dimensions, notes.amount);

                notes.saveItemsToFile(); //zapis na koncu!!!
                application.saveRemovedToFile();

            }

                ///////////////////////////////////////////////////////////////////////////////////////////////////////////

            else if (choose == 3) {

                shop::Bagpack bags;

                bags.readItemsFromFile();
                application.readRemoveFromFile();
                bags.presentationOfBags();

                bags.getMarksAndAmounts();
                purchases.remove(application.removedThings, bags.allMarks, bags.allAmounts);
                bags.refreshObjectsAfterRemoving(bags.bags);

                bags.chooseBag(purchases);
                purchases.showOrderedPurchases();


                bags.saveItemsToFile();
                application.saveRemovedToFile();
            }

                ///////////////////////////////////////////////////////////////////////////////////////////////////////////

            else if (choose == 4) {
                shop::SchoolSupplies supplies;


                supplies.readItemsFromFile();
                application.readRemoveFromFile();

                supplies.presentationOfSupplies();
                supplies.chooseSup(purchases);

                supplies.getSize();

                purchases.showOrderedPurchases();

                supplies.getNamesAndAmounts();
                purchases.remove(application.removedThings, supplies.names, supplies.amounts);
                supplies.refreshAmount();

                supplies.saveItemsToFile();
                application.saveRemovedToFile();

            } else if (choose == 5) {

                ///logika usuniecia przedmiotu z koszyka uzytkownika
                application.readRemoveFromFile();//odczyt bufora usunietych rzeczy z  koszyka
                application.removedThings.push_back(purchases.removeThingFromPurchases());

                for (int i = 0; i < application.removedThings.size(); i++) {
                    cout << "Usuniete: " << application.removedThings[i] << endl;
                }
                application.saveRemovedToFile();


            } else if (choose == 6) {
                application.mode = purchases.changeModeToSellerMode("password", application.mode);


            } else if (choose == 7) {
                cout << "Tu" << endl;
                application.stage = CONFIRM;


            } else {
                application.chooseOfService();
            }

            //sprawdzic czy klient juz konczy zakupy i wystawuc mu rachunek po przerwaniu petli


        } else if (application.mode == SELLER_MODE)//TRZEBA ZROBIC OBSLUGE WSZYSTKICH RZECZ -NIE TYLKO KSIAZEK!!!
        {
            std::string title;

            application.presentationOfServices();
            {

                auto *bookEdition = new shop::Book;
                auto *noteEdition = new shop::Notepad;
                auto *bagEdition = new shop::Bagpack();
                auto *suppliesEdition = new shop::SchoolSupplies;
                int chooseOfEdition = enteringTheNumber(1, 7);

                //edycja wybranej listy rzeczy (tylko w trybie sprzedawcy)
                switch (chooseOfEdition) {
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
                        application.mode = purchases.changeModeToSellerMode("password", application.mode);
                        break;

                    default:
                        break;
                }

            }

        }


    }

   // Pokazanie rachunku

    Bill bill(purchases);
    shop::towar_int_t toPay = bill.calculate();
    shop::towar_int_t wynik_x =( shop::towar_int_t )(( int )( toPay * 100 ) ) / 100;
    wynik_x = purchases.roundFloatToSecond(wynik_x);
    assert(purchases.orderedPurchasesName.size() == purchases.orderedPurchasesPrice.size());

    bill.printBill(toPay);

    return 0;


}




