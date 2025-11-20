#ifndef SLEEPY_LOG_SLEEPROWWIDGET_H
#define SLEEPY_LOG_SLEEPROWWIDGET_H

#include <QWidget>

class SleepRowWidget : public QWidget {
    Q_OBJECT
public:
    explicit SleepRowWidget(int index, QString& date, QString& time,
        QString& duration, QWidget *parent = nullptr);

signals:
    void rowClicked(int index);
    void rowHovered(int index, bool hovered);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    QWidget* progressBar;
    int rowIndex;
    bool isHovered;
    bool isSelected;

    QString start_time;

    QString _date;

    QString _time;
    float time_h;
    int _time_converted;

    QString _duration;
    float duration_h;
    int _duration_converted;

    QWidget* leftPart;
    QWidget* centerPart;
    QWidget* rightPart;

    float convertTime(QString time_local);
    void setupUI();
    void setupLeftPart();
    void setupCentral();
    void updateStyle();
    void calculateTimePositions();
    void saveSleepData();
};

#endif //SLEEPY_LOG_SLEEPROWWIDGET_H