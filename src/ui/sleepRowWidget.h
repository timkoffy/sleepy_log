#ifndef SLEEPY_LOG_SLEEPROWWIDGET_H
#define SLEEPY_LOG_SLEEPROWWIDGET_H

#include <QWidget>

class SleepRowWidget : public QWidget {
    Q_OBJECT
public:
    explicit SleepRowWidget(int index, const QString& date, const QString& time,
        int duration, QWidget *parent = nullptr);
    QString date;
    QString time;
    int duration;

signals:
    void rowClicked(int index);
    void rowHovered(int index, bool hovered);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    int rowIndex;
    bool isHovered;
    bool isSelected;

    QWidget* leftPart;
    QWidget* centerPart;
    QWidget* rightPart;

    void setupUI();
    void setupLeftPart();
    void setupCentral();
    void updateStyle();
};

#endif //SLEEPY_LOG_SLEEPROWWIDGET_H