#ifndef SLEEPY_LOG_MAINWINDOW_H
#define SLEEPY_LOG_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDateTime>
#include <QFile>
#include <QHBoxLayout>
#include <QListWidget>

#include "../data/sleepDataStruct.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

signals:
    void editModeEnabled(int index);

public slots:
    void onRowClicked(int index);
    void onEditModeDisabled(int index);

private:
    void setupUI();
    void setupRowList();
    void setupHeaderWidget();
    void createSleepItem(sleepDataStruct &sleepItem);

    QWidget *mainWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *headerLayout;
    QWidget *headerWidget;
    QListWidget *sleepListWidget;

    QDate currentDate;
    bool editMode = false;

    QVector<sleepDataStruct> sleepData;
};

#endif //SLEEPY_LOG_MAINWINDOW_H