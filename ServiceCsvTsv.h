//
// Created by Admin on 08.01.2021.
//

#ifndef MACHINEOFSTATE_SERVICECSVTSV_H
#define MACHINEOFSTATE_SERVICECSVTSV_H


#include <vector>
#include <string>
#include <fstream>

class ServiceCsvTsv{
public:
    ServiceCsvTsv() = default;


protected:
    std::string join(const std::vector<std::string> &data, const std::string &delimiter);

    std::string extensionOfFile;
    bool csvFormat;

private:

};


#endif //MACHINEOFSTATE_SERVICECSVTSV_H
