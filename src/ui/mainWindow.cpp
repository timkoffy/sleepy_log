#include "mainWindow.h"
#include <QHBoxLayout>
#include <QListWidget>
#include <QDateTime>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QPainter>

#include "sleepRowWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    currentDate = QDate::currentDate();;
    sleepData = loadSleepData("../data.json");
    setupUI();
}

void MainWindow::setupUI() {
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    mainWidget->setMinimumSize(773, 711);
    mainWidget->setStyleSheet("background: #FFFFFF;");

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    headerWidget = new QWidget();
    headerWidget->setFixedHeight(27);

    setupHeaderWidget();

    sleepListWidget = new QListWidget();
    sleepListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    sleepListWidget->setStyleSheet("QListWidget { border: none; }");

    setupRowList();

    mainLayout->addWidget(headerWidget);
    mainLayout->addWidget(sleepListWidget);

    this->show();
}

void MainWindow::createSleepItem(sleepDataStruct &sleepItem) {
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(QSize(0, 27));

    SleepRowWidget* rowWidget = new SleepRowWidget(sleepItem.index, sleepItem.date, sleepItem.start, sleepItem.end, sleepItem.isEmpty);
    sleepListWidget->addItem(item);
    sleepListWidget->setItemWidget(item, rowWidget);

    connect(rowWidget, &SleepRowWidget::rowClicked, this, &MainWindow::onRowClicked);
    connect(rowWidget, &SleepRowWidget::editModeDisabled, this, &MainWindow::onEditModeDisabled);
    connect(this, &MainWindow::editModeEnabled, rowWidget, &SleepRowWidget::onEditModeEnabled);
}

void MainWindow::onRowClicked(int index) {
    if (!editMode) {
        editMode = true;
        emit editModeEnabled(index);
    }
}

void MainWindow::onEditModeDisabled() {
    editMode = false;
    sleepListWidget->clear();
    setupRowList();
}

QVector<sleepDataStruct> MainWindow::loadSleepData(QString path) {
    QVector<sleepDataStruct> sleepDataLocal;

    QJsonDocument doc;
    {
        QFile fin(path);
        fin.open(QIODevice::ReadOnly);
        QByteArray ba = fin.readAll();
        doc = QJsonDocument::fromJson(ba);
    }

    if (doc.isArray()) {
        QJsonArray arrayJson = doc.array();
        for (QJsonValue valueJson : arrayJson) {
            QJsonObject obj = valueJson.toObject();
            sleepDataStruct t;
            t.index = obj["index"].toInt();
            t.start = obj["start"].toString();
            t.end = obj["end"].toString();
            sleepDataLocal.append(t);
        }
    }

    return sleepDataLocal;
}

void MainWindow::setupRowList() {
    QDate date(currentDate.year(), 1, 1);
    int j = 0;
    for (int i = 0; i < 365; i++) {
        sleepDataStruct t;
        t.index = i;
        t.date = date.toString("MM.dd");
        t.isEmpty = true;
        if (j < sleepData.size() && sleepData[j].index == i) {
            t.start = sleepData[j].start;
            t.end = sleepData[j].end;
            t.isEmpty = false;
            j++;
        }
        createSleepItem(t);
        date = date.addDays(1);
    }
    sleepListWidget->scrollToItem(sleepListWidget->item(currentDate.dayOfYear()-1),
        QAbstractItemView::PositionAtCenter);
}

void MainWindow::setupHeaderWidget() {
    headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(100, 0, 114, 0);
    headerLayout->setSpacing(0);

    for (int i = 0; i < 24; i++) {
        QString text = QString::number(i);
        QString style = "color: #808080";
        if (i == 0) text = "12";
        if (i > 12) text = QString::number(i - 12);
        if (i == 11 || i == 19) style = "color: #000000";
        QLabel *label = new QLabel();
        label->setText(text);
        label->setStyleSheet(style);
        label->setAlignment(Qt::AlignLeft);
        label->setAlignment(Qt::AlignVCenter);
        headerLayout->addWidget(label);
    }
}