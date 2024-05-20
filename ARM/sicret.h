#ifndef SICRET_H
#define SICRET_H

#include <QDialog>

namespace Ui {
class sicret;
}

class sicret : public QDialog {
    Q_OBJECT
public:
    explicit sicret(QWidget *parent = nullptr);
    ~sicret();
    QPoint p;

private:
    Ui::sicret *ui;
};

#endif // SICRET_H
