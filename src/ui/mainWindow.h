#ifndef SLEEPY_LOG_MAINWINDOW_H
#define SLEEPY_LOG_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDateTime>
#include <QFile>
#include <QHBoxLayout>
#include <QListWidget>


struct sleepDataStruct {
    int index;
    QString date;
    QString start;
    QString end;
    bool isEmpty;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

signals:
    void editModeEnabled(int index);

public slots:
    void onRowClicked(int index);
    void onEditModeDisabled();

private:
    void setupUI();
    void setupRowList();
    void setupHeaderWidget();
    void createSleepItem(sleepDataStruct &sleepItem);
    QVector<sleepDataStruct> loadSleepData(QString path);

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