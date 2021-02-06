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

std::vector<std::string> ServiceCsvTsv::split(const std::string &data, const std::string &delimiter){

    int ind =0;
    std::vector<std::string> out;
    std::string text;
    std::vector<int>indexes;//przechowuje indeksy, w których zaczynają sie separatory
    std::string compare;
    compare = "";
    int j = 0;
    int s = delimiter.size();
    if(s == 0){
        out.push_back(data);//gdy brak separatora -> zwrócenie ciągu wejściowego
    }
    else {
        for (int i = 0; i < data.size(); i++) {

            if (data[i] == delimiter[j]) {
                ind = i;
                compare += data[i];
                j++;
                if (compare == delimiter && compare.size() == s) {
                    indexes.push_back(ind);
                    compare = "";
                }

            } else {
                j = 0;
                compare = "";
                if (data[i] == delimiter[j]) {
                    compare += data[i];
                    j++;
                }
                if (compare == delimiter && compare.size() == s) {
                    indexes.push_back(i);
                }

            }
        }
        out.clear();
        text = "";

        //dodanie poczatkowego i koncowego indeksu do vectora indeksow
        indexes.insert(indexes.begin(), 0);
        indexes.insert(indexes.end(), data.size());
        std::string d = data;

        for (int i = 1; i < indexes.size() - 1; i++) {
            indexes[i] -= delimiter.size();
        }

        for (int i = 0; i < indexes.size() - 1; i++) {
            if (i == 0) {
                for (int l = indexes[i]; l <= indexes[i + 1]; l++) {
                    text += d[l];
                }
            } else if (i == indexes.size() - 2) {
                for (int l = indexes[i] + delimiter.size() + 1; l < data.size(); l++) {
                    text += d[l];
                }
            } else {
                for (int l = indexes[i] + delimiter.size() + 1; l <= indexes[i + 1]; l++) {
                    text += d[l];
                }
            }

            out.push_back(text);
            text = "";

        }
        for (int i = 0; i < out.size(); i++) {
            if (out[i] == "") {
                out.erase(out.begin() + i);
            }
        }
    }

    return out;
}
