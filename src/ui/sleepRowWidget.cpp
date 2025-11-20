#include "sleepRowWidget.h"
#include <QHBoxLayout>

SleepRowWidget::SleepRowWidget(int index, const QString& date, const QString& time,
        int duration, QWidget *parent)
    : QWidget(parent), rowIndex(index), isHovered(false), _duration(duration) {

    setFixedHeight(27);
    setMouseTracking(true);
    setupUI();
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
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->setAlignment(Qt::AlignLeft);

    QWidget *progressBar = new QWidget();
    progressBar->setFixedWidth(_duration);
    progressBar->setStyleSheet("background: #667AFF");

    centerLayout->addWidget(progressBar);
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

    if (isHovered || isSelected) {
        styleCentralBG = "background: #F0F0F0";
        styleSideBG = "background: #DEDEDE";
    }

    leftPart->setStyleSheet(styleSideBG);
    rightPart->setStyleSheet(styleSideBG);
    centerPart->setStyleSheet(styleCentralBG);
}
