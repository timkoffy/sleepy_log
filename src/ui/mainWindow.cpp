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

    sleepListLayout = new QVBoxLayout;
    sleepListLayout->setContentsMargins(0, 0, 0, 0);
    sleepListLayout->setSpacing(0);

    srand(2190129);
    for (int i = 0; i < 20; i++) {
        sleepTime t;
        t.index = 0;
        t.date = "12/11/2025";
        t.time = "12:10";
        t.duration = rand()%300;
        qDebug() << t.duration;
        createSleepItem(t);
    }

    mainLayout->addLayout(sleepListLayout);

    this->show();
}

void MainWindow::createSleepItem(const sleepTime &sleepItem) {
    auto w = new SleepRowWidget(sleepItem.index, sleepItem.date, sleepItem.time, sleepItem.duration, mainWidget);
    connect(w, &SleepRowWidget::rowClicked, this, &MainWindow::onRowClicked);
    connect(w, &SleepRowWidget::rowHovered, this, &MainWindow::onRowHovered);
    sleepListLayout->addWidget(w);
}

void MainWindow::loadSleepData() {

}

void MainWindow::saveSleepData() {

}

void MainWindow::onRowClicked(int rowIndex) {
}

void MainWindow::onRowHovered(int rowIndex, bool hovered) {
}