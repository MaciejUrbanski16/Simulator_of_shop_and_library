//
// Created by Admin on 06.02.2021.
//

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
                for(const auto & i1 : dataAsString) {

                    read.push_back(i1);
                }
            }
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

void ReadCsvTsv::readFromFile(std::vector<shop::ConcreteBook> &books, std::vector<int> &amounts) {

    std::ifstream in;
    in.open(path);
    std::string line;
    std::vector<std::string> dataAsString;
    std::string tempStr;
    int i = 0;
    std::vector<std::string> read;
    if(csvFormat) {
        //*.csv
        while (std::getline(in, line)) {
            if(i>=1){
                dataAsString = split(line,",");
                for(auto & i1 : dataAsString) {

                    read.push_back(i1); //it is not ended
                }
            }

            i++;
        }
    }
    else if(!csvFormat){
        //*.tsv
        while (std::getline(in, line)) {
            if(i>=1) {
                read = split(line,"\t");

                //read[0]  --> author
                //read[1]  --> title
                //read[2]  --> price
                //read[3]  --> amount

                std::pair<std::string, std::string> pairFromReading(read[0],read[1]);

                //it storages amounts in another container
                amounts.push_back(atoi(read[3].c_str()));

                shop::ware_t priceFromReading = atof(read[2].c_str());

                //it storages books in one container
                books.emplace_back(pairFromReading, priceFromReading);
            }
            i++;
        }
    }

}

void ReadCsvTsv::readFromFile(std::vector<shop::ConcreteNotepad> &notepads, std::vector<int> &amounts) {

    std::ifstream in;
    in.open(path);
    std::string line;
    std::vector<std::string> dataAsString;
    std::string tempStr;
    int i = 0;
    std::vector<std::string> read;
    if(csvFormat) {
        //*.csv
        while (std::getline(in, line)) {
            if(i>=1){
                dataAsString = split(line,",");
                for(auto & i1 : dataAsString) {

                    read.push_back(i1); //it is not ended
                }
            }

            i++;
        }
    }
    else if(!csvFormat){
        //*.tsv
        while (std::getline(in, line)) {
            if(i>=1) {
                read = split(line,"\t");

                //read[0]  --> format
                //read[1]  --> price
                //read[2]  --> amount
                //read[3]  --> cards


                //it storages amounts in another container
                amounts.push_back(atoi(read[2].c_str()));

                int numOfCards = atoi(read[3].c_str());

                shop::ware_t priceFromReading = atof(read[1].c_str());

                //it storages notepads in one container
                notepads.emplace_back(read[0],numOfCards,priceFromReading);
            }
            i++;
        }
    }

}
