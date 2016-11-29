#include "timeinfo.h"

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

void TimeInfo::init(const TimeInfo::time_point &tp) {
    using namespace std::chrono;

    mLongTp = TimeInfo::fromTimePointToLong(tp);

    auto tt = system_clock::to_time_t(tp);
    tm local_tm = *localtime(&tt);

    mYear = local_tm.tm_year + 1900;
    mMonth = local_tm.tm_mon + 1;
    mDay = local_tm.tm_mday;

    mHour = local_tm.tm_hour;
    mMinute = local_tm.tm_min;
    mSecond = local_tm.tm_sec;
}

static long TimeInfo::fromTimePointToLong(const TimeInfo::time_point &tp) {
    auto tpMs = std::chrono::time_point_cast<std::chrono::milliseconds>(tp);
    auto sinceEpoch = tpMs.time_since_epoch();
    auto sinceEpochMs = std::chrono::duration_cast<std::chrono::milliseconds>(sinceEpoch);
    return sinceEpochMs.count();
}

static TimeInfo::time_point TimeInfo::fromLongToTimePoint(const long longTp) {
    std::chrono::milliseconds sinceEpochMs(longTp);
    return time_point(sinceEpochMs);
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
    return TimeInfo::fromLongToTimePoint(mLongTp);
}

void TimeInfo::print() const {
    std::cout << mYear<< '-' << mMonth << '-' << mDay << ' ' 
              << mHour << ':' << mMinute << ':' << mSecond << std::endl;
}