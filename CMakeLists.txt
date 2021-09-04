cmake_minimum_required(VERSION 3.15)
project(machineOfState)

set(CMAKE_CXX_STANDARD 20)



add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(machineOfState main.cpp ShopWare.h ShopWare.cpp Managers/BookManager.cpp Managers/BookManager.h
        Managers/NotepadManager.cpp Managers/NotepadManager.h Tests/NotepadTests.cpp Managers/BagpackManager.cpp
        Managers/BagpackManager.h generalFunctions.cpp generalFunctions.h Managers/SchoolSuppliesManager.cpp Managers/SchoolSuppliesManager.h
        Bill.cpp Bill.h Tests/TowarTests.cpp Application.cpp Application.h ServiceCsvTsv.cpp ServiceCsvTsv.h
        WriteCsvTsv.cpp WriteCsvTsv.h Tests/WritingReadingCsvTsvTests.cpp ReadCsvTsv.cpp ReadCsvTsv.h
        Tests/BookTests.cpp ConcreteItems/ConcreteBagpack.cpp ConcreteItems/ConcreteBagpack.h Tests/BagpackTests.cpp ConcreteItems/ConcreteBook.cpp ConcreteItems/ConcreteBook.h
        ConcreteItems/ConcreteSchoolSupply.cpp ConcreteItems/ConcreteSchoolSupply.h ConcreteItems/ConcreteNotepad.cpp ConcreteItems/ConcreteNotepad.h Tests/SchoolSuppliesTests.cpp Library/Library.cpp Library/Library.h Library/ClientInLibrary.cpp Library/ClientInLibrary.h Tests/LibraryTests.cpp Library/TimeOfBorrowing.cpp Library/TimeOfBorrowing.h)

target_link_libraries(machineOfState gtest gtest_main)