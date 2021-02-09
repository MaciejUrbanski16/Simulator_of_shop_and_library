//
// Created by Admin on 20.01.2021.
//

#ifndef MACHINEOFSTATE_BILL_H
#define MACHINEOFSTATE_BILL_H

#include "Book.h"
#include "ctime"

using namespace shop;


class Bill : public shop::Ware {
public:
    Bill() = default;
    Bill(Ware &ware);

    shop::towar_int_t calculate();

    void printBill(shop::towar_int_t toPay);

    void payForPurchases();

private:
    shop::towar_int_t allGain;

    shop::Ware ware;

};


#endif //MACHINEOFSTATE_BILL_H
