#include "TimeInfo.h"

#include <iostream>


TimeInfo::TimeInfo() {}

TimeInfo::TimeInfo(long longTp) {
    std::chrono::duration<long> duration(longTp);
    std::chrono::time_point<std::chrono::system_clock> tp(duration);
    init(tp);
}

TimeInfo::TimeInfo(const TimeInfo::time_point &tp) {
    init(tp);
}

int TimeInfo::year() const {
    return mYear;
}

int TimeInfo::month() const {
    return mMonth;
}

int TimeInfo::day() const {
    return mDay;
}

int TimeInfo::hour() const {
    return mHour;
}

int TimeInfo::min() const {
    return mMinute;
}

int TimeInfo::sec() const {
    return mSecond;
}

long TimeInfo::toLong() const {
    return mLongTp;
}

TimeInfo::time_point TimeInfo::toTimePoint() const {
    std::chrono::duration<long> duration(mLongTp);
    std::chrono::time_point<std::chrono::system_clock> result(duration);

    return result;
}

void TimeInfo::init(const TimeInfo::time_point &tp) {
    using namespace std::chrono;

    mLongTp = tp.time_since_epoch().count();

    time_t tt = system_clock::to_time_t(tp);
    tm local_tm = *localtime(&tt);

    mYear = local_tm.tm_year + 1900;
    mMonth = local_tm.tm_mon + 1;
    mDay = local_tm.tm_mday;

    mHour = local_tm.tm_hour;
    mMinute = local_tm.tm_min;
    mSecond = local_tm.tm_sec;

}

void TimeInfo::print() const {
    std::cout << mYear<< '-' << mMonth << '-' << mDay << ' ' 
              << mHour << ':' << mMinute << ':' << mSecond << std::endl;
}