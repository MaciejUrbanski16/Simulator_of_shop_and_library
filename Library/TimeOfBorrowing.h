//
// Created by Admin on 22.02.2021.
//

#ifndef MACHINEOFSTATE_TIMEOFBORROWING_H
#define MACHINEOFSTATE_TIMEOFBORROWING_H

#include <ctime>
#include <ostream>

namespace library {

    class TimeOfBorrowing;

    class TimeLeft{

    public:
        TimeLeft() = default;
        TimeLeft(TimeOfBorrowing &t);
        TimeLeft(std::string timeAsString);



        int operator-(const TimeLeft &time1);

        //int operator -(const TimeOfBorrowing &time1);

        //to compare with deadline
        bool operator>(const TimeLeft &time1);
        bool operator<(const TimeLeft &time1);
        bool operator==(const TimeLeft &time);

        std::string getCurrentTimeAsString();

        std::string getTimeToGiveBack();

    private:
        void convertTimeFromStringToInts(const std::string &timeAsStrings);
        int days_,mons_,years_,hours_,mins_,secs_;
    };

    class TimeOfBorrowing {
    public:

        //Time was taken from ctime library because of  easiest way to access particular parts of time like days, month etc.
        //std::chrono is not so easy to use it in my need. I would have to convert these time to a type taken from ctime library.
        TimeOfBorrowing();
        TimeOfBorrowing(const TimeOfBorrowing &t);

       // int operator-(const TimeOfBorrowing &time1);

        //int operator -(const TimeOfBorrowing &time1);

        //to compare with deadline
        //bool operator>(const TimeOfBorrowing &time1);
       // bool operator<(const TimeOfBorrowing &time1);

        friend std::ostream &operator<<(std::ostream &out, const TimeOfBorrowing &time);

        std::string mday, mon, year, hour, min, sec;

        const std::string getCurrentTimeAsString();

        const std::string getTimeToGiveBack();


        std::vector<int> getTimeAsInts();

    private:
        std::tm *now_;
        std::vector<int> partsOfTime;
    };
}//end namespace library


#endif //MACHINEOFSTATE_TIMEOFBORROWING_H
