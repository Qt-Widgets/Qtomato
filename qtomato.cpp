#include "qtomato.h"
#include "ui_qtomato.h"

Qtomato::Qtomato(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Qtomato)
{
    ui->setupUi(this);

    pomodoroTimerElpsed = 0;

    threadTimer.setInterval(1000);

    connect(&threadTimer, SIGNAL(timeout()), this, SLOT(processTimer()));

    ui->buttonStart->setDisabled(true);
    ui->buttonStop->setDisabled(true);
    ui->buttonReset->setDisabled(true);

    trayIconMenu.addAction(QIcon(":/icon24"), "Pomodoro", this, SLOT(on_buttonPomodoro_clicked()));
    trayIconMenu.addAction(QIcon(":/break_short"), "Short Break", this, SLOT(on_buttonShortBreak_clicked()));
    trayIconMenu.addAction(QIcon(":/break_long"), "Long Break", this, SLOT(on_buttonLongBreak_clicked()));
    trayIconMenu.addSeparator();
    trayIconMenu.addAction(QIcon(":/quit"), "Quit", qApp, SLOT(quit()));

    trayIconMain = QIcon(":/icon24");
    trayIcon.setIcon(trayIconMain);
    trayIcon.setContextMenu(&trayIconMenu);
    trayIcon.show();

    connect(&trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(handleTrayActivationReason(QSystemTrayIcon::ActivationReason)));

    setWindowIcon(QIcon(":/icon48"));

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
    pomodoroTimer.setInterval(25*60*1000);
    pomodoroTimer.start();

    ui->buttonStop->setEnabled(true);
    ui->buttonReset->setEnabled(true);
}

void Qtomato::on_buttonShortBreak_clicked()
{
    pomodoroTimer.setInterval(5*60*1000);
    pomodoroTimer.start();

    ui->buttonStop->setEnabled(true);
    ui->buttonReset->setEnabled(true);
}

void Qtomato::on_buttonLongBreak_clicked()
{
    pomodoroTimer.setInterval(10*60*1000);
    pomodoroTimer.start();

    ui->buttonStop->setEnabled(true);
    ui->buttonReset->setEnabled(true);
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
        if(pomodoroTimer.remainingTime() <= 1000)
        {
            trayIcon.showMessage("QTomato", "Take a break!");
            return;
        }
        QString timeText = QDateTime::fromTime_t(pomodoroTimer.remainingTime()/1000)
                .toUTC().toString("mm:ss");
        ui->time->setText(timeText);
    }
}

void Qtomato::handleTrayActivationReason(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::DoubleClick:
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::MiddleClick:
        if(isHidden())
            //show();
            //raise();
            showNormal();
        else
            hide();
    default:
        ;
    }
}
