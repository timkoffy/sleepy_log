#include "mainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QScrollBar>
#include <QDateTime>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

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

    leftSideWidget = new QWidget;
    centralWidget = new QWidget;
    rightSideWidget = new QWidget;

    mainWidget->setFixedSize(773, 711);
    mainWidget->setStyleSheet("background: #FFFFFF;");

    leftSideWidget->setFixedWidth(100);
    leftSideWidget->setStyleSheet("background: #ECECEC");

    rightSideWidget->setFixedWidth(100);
    rightSideWidget->setStyleSheet("background: #ECECEC");

    mainLayout = new QHBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(leftSideWidget);
    mainLayout->addWidget(centralWidget, 1);
    mainLayout->addWidget(rightSideWidget);

    setupLeftSidebar();
    setupCentralArea();

    this->show();
}

void MainWindow::onItemClicked(QListWidgetItem *item) {

}

void MainWindow::createSleepRowItem(const sleepTime &sleep) {

}

void MainWindow::loadSleepData() {

}

void MainWindow::saveSleepData() {

}

void MainWindow::setupCentralArea() {

}

void MainWindow::setupLeftSidebar() {

}