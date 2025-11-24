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

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    sleepListWidget = new QListWidget();
    sleepListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    sleepListWidget->setStyleSheet("QListWidget { border: none; background: white; }");

    QDate currentDate = QDate::currentDate();
    QString dateString = currentDate.toString("yyyy.MM.dd");

    QDate date(currentDate.year(), 1, 1);
    for (int i = 0; i < 365; i++) {
        sleepTime t;
        t.date = date.toString("MM.dd");
        createSleepItem(t);
        date = date.addDays(1);
    }

    mainLayout->addWidget(sleepListWidget);

    this->show();
}

void MainWindow::createSleepItem(sleepTime &sleepItem) {
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(0, 27));

    SleepRowWidget* rowWidget = new SleepRowWidget(sleepItem.index, sleepItem.date, sleepItem.start, sleepItem.duration);
    sleepListWidget->addItem(item);
    sleepListWidget->setItemWidget(item, rowWidget);

    connect(rowWidget, &SleepRowWidget::rowClicked, this, &MainWindow::onRowClicked);
    connect(rowWidget, &SleepRowWidget::rowHovered, this, &MainWindow::onRowHovered);
}

void MainWindow::loadSleepData() {

}

void MainWindow::saveSleepData() {

}

void MainWindow::onRowClicked(int rowIndex) {
}

void MainWindow::onRowHovered(int rowIndex, bool hovered) {
}