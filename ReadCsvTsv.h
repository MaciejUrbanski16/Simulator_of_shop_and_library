//
// Created by Admin on 06.02.2021.
//

#ifndef MACHINEOFSTATE_READCSVTSV_H
#define MACHINEOFSTATE_READCSVTSV_H

#include "ServiceCsvTsv.h"
#include "ConcreteBook.h"
#include "ConcreteNotepad.h"

#include "Library/ClientInLibrary.h"

namespace library{
    class Library;
    class ClientInLibrary;
}

namespace shop{
    class ConcreteBook;
    class ConcreteNotepad;
}

namespace base {

    class ReadCsvTsv : public ServiceCsvTsv {
    public:
        ReadCsvTsv(std::string path);

        void readFromFile(std::vector<std::string> &names, std::vector<int> &amounts, std::vector<double> &prices);

        void readFromFile(std::vector<shop::ConcreteBook> &books, std::vector<int> &amounts);

        void readFromFile(std::vector<shop::ConcreteNotepad> &notepads, std::vector<int> &amounts);

        void readFromFile(std::vector<library::ClientInLibrary> &clients);

    private:
        std::string path;

    };
}


#endif //MACHINEOFSTATE_READCSVTSV_H
