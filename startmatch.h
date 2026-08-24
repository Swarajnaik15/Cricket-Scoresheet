#ifndef STARTMATCH_H
#define STARTMATCH_H

#include <QDialog>
#include <QWidget>
#include <QString>

namespace Ui {
class Startmatch;

}

class Startmatch : public QDialog
{
    Q_OBJECT

public:
    explicit Startmatch(QWidget *parent = nullptr);
    ~Startmatch();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Startmatch *ui;
};

#endif // STARTMATCH_H
