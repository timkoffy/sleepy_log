#include "sleepDataManager.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>

QVector<sleepDataStruct> sleepDataManager::loadSleepData(QString path) {
    QVector<sleepDataStruct> data;

    QJsonDocument doc;
    {
        QFile fin(path);
        fin.open(QIODevice::ReadOnly);
        QByteArray ba = fin.readAll();
        doc = QJsonDocument::fromJson(ba);
    }

    if (doc.isArray()) {
        QJsonArray arrayJson = doc.array();
        for (QJsonValue valueJson : arrayJson) {
            QJsonObject obj = valueJson.toObject();
            sleepDataStruct t;
            t.index = obj["index"].toInt();
            t.start = obj["start"].toString();
            t.end = obj["end"].toString();
            data.append(t);
        }
    }

    return data;
}

void sleepDataManager::saveSleepData(QVector<sleepDataStruct> data, QString path) {

}

double sleepDataManager::convertTime(QString time_local) {
    if ( time_local.length() == 0 ) return 0;
    int hours = QString(time_local[0]).toInt() * 10 + QString(time_local[1]).toInt();
    int minutes = QString(time_local[3]).toInt() * 10 + QString(time_local[4]).toInt();
    if (hours < 12) hours+=24;
    return hours+minutes/60.f;
}
