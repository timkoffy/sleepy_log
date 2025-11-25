#ifndef SLEEPY_LOG_MAINWINDOW_H
#define SLEEPY_LOG_MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QDateTime>
#include <QHBoxLayout>

class QListWidget;
class QWidget;

struct sleepTime {
    int index;
    QString date;
    QString start;
    QString duration;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool editMode;

private slots:
    void onRowClicked(int index);

private:
    void setupUI();
    void createSleepItem(sleepTime &sleepItem);
    void loadSleepData();

    QWidget *mainWidget;
    QVBoxLayout *mainLayout;
    QListWidget *sleepListWidget;

    int yearCurrent;

    QVector<sleepTime> sleepData;
};

#endif //SLEEPY_LOG_MAINWINDOW_H