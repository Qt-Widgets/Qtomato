#ifndef QTOMATO_H
#define QTOMATO_H

#include <QDialog>
#include <QTimer>
#include <QDebug>
#include <QTime>

namespace Ui {
class Qtomato;
}

class Qtomato : public QDialog
{
    Q_OBJECT

public:
    explicit Qtomato(QWidget *parent = 0);
    ~Qtomato();

private slots:
    void on_buttonPomodoro_clicked();
    void on_buttonShortBreak_clicked();
    void on_buttonLongBreak_clicked();
    void on_buttonStart_clicked();
    void on_buttonStop_clicked();
    void on_buttonReset_clicked();

    void processTimer();

private:
    Ui::Qtomato *ui;
    QTimer pomodoroTimer;
    QTimer threadTimer;
    qint64 pomodoroTimerElpsed;
};

#endif // QTOMATO_H
