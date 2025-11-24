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
    ~MainWindow();

private slots:
    void onRowClicked(int index);
    void onRowHovered(int index, bool hovered);

private:
    void setupUI();
    void createSleepItem(sleepTime &sleepItem);
    void loadSleepData();
    void saveSleepData();

    QWidget *mainWidget;
    QVBoxLayout *mainLayout;
    QListWidget *sleepListWidget;

    int yearCurrent;

    QVector<sleepTime> sleepData;
};

#endif //SLEEPY_LOG_MAINWINDOW_H