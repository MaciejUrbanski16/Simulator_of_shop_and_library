#include <iostream>

#include <memory>

#include "generalFunctions.h"

#include <cassert>
#include <vector>
#include "tests.h"

#include "Application.h"
#include "BookManager.h"
#include "Notepad.h"
#include "BagpackManager.h"
#include "ConcreteBagpack.h"
#include "SchoolSupplies.h"

#include "Bill.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <map>




using namespace std;

int mode;
int stage;

Application* Application::app = nullptr;


int main(int argc, char *argv[]) {

    //instancja klasy zawierajacej konfigurację programu
    Application application;

    testing::InitGoogleTest(&argc,argv);
    int t = RUN_ALL_TESTS();


    shop::Ware purchases;

    application.mode = CUSTOMER_MODE;

    application.presentationOfServices();

    application.stage = START;          //odwołania do enuma zawierajacego etapy zakupu z deklaracji klasy Ware

    if(purchases.enterToShop())
    {
        application.stage = INTRODUCTION;
    }

    application.readRemovedFromFile(); //wczytanie usunietych przedmiotow z bufora


    while(application.stage != CONFIRM) {


        ///PRZEŁĄCZENIE W ZALEŻNOŚCI OD TRYBU: KLIENTA/SPRZEDAWCY
        if (application.mode == CUSTOMER_MODE) {

            int choose;
            choose = application.chooseOfService();

            if (choose == 1) {

                shop::BookManager books;
                books.readItemsFromFile();                      //odczyt musi nastąpić zaraz po deklaracji
                application.readRemovedFromFile();
                books.searchInRemoved(application);             //sprawdza czy element z kontenera jest w ogolnym spisie elementow tytulow ksiazek

                std::string title = books.getTitleOfConcreteBook(0);
                cout<<"Title: "<<books.getTitleOfConcreteBook(0)<<endl;
                                                                    //i oddaje ten element na swoje miejsce "polke"
                //char choosenLetter = purchases.enterTheLetter();
                if (books.searchingBook() == shop::BookManager::FOUND) {
                    cout<<"Size "<< books.getSizeOfCurrentSearchings()<<endl;
                    purchases.paramOfChoosenThing = books.chooseOfSearchedBook();    //t - parametr okreslajacy wybrana pozycje ks w currentSearching
                    if (purchases.paramOfChoosenThing == books.getSizeOfCurrentSearchings()) {
                        cout << "Nie wybrano zadnej z powyzszych" << endl;
                    } else {

                        books.choosenTitle = books.getSearchedBook(purchases.paramOfChoosenThing - 1);
                        cout<<"Wybrano: "<<books.choosenTitle<<endl;
                        purchases.position = books.checkIfBookExist(books.choosenTitle);   //sprawdzenie, czy wybrana pozycja istnieje na liscie
                        cout<<"Pozycja: "<<purchases.position<<endl;
                        if (books.checkAmountofBookInShop(purchases)) {                        //sprawdzenie, czy jest jescze dostępna jakakolwiek ksiazka
                                                                                                //o wybranym tytule

                           // purchases.name = books.titleOfBooksInShop[purchases.position];        //zapisanie nazwy biezacej ksiazki do zmiennej titleOfBooksInShop klasy Ware
                            purchases.name = books.getBook(purchases.position).getPairOfTitleAndAuthorBook().first;//wyłuskanie tytułu ksiazki z pary
                            cout<<"Name: "<<purchases.name<<endl;
                            //purchases.praise = books.pricesOfBooksInShop[purchases.position];    //zapisanie ceny biezacej ksiazki do zmiennj klasy Ware
                            purchases.praise = books.getBook(purchases.position).getPrice();    //wyłuskanie ceny ksiazki
                            cout<<"Price: "<<purchases.praise;
                            purchases.addToPurchases();             //dodanie do koszyka

                            purchases.showOrderedPurchases();
                        }
                    }
                } else {
                    purchases.showOrderedPurchases();
                }


                ///oddaje pozycje umieszczone w buforze zwrotnym, w którym umieszczone są rzeczy zwrocone przez kupujacego
                ///spowrotem do sklepu, do odpowiednich rodzajów rzeczy zwiekszając przy tym liczebność danej rzeczy o jeden
                std::vector<ConcreteBook> b;
                b = books.getBooks(); //wyłuskanie zbioru ksiazek
                remove(application.removedThings,
                       b,
                       books.amountOfBooksInShop); // zwrot niechcianych ksiazek z koszyka powrotemo do sklepu

                ///zapisuje vector - ze zwróconymi nazwami rzeczy przez kupującego jeszcze w trakcie wykonywania zakupów - do pliku .txt
                application.saveRemovedToFile();

                ///zapisuje aktualny stan - nazwy wszystkich rzeczy, ich aktualną liczebnosc i ceny do plików .txt
                books.saveItemsToFile();  //zapisanie biezacego stanu sklepu

            } else if (choose == 2) {
                shop::Notepad notes;




                notes.readItemsFromFile(); // wczytanie danych
                application.readRemovedFromFile();

                cout << "Size dimension notes: " << notes.dimensions.size() << endl;

                assert(notes.dimensions.size() == notes.amount.size()); //asercja po odczycie danych

                int c;
                c = notes.chooseOfDimension();

                //notes->chooseOfColor();


                if (notes.checkIfNoteIsAvailable(c)) // sprawdzenie czy notes o wybranej pozycji jest nadal dostepny
                {
                    purchases.name = notes.dimensions[c - 1];
                    purchases.praise = notes.price[c - 1];

                    notes.amount[c - 1]--;          //dekrementacja ilosci wybranego notesu

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

                shop::BagpackManager bags;

                bags.readItemsFromFile();
                application.readRemovedFromFile();
                bags.presentationOfBags();

                bags.getMarks();
                purchases.remove(application.removedThings, bags.allMarks, bags.amountsOfBags);


                bags.chooseBagToPurchases(purchases);
                purchases.showOrderedPurchases();


                bags.saveItemsToFile();
                application.saveRemovedToFile();
            }

                ///////////////////////////////////////////////////////////////////////////////////////////////////////////

            else if (choose == 4) {
                shop::SchoolSupplies supplies;


                supplies.readItemsFromFile();
                application.readRemovedFromFile();

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
                application.readRemovedFromFile();//odczyt bufora usunietych rzeczy z  koszyka
                application.removedThings.push_back(purchases.removeThingFromPurchases());

                for (int i = 0; i < application.removedThings.size(); i++) {
                    cout << "Usuniete: " << application.removedThings[i] << endl;
                }
                application.saveRemovedToFile();


            } else if (choose == 6) {
                application.mode = purchases.changeModeToSellerMode("password", application.mode);


            } else if (choose == 7) {

                application.stage = CONFIRM;


            } else {
                application.chooseOfService();
            }

            //sprawdzic czy klient juz konczy zakupy i wystawuc mu rachunek po przerwaniu petli


        } else if (application.mode == SELLER_MODE)//TRZEBA ZROBIC OBSLUGE WSZYSTKICH RZECZ -NIE TYLKO KSIAZEK!!!
        {
            application.presentationOfServices();
            {

                auto *bookEdition = new shop::BookManager;
                auto *noteEdition = new shop::Notepad;
                auto *bagEdition = new shop::BagpackManager();
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

   if(!purchases.inSellerMode) {
       Bill bill(purchases);
       shop::ware_t toPay = bill.calculate();
       shop::ware_t wynik_x = (shop::ware_t) ((int) (toPay * 100)) / 100;
       wynik_x = purchases.roundFloatToSecond(wynik_x);
       assert(purchases.orderedPurchasesName.size() == purchases.orderedPurchasesPrice.size());

       bill.printBill(toPay);
   }

    return 0;


}




