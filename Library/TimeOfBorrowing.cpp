//
// Created by Admin on 22.02.2021.
//

#include <iostream>
#include <vector>
#include <sstream>
#include "TimeOfBorrowing.h"
#include "time.h"

namespace library {

    TimeOfBorrowing::TimeOfBorrowing() {

        //when creating instance -> keep time of creating
        std::time_t t = std::time(nullptr);   // get time now
        this->now_ = std::localtime(&t);

        this->now_->tm_year += 1900;
    }

    std::ostream &operator<<(std::ostream &out, const TimeOfBorrowing &time) {
        return out << time.now_->tm_mday << "." << time.now_->tm_mon << "." << time.now_->tm_year + 1900 << "  " <<
                   time.now_->tm_hour << ":" << time.now_->tm_min << ":" << time.now_->tm_sec << std::endl;
    }

    const std::string TimeOfBorrowing::getCurrentTimeAsString() {

        //preparing data of time to save an read it from file easily

        this->mday = std::to_string(now_->tm_mday);
        this->mon = std::to_string(now_->tm_mon);
        this->year = std::to_string(now_->tm_year);
        this->hour = std::to_string(now_->tm_hour);
        this->min = std::to_string(now_->tm_min);
        this->sec = std::to_string(now_->tm_sec);


        if (now_->tm_mday < 10) mday = "0" + std::to_string(now_->tm_mday);
        if (now_->tm_mon < 10) mon = "0" + std::to_string(now_->tm_mon);
        //if(now_->tm_year<10) year = std::to_string(now_->tm_year);
        if (now_->tm_hour < 10) hour = "0" + std::to_string(now_->tm_hour);
        if (now_->tm_min < 10) min = "0" + std::to_string(now_->tm_min);
        if (now_->tm_sec < 10) sec = "0" + std::to_string(now_->tm_sec);

        return mday + "." + mon + "." + year + "  " + hour + ":" + min + ":" + sec;
    }


    TimeOfBorrowing::TimeOfBorrowing(const TimeOfBorrowing &t) {
        this->now_ = t.now_;
    }

    std::vector<int> TimeOfBorrowing::getTimeAsInts() {

        this->partsOfTime.push_back(this->now_->tm_mday);
        this->partsOfTime.push_back(this->now_->tm_mon);
        this->partsOfTime.push_back(this->now_->tm_year);
        this->partsOfTime.push_back(this->now_->tm_hour);
        this->partsOfTime.push_back(this->now_->tm_min);
        this->partsOfTime.push_back(this->now_->tm_sec);

        return this->partsOfTime;
    }

    TimeLeft::TimeLeft(TimeOfBorrowing &t) {

        std::vector<int> tempTime = t.getTimeAsInts();


        this->days_ = tempTime[0];
        this->mons_ = tempTime[1];
        this->years_ = tempTime[2];
        this->hours_ = tempTime[3];
        this->mins_ = tempTime[4];
        this->secs_ = tempTime[5];
    }

    TimeLeft::TimeLeft(std::string timeAsStrings) {

        if(timeAsStrings.size() == 20){

            std::string temp;

            temp.push_back(char(timeAsStrings[0]));
            temp.push_back(char(timeAsStrings[1]));


            this->days_ = std::stoi(temp);

            temp.clear();

            temp.push_back(char(timeAsStrings[3]));
            temp.push_back(char(timeAsStrings[4]));

            this->mons_ = std::stoi(temp);

            temp.clear();

            temp.push_back(char(timeAsStrings[6]));
            temp.push_back(char(timeAsStrings[7]));
            temp.push_back(char(timeAsStrings[8]));
            temp.push_back(char(timeAsStrings[9]));

            this->years_ = std::stoi(temp);

            temp.clear();

            temp.push_back(char(timeAsStrings[12]));
            temp.push_back(char(timeAsStrings[13]));

            this->hours_ = std::stoi(temp);
            temp.clear();

            temp.push_back(char(timeAsStrings[15]));
            temp.push_back(char(timeAsStrings[16]));

            this->mins_ = std::stoi(temp);

            temp.clear();

            temp.push_back(char(timeAsStrings[18]));
            temp.push_back(char(timeAsStrings[19]));

            this->secs_ = std::stoi(temp);

            temp.clear();

        }
    }

    //TODO this operators
    int TimeLeft::operator-(const TimeLeft &time1) {

        return 0;
    }

    bool TimeLeft::operator>(const TimeLeft &time1) {

        if(this->years_ == time1.years_){
            int expiredDaysThis = this->mons_ * 30 + this->days_;
            int expiredDaysTime1 = time1.mons_ *30 + time1.days_;
            return expiredDaysThis < expiredDaysTime1;
        }
        else return this->years_ <= time1.years_;
    }

    bool TimeLeft::operator<(const TimeLeft &time1) {
        return !(*this < time1) && !(*this == time1);
    }


    bool TimeLeft::operator==(const TimeLeft &time) {
        return this->years_ == time.years_ && this->mons_ == time.mons_ && this->days_ == time.days_ &&
               this->hours_ == time.hours_ && this->mins_ == time.mins_ && this->secs_ == time.secs_;
    }

    std::string TimeLeft::getCurrentTimeAsString() {


        //preparing time to save to file

        std::string tempTimeAsString;

        if(this->days_ < 10) {
            tempTimeAsString += '0';
        }

        tempTimeAsString += std::to_string(this->days_);

        tempTimeAsString += '.';

        if(this->mons_ < 10) {
            tempTimeAsString += '0';
        }

        tempTimeAsString += std::to_string(this->mons_);

        tempTimeAsString += '.';

        tempTimeAsString += std::to_string(this->years_);

        tempTimeAsString += "  ";

        if(this->hours_ < 10) {
            tempTimeAsString += '0';
        }

        tempTimeAsString += std::to_string(this->hours_);

        tempTimeAsString += ':';

        if(this->mins_ < 10) {
            tempTimeAsString += '0';
        }

        tempTimeAsString += std::to_string(this->mins_);

        tempTimeAsString += ':';

        if(this->secs_ < 10) {
            tempTimeAsString += '0';
        }

        tempTimeAsString += std::to_string(this->secs_);


        return tempTimeAsString;
    }

    std::string TimeLeft::getTimeToGiveBack() {

        this->mons_ += 2;
        return this->getCurrentTimeAsString();
    }



}//end namespace library
