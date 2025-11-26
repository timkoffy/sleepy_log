#include "sleepRowWidget.h"
#include <QHBoxLayout>
#include <QLabel>

SleepRowWidget::SleepRowWidget(int index, QString date, QString start,
        QString duration, QWidget *parent)
        : QWidget(parent), rowIndex(index), isHovered(false), isSelected(false), _date(date), _start(start), _duration(duration),
        _start_converted(0), _duration_converted(0), isEdited(false) {
    setMouseTracking(true);
    left_time = "12:00";

    setupUI();
    setProgressBar(_start, _duration);
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
    layout->addWidget(centerPart, 1);
    layout->addWidget(rightPart);

    updateStyle();

    this->show();
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
    centerLayout->setContentsMargins(_start_converted, 0, 0, 0);
    centerLayout->setAlignment(Qt::AlignLeft);

    progressBar = new QWidget();
    progressBar->setFixedWidth(_duration_converted);
    progressBar->setStyleSheet("background: #667AFF");

    centerLayout->addWidget(progressBar);
}

void SleepRowWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    setProgressBar(_start, _duration);
}

void SleepRowWidget::mousePressEvent(QMouseEvent *event) {
    if (!editMode) isSelected = !isSelected;
    updateStyle();

    emit rowClicked(rowIndex);

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

    if (editMode && !isEdited) {
        styleProgressBarBG = "background: #BDC5F8";
    } else if (isHovered || isSelected) {
        styleCentralBG = "background: #F0F0F0";
        styleSideBG = "background: #DEDEDE";
    }

    progressBar->setStyleSheet(styleProgressBarBG);
    leftPart->setStyleSheet(styleSideBG);
    rightPart->setStyleSheet(styleSideBG);
    centerPart->setStyleSheet(styleCentralBG);
}

float SleepRowWidget::convertTime(QString time_local) {
    if ( time_local.length() == 0 ) return 0;
    int hours = QString(time_local[0]).toInt() * 10 + QString(time_local[1]).toInt();
    int minutes_raw = QString(time_local[3]).toInt() * 10 + QString(time_local[4]).toInt();
    int minutes_rounded = (minutes_raw + 7) / 15 * 15;

    if (minutes_rounded >= 60) {
        minutes_rounded = 0;
        hours++;
    } return hours+minutes_rounded/60.f;
}

void SleepRowWidget::setProgressBar(QString startLocal, QString durationLocal) {
    start_h = convertTime(startLocal);
    duration_h = convertTime(durationLocal);
    int start_time_h = convertTime(left_time);

    if (centerPart) {
        const int VISIBLE_HOURS = 24;
        const int BASE_OFFSET = 100;

        float pixelsPerHour = centerPart->width() / (float)VISIBLE_HOURS;

        float hoursFromStart = start_h - start_time_h;
        _start_converted = pixelsPerHour * hoursFromStart + BASE_OFFSET;

        _duration_converted = pixelsPerHour * duration_h;

        if (progressBar) {
            int barWidth = _duration_converted;
            int barPosition = _start_converted - BASE_OFFSET;

            progressBar->setFixedWidth(barWidth);
            centerLayout->setContentsMargins(barPosition, 0, 0, 0);
        }
    }
}

void SleepRowWidget::saveSleepData() {

}

void SleepRowWidget::onEditModeChanged(int index) {
    editMode = true;
    if (index == rowIndex) {
        isEdited = true;
    }
    updateStyle();
}