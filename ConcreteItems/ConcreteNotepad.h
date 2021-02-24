//
// Created by Admin on 19.02.2021.
//

#ifndef MACHINEOFSTATE_CONCRETENOTEPAD_H
#define MACHINEOFSTATE_CONCRETENOTEPAD_H

#include "../Managers/NotepadManager.h"

namespace shop {


    class ConcreteNotepad {
    public:
        ConcreteNotepad() = default;

        ConcreteNotepad(std::string &format, int numberOfCards, ware_t price);

        ~ConcreteNotepad() = default;
    private:
        std::string format_;
        int numberOfCards_;
        ware_t price_{};
    public:
        const std::string &getFormat() const;

        void setFormat(const std::string &dimension);

        int getNumberOfCards() const;

        void setNumberOfCards(int NumberOfCards);

        ware_t getPrice() const;

        void setPrice(ware_t price);

    };

}
#endif //MACHINEOFSTATE_CONCRETENOTEPAD_H
