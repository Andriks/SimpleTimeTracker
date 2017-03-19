#ifndef EVENTDRIVERCONFIGURATION_H
#define EVENTDRIVERCONFIGURATION_H

#include <QTime>

class EventDriverConfiguration
{
private:
    static const unsigned int DEFAULT_UPDATE_TIMEOUT_MS;
    static const unsigned int DEFAULT_AUTOSAVE_TIMEOUT_MS;
    static const unsigned int DEFAULT_MAX_IDLE_TIME_MS;
    static const QTime DEFAULT_TIME_TRACK_FROM;
    static const QTime DEFAULT_TIME_TRACK_TILL;

public:
    void readConfiguration();

    unsigned int getUpdateTimeoutMs();
    unsigned int getAutosaveTimeoutMs();
    unsigned int getMaksIdleTimeMs();
    bool isTrackedTime(QTime time);

private:
    unsigned int mUpdateTimeout;
    unsigned int mAutosaveTimeout;
    unsigned int mMaksIdleTime;
    QTime mTrackFrom;
    QTime mTrackTill;

};

#endif // EVENTDRIVERCONFIGURATION_H
