#ifndef QTOMATO_H
#define QTOMATO_H

#include <QDialog>

namespace Ui {
class Qtomato;
}

class Qtomato : public QDialog
{
    Q_OBJECT

public:
    explicit Qtomato(QWidget *parent = 0);
    ~Qtomato();

private:
    Ui::Qtomato *ui;
};

#endif // QTOMATO_H
