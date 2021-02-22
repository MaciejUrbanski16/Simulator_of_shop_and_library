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

#include "Library/Library.h"

#include "Bill.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <map>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {

    srand(time(nullptr));

    //instance of class which includes config of program
    Application application;

    //start tests
    testing::InitGoogleTest(&argc,argv);



    shop::Ware purchases(application);

    BookManager bookManager;
    library::Library lib(bookManager);
    lib.readUsersFromFile();


    application.mode = CLIENT_MODE;

    application.presentationOfServices();

    application.stage = START;

    application.setKindOfService();

    application.readRemovedFromFile(); //load removed thing from buffer

    //main loop of program
    while(application.stage != CONFIRM) {


        ///SWITCH DEPENDS ON ACTUAL MODE
        if (application.mode == CLIENT_MODE &&
            static_cast<Application::kindOfService>(application.kindOfService_) == Application::kindOfService::SHOP) {

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

                            books.choosenTitle = books.getTitleOfSearchedBook(purchases.indexOfChoosenThing - 1);

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

        else if (application.mode == SELLER_MODE &&
                static_cast<int>(Application::kindOfService::SHOP) == application.kindOfService_)
        {
            application.presentationOfServices();
            {

                auto *bookEdition = new shop::BookManager;
                auto *noteEdition = new shop::NotepadManager;
                auto *bagEdition = new shop::BagpackManager();
                auto *suppliesEdition = new shop::SchoolSuppliesManager;
                int chooseOfEdition = enteringTheNumber(1, 5);

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

        else if(static_cast<int>(Application::kindOfService::LIBRARY_BORROW) == application.kindOfService_ ||
                static_cast<int>(Application::kindOfService::LIBRARY_GIVE_BACK) == application.kindOfService_) {
            //implementation of library's behaviour

            BookManager books;
            books.readItemsFromFile();

            library::Library library(books);
            library.readUsersFromFile();

            std::cout << "S1: " << library.getClients().size() << std::endl;


            std::cout << "You are at library. Please enter your ID number and password to login " << std::endl;
            std::cin >> library.enterIDtoLogin;
            std::cin >> library.enterPasswordToLogin;

            while (library.attemptsToLogin > 1) {

                if (library.loginToLibrary(library.enterIDtoLogin)) {
                    std::cout << "You login successfully, now you can use from library resources" << std::endl;
                    library.attemptsToLogin = 3;
                    library.validLogin = true;
                    break;
                } else {
                    std::cout << "Your login or password are incorrect. You have " << library.attemptsToLogin
                              << " left!" << std::endl;
                    library.attemptsToLogin--;

                    std::cout << "Try to enter your ID number and password again!" << std::endl;
                    std::cin >> library.enterIDtoLogin;
                    std::cin >> library.enterPasswordToLogin;

                    if (library.attemptsToLogin == 1) {
                        std::cout
                                << "You do not have anymore attempts to login! Do you want to register new account [y/n]"
                                << std::endl;
                        std::cin >> library.createNewAccount;

                        if (library.createNewAccount == 'n') {
                            break;
                        } else if (library.createNewAccount == 'y') {
                            std::cout << "Enter your name, surname and password in this order: " << std::endl;

                            library::ClientInLibrary newClient;

                            std::string name, surname, password;
                            std::cin >> name >> surname >> password;

                            newClient.setNameOfClient(name);
                            newClient.setSurnameOfClient(surname);

                            std::string clientID = library.generateIDofNewClient();
                            //TODO make generating  id of new client by randoming
                            library.addNewClient(library::ClientInLibrary(name, surname, clientID));

                            library.validLogin = true;

                            library.currentIDloggedIn = std::atoi(clientID.c_str());
                        }
                    }
                }
            }

            //check if process of login was successful
            if (library.validLogin) {
                if (static_cast<int>(Application::kindOfService::LIBRARY_BORROW) == application.kindOfService_ ) {

                    ///process of borrowing book from libraary

                    if (books.searchingBook() == books.FOUND) {

                        purchases.indexOfChoosenThing = books.chooseOfSearchedBook();

                        if (purchases.indexOfChoosenThing == books.getSizeOfCurrentSearchings()) {
                            cout << "You do not choose any book to borrow! " << endl;
                        } else {
                            std::cout << "TU";
                            books.choosenTitle = books.getTitleOfSearchedBook(purchases.indexOfChoosenThing - 1);

                            purchases.position = books.checkIfBookExist(
                                    books.choosenTitle);   //check if chosen book exists in list and return position
                            std::cout << "TU";
                            if (books.checkAmountofBookInShop(
                                    purchases)) {                        //and check if there is available one book witth chosen title at least

                                //borrow book
                                std::string tempTitle = books.choosenTitle;
                                library.borrowBook(purchases.position, tempTitle);

                                std::cout << "You borrow " << books.tempAuthor << "   " << tempTitle << std::endl;

                                library.setManageBooks(books); //refresh actual state of book in library

                            }
                        }
                    } else {
                        std::cout << "There are no more books with given title! " << std::endl;
                    }
                }


                    ///process of giving back book to library
                else if (static_cast<int>(Application::kindOfService::LIBRARY_GIVE_BACK) == application.kindOfService_) {
                    std::cout<<"Przed oddaniem: "<<library.getClients()[1].borrowedByClient.size()<<std::endl;
                    std::cout<<"Choose book you want to give back: "<<std::endl;
                    library.showBorrowedBooksByUser();
                    int index = library.getIndexOfClientWithGivenID();


                    //i'm not sure if it is good idea to write code like this below, but i will have to do refactor of this
                    int choose = purchases.enteringTheNumber(1,library.getClients()[index].borrowedByClient.size());

                    int indexOfActualClient = library.getIndexOfClientWithGivenID();
                    std::vector<library::ClientInLibrary> tempClients = library.getClients();

                    std::string choosenBookToGiveBack = reinterpret_cast<basic_string<char> &&>(tempClients[indexOfActualClient].borrowedByClient[choose]);

                    //library.giveBackBook(choosenBookToGiveBack,
                      //      tempClients[indexOfActualClient]);
                      std::vector<shop::ConcreteBook> actualStateOfBorrowedBooks = library.giveBackBook(choose, tempClients[indexOfActualClient]);

                    tempClients[indexOfActualClient].setBorrowedByClient(actualStateOfBorrowedBooks);

                    library.setClients(tempClients);

                    int p= 1;
                    p++;

                }
            }



            std::cout<<"S2: "<<library.getClients().size()<<std::endl;
            std::cout<<"S2: "<<library.getClients().back().getNameOfClient()<<std::endl;

            std::cout<<"Przed zapisem: "<<library.getClients()[1].borrowedByClient.size()<<std::endl;

            library.saveUsersToFile();
            books.saveItemsToFile();



            application.stage = CONFIRM;//temporary
        }

    }



   /// show bill after shopping

   if(!purchases.inSellerMode && static_cast<int>(Application::kindOfService::SHOP) == application.kindOfService_) {

       Bill bill(purchases);
       shop::ware_t toPay = bill.calculate();
       shop::ware_t wynik_x = (shop::ware_t) ((int) (toPay * 100)) / 100;
       wynik_x = purchases.roundFloatToSecond(wynik_x);
       assert(purchases.orderedPurchasesName.size() == purchases.orderedPurchasesPrice.size());

       bill.printBill(toPay);
   }

    return 0;//RUN_ALL_TESTS();
}




