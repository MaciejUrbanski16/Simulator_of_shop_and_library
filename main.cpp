
#include "generalFunctions.h"

#include "Application.h"

#include "Managers/BookManager.h"
#include "Managers/NotepadManager.h"
#include "Managers/BagpackManager.h"
#include "Managers/SchoolSuppliesManager.h"

#include "Library/Library.h"
#include "Library/TimeOfBorrowing.h"

#include "Bill.h"

#include <gtest/gtest.h>

#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <ctime>
#include <chrono>


int main(int argc, char *argv[]) {

    //start tests
    testing::InitGoogleTest(&argc,argv);


    srand(time(nullptr));

    //instance of class which includes config of program
    Application application;

    shop::Ware purchases(application);

    //initializing objects to storage data of library and its books
    shop::BookManager bookManager;
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
                            std::cout << "You do not choose any book! " << std::endl;
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

                std::cout << "Size dimension notes: " << notes.notepads.size() << std::endl;

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
                    std::cout << "There are no notes with chosen format " << purchases.name << std::endl;
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
                    std::cout << "Removed: " << removedThing << std::endl;
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


            int chooseOfEdition = application.enteringTheNumber(1, 5);

                //edition of chosen list of things (only in SELLER_MODE)
                if (chooseOfEdition == 1) {

                    auto *bookEdition = new shop::BookManager;
                    bookEdition->readItemsFromFile();
                    bookEdition->editionStateOfBooks();
                    bookEdition->saveItemsToFile();

                    delete bookEdition;

                }

                else if(chooseOfEdition == 2) {
                    auto *noteEdition = new shop::NotepadManager;
                    noteEdition->readItemsFromFile();
                    noteEdition->editionStateOfNotes();
                    noteEdition->saveItemsToFile();

                    delete noteEdition;

                }
                else if(chooseOfEdition == 3) {
                    auto *bagEdition = new shop::BagpackManager();
                    bagEdition->readItemsFromFile();
                    bagEdition->editionStateOfBags();
                    bagEdition->saveItemsToFile();

                    delete bagEdition;
                }

                else if(chooseOfEdition == 4) {
                    auto *suppliesEdition = new shop::SchoolSuppliesManager;
                    suppliesEdition->readItemsFromFile();
                    suppliesEdition->editionState();
                    suppliesEdition->saveItemsToFile();

                    delete suppliesEdition;
                }

                else if(chooseOfEdition == 5) {
                    application.mode = purchases.changeModeToSellerMode("password", application.mode);
                }


        }

        else if(static_cast<int>(Application::kindOfService::LIBRARY_BORROW) == application.kindOfService_ ||
                static_cast<int>(Application::kindOfService::LIBRARY_GIVE_BACK) == application.kindOfService_) {
            //implementation of library's behaviour

            shop::BookManager books;
            books.readItemsFromFile();

            library::Library library(books);
            library.readUsersFromFile();

            library::TimeOfBorrowing time1;
            std::string timePrev = time1.getCurrentTimeAsString();
            std::cout<<"AsString: "<<timePrev<<std::endl;


            std::cout << "You are at library. Please enter your ID number to login " << std::endl;
            std::cin >> library.enterIDtoLogin;

            while (library.attemptsToLogin > 1) {

                if (library.loginToLibrary(library.enterIDtoLogin)) {
                    std::cout << "You login successfully, now you can use from library resources" << std::endl;
                    library.attemptsToLogin = 3;
                    library.validLogin = true;
                    break;
                } else {
                    std::cout << "Your login ID is incorrect. You have " << library.attemptsToLogin
                              << " left!" << std::endl;
                    library.attemptsToLogin--;

                    std::cout << "Try to enter your ID number again!" << std::endl;
                    std::cin >> library.enterIDtoLogin;


                    if (library.attemptsToLogin == 1) {
                        std::cout
                                << "You do not have anymore attempts to login! Do you want to register new account [y/n]"
                                << std::endl;
                        std::cin >> library.createNewAccount;

                        if (library.createNewAccount == 'n') {
                            break;
                        }
                        else if (library.createNewAccount == 'y') {
                            std::cout << "Enter your name, surname and password in this order: " << std::endl;

                            library::ClientInLibrary newClient;

                            std::string name, surname, password;
                            std::cin >> name >> surname >> password;

                            newClient.setNameOfClient(name);
                            newClient.setSurnameOfClient(surname);

                            std::string clientID = library.generateIDofNewClient();

                            library.addNewClient(library::ClientInLibrary(name, surname, clientID));

                            library.validLogin = true;

                            library.currentIDloggedIn = std::atoi(clientID.c_str());
                        }
                    }
                }
            }

            //check if process of login was successful
            if (library.validLogin) {

                //if client wants to borrow a book
                if (static_cast<int>(Application::kindOfService::LIBRARY_BORROW) == application.kindOfService_ ) {

                    ///process of borrowing book from library

                    int indexOfActualClient = library.getIndexOfClientWithGivenID();

                    std::vector<library::ClientInLibrary> tempClients = library.getClients();

                    //get current time to compare with deadlines
                    library::TimeOfBorrowing currentTime;

                    //check if client has not any overdue books
                    ///TODO how to get deadline of concrete borrowed book

                    //bool canBorrow = true;

                    library::TimeLeft firstDeadline,actualTime(currentTime);
                    std::pair<int, library::TimeLeft> theShortestDeadline;

                    if(!tempClients[indexOfActualClient].getBorrowedByClient().empty()) {

                        //take the shortest term of book to give back
                        //index of this term is associated with this term
                        theShortestDeadline = tempClients[indexOfActualClient].getTheShortestDeadline();

                        if(actualTime > theShortestDeadline.second){
                            library.canBorrow = true;
                        } else{
                            library.canBorrow = false;
                        }
                    }


                    //compare the actual time with the shortest time (deadline)
                    if(library.canBorrow) {
                        
                        //there is time yet
                        std::cout << "There is time yet: " << actualTime - firstDeadline << std::endl;
                        
                        //search chosen book by client
                        if (books.searchingBook() == books.FOUND) {

                            purchases.indexOfChoosenThing = books.chooseOfSearchedBook();

                            if (purchases.indexOfChoosenThing == books.getSizeOfCurrentSearchings()) {
                                std::cout << "You did not choose any book to borrow! " << std::endl;
                            } else {

                                books.choosenTitle = books.getTitleOfSearchedBook(purchases.indexOfChoosenThing - 1);

                                purchases.position = books.checkIfBookExist(books.choosenTitle);   //check if chosen book exists in list and return position

                                if (books.checkAmountofBookInShop(purchases)) {                        //and check if there is available one book witth chosen title at least

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
                    else{
                        //the time was expired

                        //show book which time was expired
                        if(!tempClients[indexOfActualClient].getBorrowedByClient().empty()) {
                            std::cout << "The time of borrowing was expired! Until you give back your book "
                                      << tempClients[indexOfActualClient].getBorrowedByClient()[theShortestDeadline.first]
                                      <<
                                      " you can not borrow another! " << std::endl;
                        }
                    }
                }


                    ///process of giving back book to library
                    //if client wants to give back a book
                else if (static_cast<int>(Application::kindOfService::LIBRARY_GIVE_BACK) == application.kindOfService_) {

                    library.showBorrowedBooksByUser();


                    int indexOfActualClient = library.getIndexOfClientWithGivenID();
                    //i'm not sure if it is good idea to write code like this below, but i will have to do refactor of this
                    std::vector<library::ClientInLibrary> tempClients = library.getClients();

                    //if user has borrowed some books
                    if(!tempClients[indexOfActualClient].borrowedByClient.empty()) {

                        std::cout<<"Choose book you want to give back: "<<std::endl;

                        int choose = purchases.enteringTheNumber(1,
                                                                 library.getClients()[indexOfActualClient].borrowedByClient.size());


                        //here should be object of ConcreteBook
                        shop::ConcreteBook bookToGiveBack = tempClients[indexOfActualClient].borrowedByClient[choose - 1];

                        books.incrementAmountOfBook(bookToGiveBack);

                        std::vector<shop::ConcreteBook> actualStateOfBorrowedBooks = library.giveBackBook(choose - 1,
                                                                                                          tempClients[indexOfActualClient]);

                        tempClients[indexOfActualClient].setBorrowedByClient(actualStateOfBorrowedBooks);
                    }
                    else{
                        std::cout<< "You do not have any borrowed book "<<std::endl;
                        //application.stage = CONFIRM;
                    }

                    //refresh these instances
                    library.setClients(tempClients);
                    library.setManageBooks(books);

                }
            }

            //save all data after all
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




