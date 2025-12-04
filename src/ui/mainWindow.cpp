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
    editMode = false;
    loadSleepData();
    setupUI();
}

void MainWindow::setupUI() {
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    mainWidget->setMinimumSize(773, 711);
    mainWidget->setStyleSheet("background: #FFFFFF;");

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    sleepListWidget = new QListWidget();
    sleepListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    sleepListWidget->setStyleSheet("QListWidget { border: none; }");

    QDate currentDate = QDate::currentDate();
    QString dateString = currentDate.toString("yyyy.MM.dd");

    QDate date(currentDate.year(), 1, 1);
    int j = 0;
    for (int i = 0; i < 365; i++) {
        sleepTime t;
        t.index = i;
        t.date = date.toString("MM.dd");
        if (j < sleepData.size() && sleepData[j].index == i) {
            t.start = sleepData[j].start;
            t.duration = sleepData[j].duration;
            j++;
        }
        createSleepItem(t);
        date = date.addDays(1);
    }

    mainLayout->addWidget(sleepListWidget);

    this->show();
}

void MainWindow::createSleepItem(sleepTime &sleepItem) {
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(QSize(0, 27));

    SleepRowWidget* rowWidget = new SleepRowWidget(sleepItem.index, sleepItem.date, sleepItem.start, sleepItem.duration);
    sleepListWidget->addItem(item);
    sleepListWidget->setItemWidget(item, rowWidget);

    connect(rowWidget, &SleepRowWidget::rowClicked, this, &MainWindow::onRowClicked);
    connect(this, &MainWindow::editModeChanged, rowWidget, &SleepRowWidget::onEditModeChanged);
}

void MainWindow::onRowClicked(int index) {
    if (!editMode) {
        editMode = true;
        emit editModeChanged(index);
    }
}

void MainWindow::loadSleepData() {
    QJsonDocument doc;
    {
        QFile fin("../data.json");
        fin.open(QIODevice::ReadOnly);
        QByteArray ba = fin.readAll();
        doc = QJsonDocument::fromJson(ba);
    }

    if (doc.isArray()) {
        QJsonArray arrayJson = doc.array();
        for (QJsonValue valueJson : arrayJson) {
            QJsonObject obj = valueJson.toObject();
            sleepTime t;
            t.index = obj["index"].toInt();
            t.start = obj["start"].toString();
            t.duration = obj["duration"].toString();
            sleepData.append(t);
        }
    }
}