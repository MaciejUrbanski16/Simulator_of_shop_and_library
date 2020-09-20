//
// Created by Admin on 12.09.2020.
//

#pragma once
//#include "accesories.h"
#include <string>
#include <vector>
template <class typ, std::size_t s>
typ fun(typ param);

std::vector<int> incrementAmountOfNoteAfterReturnedItToShop(std::vector<std::string> removedThings, std::vector<std::string> dimensions, std::vector<int>amount);
void remove(std::vector<std::string> &removedThings, std::vector<std::string> &dimensions,std::vector<int>&amount);

//#endif //MACHINEOFSTATE_GENERALFUNCTIONS_H
