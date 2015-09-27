#include "qtomato.h"
#include "ui_qtomato.h"

Qtomato::Qtomato(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Qtomato)
{
    ui->setupUi(this);

    pomodoroTimerElpsed = 0;

    threadTimer.setInterval(1000);
    pomodoroTimer.setInterval(25*60*1000);

    connect(&threadTimer, SIGNAL(timeout()), this, SLOT(processTimer()));

    ui->buttonStart->setDisabled(true);
    ui->buttonStop->setDisabled(true);
    ui->buttonReset->setDisabled(true);

    processTimer();
    threadTimer.start();
}

Qtomato::~Qtomato()
{
    if(pomodoroTimer.isActive())
        pomodoroTimer.stop();

    if(threadTimer.isActive())
        threadTimer.stop();

    delete ui;
}

void Qtomato::on_buttonPomodoro_clicked()
{
    pomodoroTimer.start();

    ui->buttonStop->setEnabled(true);
    ui->buttonReset->setEnabled(true);
}

void Qtomato::on_buttonShortBreak_clicked()
{

}

void Qtomato::on_buttonLongBreak_clicked()
{

}

void Qtomato::on_buttonStart_clicked()
{
    pomodoroTimer.start(pomodoroTimerElpsed);
    ui->buttonStart->setDisabled(true);
    ui->buttonStop->setEnabled(true);
}

void Qtomato::on_buttonStop_clicked()
{
    if(pomodoroTimer.isActive())
    {
        pomodoroTimerElpsed = pomodoroTimer.remainingTime();
        pomodoroTimer.stop();

        ui->buttonStart->setEnabled(true);
        ui->buttonStop->setDisabled(true);
    }
}

void Qtomato::on_buttonReset_clicked()
{
    pomodoroTimer.stop();
    pomodoroTimerElpsed = 0;
    ui->time->setText("25:00");

    ui->buttonStart->setDisabled(true);
    ui->buttonStop->setDisabled(true);
    ui->buttonReset->setDisabled(true);
}

void Qtomato::processTimer()
{
    if(pomodoroTimer.isActive())
    {
        QString timeText = QDateTime::fromTime_t(pomodoroTimer.remainingTime()/1000)
                .toUTC().toString("mm:ss");
        ui->time->setText(timeText);
    }
}
