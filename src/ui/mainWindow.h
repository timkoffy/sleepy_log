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
    QString end;
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
    void createSleepItem(sleepTime &sleepItem);
    void loadSleepData();

    QWidget *mainWidget;
    QVBoxLayout *mainLayout;
    QListWidget *sleepListWidget;

    QDate currentDate;
    bool editMode = false;

    QVector<sleepTime> sleepData;
};

#endif //SLEEPY_LOG_MAINWINDOW_H