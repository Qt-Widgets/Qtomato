#include "qtomato.h"
#include "ui_qtomato.h"

Qtomato::Qtomato(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Qtomato)
{
    ui->setupUi(this);
}

Qtomato::~Qtomato()
{
    delete ui;
}
