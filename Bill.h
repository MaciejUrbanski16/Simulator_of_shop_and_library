//
// Created by Admin on 20.09.2020.
//

#ifndef MACHINEOFSTATE_BILL_H
#define MACHINEOFSTATE_BILL_H

#include "Managers/BookManager.h"
#include "ctime"

using namespace shop;


class Bill : public shop::Ware {
public:
    Bill() = default;
    Bill(Ware &ware);

    shop::ware_t calculate();

    void printBill(shop::ware_t toPay);

    void payForPurchases();

private:
    shop::ware_t allGain;

    shop::Ware ware;

};


#endif //MACHINEOFSTATE_BILL_H
