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
        QString end, bool isEmpty, QWidget *parent = nullptr);

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
    double start_h = 0;
    int start_px = 0;

    QString _end;
    double end_h = 0;
    int end_px = 0;

    bool _isEmpty;

    QString regularBedTime;
    QString regularWakeUpTime;

    void setupUI();
    void setupLeftPart();
    void setupCentral();
    void setupEditModeUI();
    void setupProgressBar(QString startLocal, QString endLocal);
    void updateStyle();

    void onCancelButtonClicked();
    void onDeleteButtonClicked();
    void onSaveButtonClicked();
};

#endif //SLEEPY_LOG_SLEEPROWWIDGET_H