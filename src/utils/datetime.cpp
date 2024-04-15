#include "./datetime.h"

DateTime::DateTime() {
    time = std::time(0);
    local = localtime(&time);
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second) {
    local->tm_year = year - 1900;
    local->tm_mon = month - 1;
    local->tm_mday = day;
    local->tm_hour = hour;
    local->tm_min = minute;
    local->tm_sec = second;
    time = mktime(local);
}

DateTime::DateTime(int i_time) {
    this->time = i_time;
    local = localtime(&time);
}

std::string DateTime::strftime() {
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local);
    return std::string(buffer);
}

int DateTime::year() {
    return 1900 + local->tm_year;
}

int DateTime::month() {
    return 1 + local->tm_mon;
}

int DateTime::day() {
    return local->tm_mday;
}

int DateTime::hour() {
    return local->tm_hour;
}

int DateTime::minute() {
    return local->tm_min;
}

int DateTime::second() {
    return local->tm_sec;
}

void DateTime::replace(int year, int month, int day, int hour, int minute, int second) {
    if (year != -1) local->tm_year = year - 1900;
    if (month != -1) local->tm_mon = month - 1;
    if (day != -1) local->tm_mday = day;
    if (hour != -1) local->tm_hour = hour;
    if (minute != -1) local->tm_min = minute;
    if (second != -1) local->tm_sec = second;
    time = mktime(local);
}

TimeDelta DateTime::operator-(DateTime other) {
    return TimeDelta(time - other.time);
}

bool DateTime::operator<(DateTime other) {
    return time < other.time;
}

bool DateTime::operator>(DateTime other) {
    return time > other.time;
}

bool DateTime::operator<=(DateTime other) {
    return time <= other.time;
}

bool DateTime::operator>=(DateTime other) {
    return time >= other.time;
}

bool DateTime::operator==(DateTime other) {
    return time == other.time;
}

bool DateTime::operator!=(DateTime other) {
    return time != other.time;
}

DateTime DateTime::operator+(TimeDelta delta) {
    return DateTime(time + delta.seconds());
}

TimeDelta::TimeDelta(int i_delta) {
    delta = i_delta;
}

int TimeDelta::years() {
    return delta / 31536000;
}

int TimeDelta::months() {
    return delta / 2592000;
}

int TimeDelta::days() {
    return delta / 86400;
}

int TimeDelta::hours() {
    return delta / 3600;
}

int TimeDelta::minutes() {
    return delta / 60;
}

int TimeDelta::seconds() {
    return delta;
}
