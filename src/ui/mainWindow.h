#ifndef SLEEPY_LOG_MAINWINDOW_H
#define SLEEPY_LOG_MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QDateTime>
#include <QHBoxLayout>

class QListWidget;
class QWidget;

struct sleepTime {
    QDateTime startTime;
    QDateTime endTime;
    int duration;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onItemClicked(QListWidgetItem *item);
    void loadSleepData();

private:
    void setupUI();
    void setupLeftSidebar();
    void setupCentralArea();
    void createSleepRowItem(const sleepTime& sleep);
    void saveSleepData();

    QWidget *mainWidget;
    QWidget *leftSideWidget;
    QWidget *centralWidget;
    QWidget *rightSideWidget;
    QHBoxLayout *mainLayout;
    QListWidget *sleepListWidget;

    QVector<sleepTime> sleepData;
};

#endif //SLEEPY_LOG_MAINWINDOW_H