
#pragma once

#include <chrono>

class TimeInfo
{
    typedef std::chrono::system_clock::time_point time_point;

public:
    TimeInfo();
    TimeInfo(long longTp);
    TimeInfo(const time_point &tp);
    void init(const time_point &tp);

    static long fromTimePointToLong(const time_point &tp);
    static time_point fromLongToTimePoint(const long longTp);

    int year() const;
    int month() const;
    int day() const;
    int hour() const;
    int min() const;
    int sec() const;
    
    long toLong() const;
    time_point toTimePoint() const;

    void print() const;

private:
    long mLongTp;

    int mYear;
    int mMonth;
    int mDay;
    int mHour;
    int mMinute;
    int mSecond;
};