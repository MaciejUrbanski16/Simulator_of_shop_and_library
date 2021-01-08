//
// Created by Admin on 20.09.2020.
//

#ifndef MACHINEOFSTATE_BILL_H
#define MACHINEOFSTATE_BILL_H
//#include "accesories.h"
#include "Book.h"
#include "ctime"

using namespace shop;


class Bill : public shop::Ware {
public:
    Bill() = default;

    shop::towar_int_t calculate(Ware &towar);

    void printBill(shop::Ware &towar, shop::towar_int_t toPay);

    void payForPurchases();

private:
    shop::towar_int_t allGain;

};


#endif //MACHINEOFSTATE_BILL_H
