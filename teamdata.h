#ifndef TEAMDATA_H
#define TEAMDATA_H

#include <QDialog>

namespace Ui {
class TeamData;
}

class TeamData : public QDialog
{
    Q_OBJECT

public:
    explicit TeamData(QWidget *parent = nullptr);

    ~TeamData();


public slots:
    void on_StartMatch_clicked();
    void show();
    void Runs(int r);
    void Change_Bowler();
    void Score_process(int r);
    void SwapInn();
    void Add();
    void Remove();
    void ShowInn2();
    void Result();
    void summery();
private slots:
    void on_next_1_clicked();

    void on_pushButton_10_clicked();

    void on_dot_clicked();

    void on_One_run_clicked();

    void on_Two_run_clicked();

    void on_Three_run_clicked();

    void on_Four_run_clicked();

    void on_Six_run_clicked();

    void on_Wide_clicked();

    void on_No_Ball_clicked();

    void on_Byes_clicked();

    void on_Leg_Byes_clicked();

    void on_pushButton_clicked();

    void on_Next_batsman_clicked();

    void on_Strike_Change_clicked();

    void on_Next_Inn_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::TeamData *ui;
};

#endif // TEAMDATA_H
