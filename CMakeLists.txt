cmake_minimum_required(VERSION 3.15)
project(machineOfState)

set(CMAKE_CXX_STANDARD 14)



add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(machineOfState main.cpp accesories.h accesories.cpp Book.cpp Book.h Notepad.cpp Notepad.h Tests/NotepadTests.cpp tests.cpp Bagpack.cpp Bagpack.h generalFunctions.cpp generalFunctions.h SchoolSupplies.cpp SchoolSupplies.h Bill.cpp Bill.h Tests/TowarTests.cpp AccessoriesFactory.cpp AccessoriesFactory.h Application.cpp Application.h ConcreteBook.cpp ConcreteBook.h ServiceCsvTsv.cpp ServiceCsvTsv.h WriteCsvTsv.cpp WriteCsvTsv.h Tests/WritingReadingCsvTsvTests.cpp ReadCsvTsv.cpp ReadCsvTsv.h)
target_link_libraries(machineOfState gtest gtest_main)