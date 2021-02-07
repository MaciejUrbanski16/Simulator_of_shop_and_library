//
// Created by Admin on 06.02.2021.
//

#include "ReadCsvTsv.h"

#include "ReadCsvTsv.h"

using namespace base;

ReadCsvTsv::ReadCsvTsv(std::string path)  {
    for(int i =path.length()-4;i <= path.length()-1;i++){
        this->extensionOfFile +=path[i];
    }

    if(this->extensionOfFile == ".csv"){
        csvFormat = true;
        this->path = path;
    }
    else if(this->extensionOfFile == ".tsv"){
        csvFormat = false;
        this->path = path;
    }
    else{
        throw std::exception();
    }
}

void ReadCsvTsv::readFromFile(std::vector<std::string> &names, std::vector<int> &amounts, std::vector<double> &prices) {

    std::ifstream in;
    in.open(path);
    std::string line;
    std::vector<std::string> dataAsString;
    std::string tempStr;
    int i = 0;
    std::vector<std::string> read;
    if(csvFormat) {
        while (std::getline(in, line)) {
            if(i>=1){
                dataAsString = split(line,",");
                for(int i = 0 ; i<dataAsString.size();i++) {

                    //read.push_back(atof(dataAsString[i].c_str()));
                }
            }
            // read.push_back(split(line, ","));
            i++;
        }
    }
    else if(!csvFormat){
        while (std::getline(in, line)) {
            if(i>=1) {
                read = split(line,"\t");

                names.push_back(read[0]);

                amounts.push_back(atoi(read[1].c_str()));

                prices.push_back(atof(read[2].c_str()));
            }
            i++;
        }
    }

}