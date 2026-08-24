#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "teamdata.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    TeamData Team_data;
    Team_data.setModal(true);
    Team_data.exec();
}


void MainWindow::on_pushButton_2_clicked()
{
    QApplication::quit();
}

