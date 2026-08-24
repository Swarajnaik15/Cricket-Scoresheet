#include "startmatch.h"
#include "ui_startmatch.h"

Startmatch::Startmatch( QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Startmatch)
{
    ui->setupUi(this);
}

Startmatch::~Startmatch()
{
    delete ui;
}


void Startmatch::on_pushButton_clicked()
{

}

