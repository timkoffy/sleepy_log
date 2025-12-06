#ifndef SLEEPY_LOG_SLEEPDATASTRUCT_H
#define SLEEPY_LOG_SLEEPDATASTRUCT_H

#include <QString>

struct sleepDataStruct {
    int index;
    QString date;
    QString start;
    QString end;
    bool isEmpty;
};

#endif //SLEEPY_LOG_SLEEPDATASTRUCT_H