//
// Created by Admin on 08.01.2021.
//

#include "ServiceCsvTsv.h"

#include <vector>
#include <string>


std::string ServiceCsvTsv::join(const std::vector<std::string> &data, const std::string &delimiter){
    std::string out;
    for(int i = 0 ; i< data.size();i++){
        if(i == data.size()-1) {
            out += data[i];
        }else {
            out += data[i];
            out += delimiter;
        }
    }
    return out;
}