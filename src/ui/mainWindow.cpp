#include "mainWindow.h"
#include <QHBoxLayout>
#include <QListWidget>
#include <QScrollBar>
#include <QDateTime>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "sleepRowWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupUI();
    loadSleepData();
}

MainWindow::~MainWindow() {
    saveSleepData();
}

void MainWindow::setupUI() {
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    mainWidget->setFixedSize(773, 711);
    mainWidget->setStyleSheet("background: #FFFFFF;");

    mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(sleepListWidget);

    this->show();
}

void MainWindow::createSleepItem(const sleepTime &sleepItem) {
    auto w = new SleepRowWidget(sleepItem.index, sleepItem.date, sleepItem.time, sleepItem.duration, mainWidget);
    sleepListWidget->addItem(w);
}

void MainWindow::loadSleepData() {

}

void MainWindow::saveSleepData() {

}