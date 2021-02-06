//
// Created by Admin on 06.02.2021.
//

#ifndef MACHINEOFSTATE_READCSVTSV_H
#define MACHINEOFSTATE_READCSVTSV_H

#include "ServiceCsvTsv.h"



class ReadCsvTsv :public ServiceCsvTsv  {
public:
    ReadCsvTsv(std::string path);

    void readFromFile(std::vector<std::string> &names, std::vector<int> &amounts, std::vector<double> &prices);

private:
    std::string path;

};


#endif //MACHINEOFSTATE_READCSVTSV_H
