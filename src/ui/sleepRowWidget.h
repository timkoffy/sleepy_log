#ifndef SLEEPY_LOG_SLEEPROWWIDGET_H
#define SLEEPY_LOG_SLEEPROWWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

class SleepRowWidget : public QWidget {
    Q_OBJECT
public:
    explicit SleepRowWidget(int index, QString date, QString start,
        QString end, QWidget *parent = nullptr);
    void setProgressBar(QString startLocal, QString endLocal);

signals:
    void rowClicked(int index);
    void editModeDisabled();

protected:
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

public slots:
    void onEditModeEnabled(int index);

private:
    QWidget* leftPart;
    QWidget* centerPart;
    QWidget* rightPart;
    QWidget* progressBar;
    QLabel* dateLabel;

    QPushButton* deleteButton;
    QPushButton* cancelButton;
    QPushButton* saveButton;

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

    QString regularBedTime;
    QString regularWakeUpTime;

    float convertTime(QString time_local);
    void setupUI();
    void setupLeftPart();
    void setupCentral();
    void setupEditModeUI();
    void updateStyle();
    void saveSleepData();
    void onCancelButtonClicked();
};

#endif //SLEEPY_LOG_SLEEPROWWIDGET_H