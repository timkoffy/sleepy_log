#include "sleepRowWidget.h"
#include <QHBoxLayout>

SleepRowWidget::SleepRowWidget(int index, const QString& date, const QString& time,
        int duration, QWidget *parent)
    : QWidget(parent), rowIndex(index), isHovered(false) {

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

}

void SleepRowWidget::setupCentral() {
    QHBoxLayout *centerLayout = new QHBoxLayout(centerPart);
    centerLayout->setContentsMargins(5, 5, 5, 5);

    // Прогресс-бар для отображения длительности сна
    QWidget *progressBg = new QWidget();
    progressBg->setFixedHeight(12);
    progressBg->setStyleSheet("background: #D0D0D0; border-radius: 6px;");

    QHBoxLayout *progressLayout = new QHBoxLayout(progressBg);
    progressLayout->setContentsMargins(1, 1, 1, 1);

    QWidget *progressBar = new QWidget();
    int barWidth = qMax(10, duration / 10); // Регулируемая ширина
    progressBar->setFixedWidth(barWidth);
    progressBar->setStyleSheet("background: #4CAF50; border-radius: 5px;");

    progressLayout->addWidget(progressBar);
    progressLayout->addStretch();

    centerLayout->addWidget(progressBg);
}

void SleepRowWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit rowClicked(index);
    }
    QWidget::mousePressEvent(event);
}

void SleepRowWidget::enterEvent(QEnterEvent *event) {
    // soon
}

void SleepRowWidget::leaveEvent(QEvent *event) {
    // soon
}

void SleepRowWidget::updateStyle() {
    QString styleCentralBG = "background #FFFFFF";
    QString styleSideBG = "background #ECECEC";

    if (isHovered || isSelected) {
        styleCentralBG = "background #F0F0F0";
        styleSideBG = "background #DEDEDE";
    }

    leftPart->setStyleSheet(styleSideBG);
    rightPart->setStyleSheet(styleSideBG);
    centerPart->setStyleSheet(styleCentralBG);
}
