//
// Created by Admin on 20.09.2020.
//

#ifndef MACHINEOFSTATE_BILL_H
#define MACHINEOFSTATE_BILL_H
//#include "accesories.h"
#include "Book.h"


class Bill : public shop::Towar {
public:
    Bill() = default;

    shop::towar_int_t calculate(Towar &towar);

    void printBill(shop::Towar &towar);

    void payForPurchases();

private:
    shop::towar_int_t allGain;

};


#endif //MACHINEOFSTATE_BILL_H
