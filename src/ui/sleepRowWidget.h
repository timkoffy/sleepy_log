#ifndef SLEEPY_LOG_SLEEPROWWIDGET_H
#define SLEEPY_LOG_SLEEPROWWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>

class SleepRowWidget : public QWidget {
    Q_OBJECT
public:
    explicit SleepRowWidget(int index, QString date, QString start,
        QString end, QWidget *parent = nullptr);
    void setProgressBar(QString startLocal, QString endLocal);

signals:
    void rowClicked(int index);
    void rowHovered(int index, bool hovered);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

public slots:
    void onEditModeChanged(int index);

private:
    QWidget* leftPart;
    QWidget* centerPart;
    QWidget* rightPart;
    QWidget* progressBar;
    QLabel* dateLabel;

    QHBoxLayout* leftLayout;
    QHBoxLayout* centerLayout;

    int rowIndex;
    bool isHovered = false;
    bool isSelected = false;
    bool editMode = false;
    bool isEdited = false;

    QString _date;

    QString _start;
    float start_h;
    int start_px = 0;

    QString _end;
    float end_h;
    int end_px = 0;

    float convertTime(QString time_local);
    void setupUI();
    void setupLeftPart();
    void setupCentral();
    void setupEditModeUI();
    void updateStyle();
    void saveSleepData();
};

#endif //SLEEPY_LOG_SLEEPROWWIDGET_H