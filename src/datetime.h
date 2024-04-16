#pragma once

#include <ctime>
#include <string>
#include <iostream>

class TimeDelta {
    private:
        time_t delta;
    public:
        TimeDelta(int i_delta);
        
        int years();
        int months();
        int days();
        int hours();
        int minutes();
        int seconds();

        friend std::ostream& operator<<(std::ostream& os, const TimeDelta& obj);
};

class DateTime {
    private:
        time_t time;
        struct tm *local;
    public:
        DateTime();
        DateTime(int year, int month, int day, int hour=0, int minute=0, int second=0);
        DateTime(int i_time);

        int year();
        int month();
        int day();
        int hour();
        int minute();
        int second();

        void replace(int year = -1, int month = -1, int day = -1, int hour = -1, int minute = -1, int second = -1);

        std::string strftime() const;

        TimeDelta operator-(DateTime other);
        DateTime operator+(TimeDelta delta);

        bool operator<(DateTime other);
        bool operator>(DateTime other);
        bool operator<=(DateTime other);
        bool operator>=(DateTime other);
        bool operator==(DateTime other);
        bool operator!=(DateTime other);

        friend std::ostream& operator<<(std::ostream& os, const DateTime& obj);
};
