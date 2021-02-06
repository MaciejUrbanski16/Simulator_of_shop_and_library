//
// Created by Admin on 06.02.2021.
//

#include "WriteCsvTsv.h"


WriteCsvTsv::WriteCsvTsv(std::string path) {

    std::string ending = ".csv";

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

void WriteCsvTsv::writeToFile(std::vector<std::string> &data) {
    outToFile.open(path,std::ios::app);

    if(csvFormat){

        if(outToFile.is_open()) {
            toFile = join(data,",");
            outToFile << toFile <<std::endl;
        }
        else{
            throw std::exception();
        }
        outToFile.close();
    }
    else if (!csvFormat){

        if(outToFile.is_open()){

            toFile = join(data,"\t");
            outToFile << toFile <<std::endl;
        }
        else {
            throw
                    std::exception();
        }
        outToFile.close();

    }

}

void WriteCsvTsv::addHeader(std::vector<std::string> &data) {

    outToFile.open(path);
    if(csvFormat){
        if(outToFile.is_open()){
            outToFile << join(data,",")<<std::endl;
        }
    }
    else if(!csvFormat){
        if(outToFile.is_open()){
            outToFile << join(data,"\t")<<std::endl;
        }
    }
    outToFile.close();
}