cmake_minimum_required(VERSION 3.15)
project(machineOfState)

set(CMAKE_CXX_STANDARD 14)



add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(machineOfState main.cpp ShopWare.h ShopWare.cpp BookManager.cpp BookManager.h
        NotepadManager.cpp NotepadManager.h Tests/NotepadTests.cpp tests.cpp Managers/BagpackManager.cpp
        Managers/BagpackManager.h generalFunctions.cpp generalFunctions.h SchoolSuppliesManager.cpp SchoolSuppliesManager.h
        Bill.cpp Bill.h Tests/TowarTests.cpp Application.cpp Application.h ServiceCsvTsv.cpp ServiceCsvTsv.h
        WriteCsvTsv.cpp WriteCsvTsv.h Tests/WritingReadingCsvTsvTests.cpp ReadCsvTsv.cpp ReadCsvTsv.h
        Tests/BookTests.cpp ConcreteBagpack.cpp ConcreteBagpack.h Tests/BagpackTests.cpp ConcreteBook.cpp ConcreteBook.h
        ConcreteSchoolSupply.cpp ConcreteSchoolSupply.h ConcreteNotepad.cpp ConcreteNotepad.h Tests/SchoolSuppliesTests.cpp Library/Library.cpp Library/Library.h Library/ClientInLibrary.cpp Library/ClientInLibrary.h Tests/LibraryTests.cpp Library/TimeOfBorrowing.cpp Library/TimeOfBorrowing.h)

target_link_libraries(machineOfState gtest gtest_main)