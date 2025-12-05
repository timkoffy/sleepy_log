#include "sleepRowWidget.h"
#include <QHBoxLayout>
#include <QLabel>

SleepRowWidget::SleepRowWidget(int index, QString date, QString start,
        QString end, bool isEmpty, QWidget *parent)
        : QWidget(parent), rowIndex(index),
        _date(date), _start(start), _end(end), _isEmpty(isEmpty){
    setMouseTracking(true);
    regularBedTime = "23:00";
    regularWakeUpTime = "07:00";

    setupUI();
    setProgressBar(_start, _end);
}

void SleepRowWidget::setupUI() {
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // лево
    leftPart = new QWidget();
    leftPart->setFixedWidth(100);
    leftPart->setStyleSheet("background: #ECECEC;");

    // центр
    centerPart = new QWidget();
    centerPart->setStyleSheet("background: #FFFFFF;");

    // право
    rightPart = new QWidget();
    rightPart->setFixedWidth(100);
    rightPart->setStyleSheet("background: #ECECEC;");

    setupLeftPart();
    setupCentral();

    layout->addWidget(leftPart);
    layout->addWidget(centerPart);
    layout->addWidget(rightPart);
}

void SleepRowWidget::setupLeftPart() {
    leftLayout = new QHBoxLayout(leftPart);
    leftLayout->setContentsMargins(3, 3, 3, 3);
    leftLayout->setAlignment(Qt::AlignRight);

    dateLabel = new QLabel();
    dateLabel->setText(_date);
    dateLabel->setStyleSheet("color: #000000");
    dateLabel->setAlignment(Qt::AlignRight);

    leftLayout->addWidget(dateLabel);
}

void SleepRowWidget::setupCentral() {
    centerLayout = new QHBoxLayout(centerPart);
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->addSpacing(5);
    centerLayout->setAlignment(Qt::AlignLeft);

    progressBar = new QWidget();
    progressBar->setFixedWidth(end_px);
    progressBar->setStyleSheet("background: #667AFF");

    centerLayout->addWidget(progressBar);
}

void SleepRowWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    setProgressBar(_start, _end);
}

void SleepRowWidget::mousePressEvent(QMouseEvent *event) {
    if (!editMode) {
        updateStyle();
        emit rowClicked(rowIndex);
    }
    QWidget::mousePressEvent(event);
}

void SleepRowWidget::enterEvent(QEnterEvent *event) {
    if (!editMode) {
        isHovered = true;
        updateStyle();
    } QWidget::enterEvent(event);
}

void SleepRowWidget::leaveEvent(QEvent *event) {
    if (!editMode) {
        isHovered = false;
        updateStyle();
    } QWidget::leaveEvent(event);
}

void SleepRowWidget::updateStyle() {
    QString styleCentralBG = "background: #FFFFFF";
    QString styleSideBG = "background: #ECECEC";
    QString styleProgressBarBG = "background: #667AFF";

    if (editMode) {
        if (!isEdited) {
            styleProgressBarBG = "background: #BDC5F8";
        } else {
            styleCentralBG = "background: #F0F0F0";
            styleSideBG = "background: #DEDEDE";
            setupEditModeUI();
        }
    } else if (isHovered || isSelected) {
        styleCentralBG = "background: #F0F0F0";
        styleSideBG = "background: #DEDEDE";
    }

    progressBar->setStyleSheet(styleProgressBarBG);
    leftPart->setStyleSheet(styleSideBG);
    rightPart->setStyleSheet(styleSideBG);
    centerPart->setStyleSheet(styleCentralBG);
}

double SleepRowWidget::convertTime(QString time_local) {
    if ( time_local.length() == 0 ) return 0;
    int hours = QString(time_local[0]).toInt() * 10 + QString(time_local[1]).toInt();
    int minutes = QString(time_local[3]).toInt() * 10 + QString(time_local[4]).toInt();
    if (hours < 12) hours+=24;
    return hours+minutes/60.f;
}

void SleepRowWidget::setProgressBar(QString startLocal, QString endLocal) {
    start_h = convertTime(startLocal);
    end_h = convertTime(endLocal);

    if (centerPart) {
        const int LEFT_TIME = 12;
        const int VISIBLE_HOURS = 24;

        double pixelsPerHour = centerPart->width() / (double)VISIBLE_HOURS;

        double hoursFromStart = start_h - LEFT_TIME;
        start_px = pixelsPerHour * hoursFromStart;

        double hoursFromEnd = end_h - LEFT_TIME;
        end_px = pixelsPerHour * hoursFromEnd;

        if (progressBar) {
            int barWidth = end_px - start_px;
            int barPosition = start_px;

            progressBar->setFixedWidth(barWidth);
            centerLayout->setContentsMargins(barPosition, 0, 0, 0);
        }
    }
}

void SleepRowWidget::saveSleepData() {

}

void SleepRowWidget::onEditModeEnabled(int index) {
    editMode = true;
    if (editMode && index == rowIndex) {
        isEdited = true;
        if (_isEmpty) setProgressBar(regularBedTime, regularWakeUpTime);
    }
    updateStyle();
}

void SleepRowWidget::setupEditModeUI() {
    QLabel* editModeDurationLabel = new QLabel;
    QString editModeDurationText = QString::number(end_h-start_h, 'f', 1) + " ч";
    editModeDurationLabel->setText(editModeDurationText);
    QHBoxLayout* progressBarLayout = new QHBoxLayout(progressBar);
    progressBarLayout->setAlignment(Qt::AlignCenter);
    progressBarLayout->addWidget(editModeDurationLabel);

    deleteButton = new QPushButton("D");
    deleteButton->setFixedSize(27,27);
    deleteButton->setStyleSheet("color: #000000");
    connect(deleteButton, &QPushButton::clicked, this, &SleepRowWidget::onDeleteButtonClicked);

    cancelButton = new QPushButton("C");
    cancelButton->setFixedSize(27,27);
    cancelButton->setStyleSheet("color: #000000");
    connect(cancelButton, &QPushButton::clicked, this, &SleepRowWidget::onCancelButtonClicked);

    saveButton = new QPushButton("S");
    saveButton->setFixedSize(27,27);
    saveButton->setStyleSheet("color: #000000");
    connect(saveButton, &QPushButton::clicked, this, &SleepRowWidget::onSaveButtonClicked);

    centerLayout->addWidget(deleteButton);
    centerLayout->addWidget(cancelButton);
    centerLayout->addWidget(saveButton);
}

void SleepRowWidget::onDeleteButtonClicked() {

}

void SleepRowWidget::onCancelButtonClicked() {
    emit editModeDisabled();
}

void SleepRowWidget::onSaveButtonClicked() {

}