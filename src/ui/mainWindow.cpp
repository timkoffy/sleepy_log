#include "mainWindow.h"
#include <QHBoxLayout>
#include <QListWidget>
#include <QDateTime>

#include "sleepRowWidget.h"
#include "../core/sleepDataManager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    currentDate = QDate::currentDate();
    sleepDataManager manager;
    sleepData = manager.loadSleepData("../data.json");
    setupUI();
}

void MainWindow::setupUI() {
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    setAttribute(Qt::WA_OpaquePaintEvent);

    mainWidget->setMinimumSize(600, 200);
    resize(900, 800);
    mainWidget->setStyleSheet("background: #FFFFFF;");

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

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
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(0);

    QWidget *leftHeaderPart = new QWidget(headerWidget);
    leftHeaderPart->setFixedWidth(100);
    leftHeaderPart->setStyleSheet("background: #ECECEC");

    QWidget *rightHeaderPart = new QWidget(headerWidget);
    rightHeaderPart->setFixedWidth(114);
    rightHeaderPart->setStyleSheet("background: #ECECEC");

    headerLayout->addWidget(leftHeaderPart);

    for (int i = 3; i < 27; i++) {
        QString text = QString::number(i);
        QString style = "color: #808080";
        if (i == 3) text = "";
        if (i > 12) text = QString::number(i - 12);
        if (i > 24) text = QString::number(i - 24);
        if (i == 11 || i == 19) style = "color: #000000";

        QLabel *label = new QLabel();
        label->setText(text);
        label->setStyleSheet(style);
        label->setAlignment(Qt::AlignLeft);
        label->setAlignment(Qt::AlignVCenter);
        headerLayout->addWidget(label);
    }

    headerLayout->addWidget(rightHeaderPart);
}