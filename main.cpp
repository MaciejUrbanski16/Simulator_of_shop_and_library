#include <iostream>

#include "generalFunctions.h"

#include <cassert>
#include <vector>
#include "tests.h"

#include "Application.h"
#include "BookManager.h"
#include "NotepadManager.h"
#include "BagpackManager.h"
#include "SchoolSuppliesManager.h"

#include "Bill.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <map>

using namespace std;

int main(int argc, char *argv[]) {

    //instance of class which includes config of program
    Application application;

    //start tests
    testing::InitGoogleTest(&argc,argv);
    int t = RUN_ALL_TESTS();


    shop::Ware purchases(application);

    application.mode = CUSTOMER_MODE;

    application.presentationOfServices();

    application.stage = START;

    if(purchases.enterToShop())
    {
        application.stage = INTRODUCTION;
    }

    application.readRemovedFromFile(); //load removed thing from buffer

    //main loop of program
    while(application.stage != CONFIRM) {


        ///SWITCH DEPENDS ON ACTUAL MODE
        if (application.mode == CUSTOMER_MODE) {

            int choose;
            choose = application.chooseOfService();

            if (choose == 1) {

                shop::BookManager books;
                books.readItemsFromFile();                      //load data firstly
                application.readRemovedFromFile();
                books.searchInRemoved(application);             //check if element in container is situated in general list of books
                                                                    //and give back it to its place in shop

                if (books.searchingBook() == shop::BookManager::FOUND) {

                    purchases.indexOfChoosenThing = books.chooseOfSearchedBook();

                    if (purchases.indexOfChoosenThing == books.getSizeOfCurrentSearchings()) {
                        cout << "You do not choose any book! " << endl;
                    } else {

                        books.choosenTitle = books.getSearchedBook(purchases.indexOfChoosenThing - 1);

                        purchases.position = books.checkIfBookExist(books.choosenTitle);   //check if chosen book exists in list

                        if (books.checkAmountofBookInShop(purchases)) {                        //and check if there is available one book witth chosen
                                                                                                //title at least

                            purchases.name = books.getTitleOfConcreteBook(purchases.position);//rewrite title and price of chosen book
                                                                                                //to add it to basket
                            purchases.praise = books.getBook(purchases.position).getPrice();

                            purchases.addToPurchases();                                         //add chosen book to basket

                            purchases.showOrderedPurchases();
                        }
                    }
                } else {
                    purchases.showOrderedPurchases();
                }


                //gives back books which are situated in buffer (removedThings),
                //match it to proper kind of book,
                //and increase amount of this book

                remove(application.removedThings,
                       books.books_,
                       books.amounts_);


                //save container with returned books by user to file
                application.saveRemovedToFile();

                //save actual state of book after all process
                books.saveItemsToFile();

            } else if (choose == 2) {
                shop::NotepadManager notes;


                notes.readItemsFromFile(); // load data about notepads
                application.readRemovedFromFile(); // load removed

                cout << "Size dimension notes: " << notes.notepads.size() << endl;

                assert(notes.notepads.size() == notes.amounts.size()); //control assert

                int c;
                c = notes.chooseOfDimension();

                //notes->chooseOfColor();


                if (notes.checkIfNoteIsAvailable(c)) // check if chosen note is still available
                {
                    purchases.name = notes.notepads[c - 1].getFormat();
                    purchases.praise = notes.notepads[c - 1].getPrice();

                    notes.amounts[c - 1]--;          //decrement of amount chosen note

                    purchases.addToPurchases();
                    purchases.showOrderedPurchases();
                } else {
                    cout << "There are no notes with chosen format " << purchases.name << endl;
                    purchases.showOrderedPurchases();
                }

                //rewrite formats to match removed formats to formats in list so that increment their amount
                std::vector<std::string> formats = notes.getFormats();
                purchases.incrementAmountOfReturnedItem(application.removedThings, formats, notes.amounts);


                //save after all!!!
                notes.saveItemsToFile();
                application.saveRemovedToFile();

            }

                ///////////////////////////////////////////////////////////////////////////////////////////////////////////

            else if (choose == 3) {

                shop::BagpackManager bags;

                bags.readItemsFromFile();
                application.readRemovedFromFile();
                bags.presentationOfBags();

                bags.getMarks();
                purchases.incrementAmountOfReturnedItem(application.removedThings, bags.allMarks, bags.amountsOfBags);


                bags.chooseBagToPurchases(purchases);
                purchases.showOrderedPurchases();


                bags.saveItemsToFile();
                application.saveRemovedToFile();
            }

                ///////////////////////////////////////////////////////////////////////////////////////////////////////////

            else if (choose == 4) {
                shop::SchoolSuppliesManager supplies;


                supplies.readItemsFromFile();
                application.readRemovedFromFile();

                supplies.presentationOfSupplies();
                supplies.chooseSup(purchases);

                supplies.getSize();

                purchases.showOrderedPurchases();

                std::vector<std::string> names = supplies.getNames();
                purchases.incrementAmountOfReturnedItem(application.removedThings, names, supplies.amounts);

                supplies.saveItemsToFile();
                application.saveRemovedToFile();

            } else if (choose == 5) {

                ///logic of removing thing from basket to shop

                //read buffer with removed things
                application.readRemovedFromFile();

                //and save removed things by user during actual shopping
                application.removedThings.push_back(purchases.removeThingFromPurchases());

                for (const auto & removedThing : application.removedThings) {
                    cout << "Removed: " << removedThing << endl;
                }

                //save all removed things to file
                application.saveRemovedToFile();


            } else if (choose == 6) {

                ///change mode
                application.mode = purchases.changeModeToSellerMode("password", application.mode);


            } else if (choose == 7) {
                ///end of shopping
                application.stage = CONFIRM;


            } else {
                //default
                application.chooseOfService();
            }



        }

        else if (application.mode == SELLER_MODE)
        {
            application.presentationOfServices();
            {

                auto *bookEdition = new shop::BookManager;
                auto *noteEdition = new shop::NotepadManager;
                auto *bagEdition = new shop::BagpackManager();
                auto *suppliesEdition = new shop::SchoolSuppliesManager;
                int chooseOfEdition = enteringTheNumber(1, 7);

                //edition of chosen list of things (only in SELLER_MODE)
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

   // show bill after shopping

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




