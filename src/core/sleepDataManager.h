#ifndef SLEEPY_LOG_SLEEPDATAMANAGER_H
#define SLEEPY_LOG_SLEEPDATAMANAGER_H

#include "sleepDataStruct.h"

class sleepDataManager {
public:
    QVector<sleepDataStruct> loadSleepData(QString path);
    void saveSleepData(QVector<sleepDataStruct> data, QString path);
    double convertTime(QString time_local);
};


#endif //SLEEPY_LOG_SLEEPDATAMANAGER_H