#include "sleepRowWidget.h"
#include <QHBoxLayout>

SleepRowWidget::SleepRowWidget(int index, QString& date, QString& time,
        QString& duration, QWidget *parent)
    : QWidget(parent), rowIndex(index), isHovered(false), _date(date), _time(time), _duration(duration) {

    setFixedHeight(27);
    setMouseTracking(true);
    start_time = "16:00";
    setupUI();
    calculateTimePositions();
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
    // soon
}

void SleepRowWidget::setupCentral() {
    QHBoxLayout *centerLayout = new QHBoxLayout(centerPart);
    centerLayout->setContentsMargins(_time_converted, 0, 0, 0);
    centerLayout->setAlignment(Qt::AlignLeft);

    progressBar = new QWidget();
    progressBar->setFixedWidth(_duration_converted);
    progressBar->setStyleSheet("background: #667AFF");

    centerLayout->addWidget(progressBar);
}

void SleepRowWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    calculateTimePositions(); // Пересчет при изменении размера
}

void SleepRowWidget::mousePressEvent(QMouseEvent *event) {
    // soon
}

void SleepRowWidget::enterEvent(QEnterEvent *event) {
    // soon
}

void SleepRowWidget::leaveEvent(QEvent *event) {
    // soon
}

void SleepRowWidget::updateStyle() {
    QString styleCentralBG = "background: #FFFFFF";
    QString styleSideBG = "background: #ECECEC";

    // if (isHovered || isSelected) {
    //     styleCentralBG = "background: #F0F0F0";
    //     styleSideBG = "background: #DEDEDE";
    // }

    leftPart->setStyleSheet(styleSideBG);
    rightPart->setStyleSheet(styleSideBG);
    centerPart->setStyleSheet(styleCentralBG);
}

float SleepRowWidget::convertTime(QString time_local) {
    int hours = QString(time_local[0]).toInt() * 10 + QString(time_local[1]).toInt();
    int minutes_raw = QString(time_local[3]).toInt() * 10 + QString(time_local[4]).toInt();
    int minutes_rounded = (minutes_raw + 7) / 15 * 15;

    if (minutes_rounded >= 60) {
        minutes_rounded = 0;
        hours++;
    }
    return hours+minutes_rounded/60.f;
};

void SleepRowWidget::calculateTimePositions() {
    time_h = convertTime(_time);
    duration_h = convertTime(_duration);
    int start_time_h = convertTime(start_time);

    if (centerPart) {
        const int VISIBLE_HOURS = 20;
        const int BASE_OFFSET = 100;

        float pixelsPerHour = centerPart->width() / (float)VISIBLE_HOURS;

        float hoursFromStart = time_h - start_time_h;
        _time_converted = pixelsPerHour * hoursFromStart + BASE_OFFSET;

        _duration_converted = pixelsPerHour * duration_h;

        if (progressBar) {
            int barWidth = qMax(10, qMin(centerPart->width(), (int)_duration_converted));
            int barPosition = qMax(0, qMin(centerPart->width() - barWidth, (int)_time_converted - BASE_OFFSET));

            progressBar->setFixedWidth(barWidth);

            QHBoxLayout* centerLayout = qobject_cast<QHBoxLayout*>(centerPart->layout());
            if (centerLayout) {
                centerLayout->setContentsMargins(barPosition, 0, 0, 0);
            }
        }
    }
}

void SleepRowWidget::saveSleepData() {

}
