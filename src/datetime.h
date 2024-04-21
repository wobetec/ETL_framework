#pragma once

#include <ctime>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

class TimeDelta {
    private:
    public:
        time_t delta;
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
    public:
        time_t time;
        struct tm *local;
        DateTime();
        DateTime(int year, int month, int day, int hour=0, int minute=0, int second=0);
        DateTime(int i_time);
        DateTime(const std::string& datetimeString) { 
            const char* format = "%Y-%m-%d %H:%M:%S";
            std::istringstream ss(datetimeString.substr(0, 18));
            std::tm tm = {};
            ss >> std::get_time(&tm, format);
            time = std::mktime(&tm);
            local = std::localtime(&time);
        }

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
