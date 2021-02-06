//
// Created by Admin on 13.01.2021.
//

#ifndef MACHINEOFSTATE_WRITECSVTSV_H
#define MACHINEOFSTATE_WRITECSVTSV_H
#include "ServiceCsvTsv.h"

class WriteCsvTsv :public ServiceCsvTsv {

public:
    WriteCsvTsv(std::string path);

    void writeToFile(std::vector<std::string> &data);
    void addHeader(std::vector<std::string> &data);

private:
    std::string path;
    std::ofstream outToFile;
    std::string toFile;
};


#endif //MACHINEOFSTATE_WRITECSVTSV_H
