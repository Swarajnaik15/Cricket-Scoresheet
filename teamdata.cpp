#include "teamdata.h"
#include "ui_teamdata.h"
#include <qstring.h>
#include <QMessageBox>
#include<QDebug>
#include<stdbool.h>
#include <algorithm>
#include <QFrame>
#include <QPixmap>
#include<QString>
#include <QTabWidget>

TeamData::TeamData(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TeamData)
{
    ui->setupUi(this);
}

TeamData::~TeamData()
{
    delete ui;
}

struct Team_Data
{
    QString Player_Name;
    int Runs_Scored=0;
    int Ball_Faced=0;
    int Runs_Conc=0;
    int Balls_Bowled=0;
    int wicket_taken=0;
    bool Out;
    bool isBatting;
    bool isBowling;
    int Over_Bowl_by_player=0;
}A[11],B[11];

int i,bat1,bat2,bowl1=11;
int b1,b2,A1;
QString TeamA_Name;
QString TeamB_Name;
QString TeamA_Short;
QString teamB_Short;
QString Tover;
int Total_Overs_per_inn;

//int inn_1_score;
int inn_1_score =0;
int inn_1_extra=0;
int inn_1_wkt=0;
//int inn_2_score;
int inn_2_score =0;
int inn_2_extra=0;
int inn_2_wkt=0;

int inn_1_Overs=0;
int inn_2_Overs=0;
int ball_in_over=0;
int ball_in_over1=0;
bool Chase=false;
bool End=false;




void TeamData::on_StartMatch_clicked()    //Getting Team & Match Details
{
    A[0].Player_Name = ui-> PlayerA1 ->text();
    A[1].Player_Name = ui-> PlayerA2 ->text();
    A[2].Player_Name = ui-> PlayerA3 ->text();
    A[3].Player_Name = ui-> PlayerA4 ->text();
    A[4].Player_Name = ui-> PlayerA5 ->text();
    A[5].Player_Name = ui-> PlayerA6 ->text();
    A[6].Player_Name = ui-> PlayerA7 ->text();
    A[7].Player_Name = ui-> PlayerA8 ->text();
    A[8].Player_Name = ui-> PlayerA9 ->text();
    A[9].Player_Name = ui-> PlayerA10 ->text();
    A[10].Player_Name = ui-> PlayerA11 ->text();

    B[0].Player_Name = ui-> PlayerB1 ->text();
    B[1].Player_Name = ui-> PlayerB2 ->text();
    B[2].Player_Name = ui-> PlayerB3 ->text();
    B[3].Player_Name = ui-> PlayerB4 ->text();
    B[4].Player_Name = ui-> PlayerB5 ->text();
    B[5].Player_Name = ui-> PlayerB6 ->text();
    B[6].Player_Name = ui-> PlayerB7 ->text();
    B[7].Player_Name = ui-> PlayerB8 ->text();
    B[8].Player_Name = ui-> PlayerB9 ->text();
    B[9].Player_Name = ui-> PlayerB10 ->text();
    B[10].Player_Name = ui-> PlayerB11 ->text();

    TeamA_Name= ui-> TeamA ->text();
    TeamB_Name= ui-> TeamB ->text();
    TeamA_Short = ui-> TeamA_short -> text();
    teamB_Short = ui-> TeamB_short -> text();
    Tover = ui->OversPerInn ->currentText();
    Total_Overs_per_inn= Tover.toInt();

    if(  Total_Overs_per_inn==-1 ||TeamA_Name.isEmpty() || TeamB_Name.isEmpty() || TeamA_Short.isEmpty() || teamB_Short.isEmpty() || A[0].Player_Name.isEmpty() || A[1].Player_Name.isEmpty()|| A[2].Player_Name.isEmpty()|| A[3].Player_Name.isEmpty()|| A[4].Player_Name.isEmpty()|| A[5].Player_Name.isEmpty()|| A[6].Player_Name.isEmpty()|| A[7].Player_Name.isEmpty()|| A[8].Player_Name.isEmpty()|| A[9].Player_Name.isEmpty() || A[10].Player_Name.isEmpty() || B[0].Player_Name.isEmpty()|| B[1].Player_Name.isEmpty()|| B[2].Player_Name.isEmpty()|| B[3].Player_Name.isEmpty()|| B[4].Player_Name.isEmpty()|| B[5].Player_Name.isEmpty()|| B[6].Player_Name.isEmpty()|| B[7].Player_Name.isEmpty()|| B[8].Player_Name.isEmpty()|| B[9].Player_Name.isEmpty() || B[10].Player_Name.isEmpty()  ) {
        QMessageBox::warning(this, "Input Error", "Please fill all the Details.");
        return;
    }

    ui->stackedWidget->setCurrentIndex(1);
    Add();
}
void TeamData::Add()
{
    for(i=0;i<11;i++)
    {
        ui->firstbat->addItem(A[i].Player_Name);
        ui->secondbat->addItem(A[i].Player_Name);
        ui->bowler->addItem(B[i].Player_Name);
        ui->Batsman1->addItem(A[i].Player_Name);
    }
}

void total(){
    int player_total=0;
    for(int i=0;i<11;i++)
    {
        player_total = player_total + A[i].Runs_Scored;
    }
    inn_1_score=player_total + inn_1_extra;
}

void TeamData::on_next_1_clicked()
{
    bat1= ui->firstbat->currentIndex();
    bat2= ui->secondbat->currentIndex();
    A[bat1].isBatting=true;
    A[bat2].isBatting=true;
    if(bat1==bat2)
    {
        QMessageBox::warning(this, "Input Error", "Please Select Different Batsman");
        return;
    }
    ui->Scrore_process->setCurrentIndex(1);
}

void TeamData::show()
{
    total();
    ui->inn1_Bat_Name->setText(TeamA_Name);
    ui->inn1_Bowl_Name->setText(TeamB_Name);
    ui->inn1_runs->setText(QString("%1/%2").arg(inn_1_score).arg(inn_1_wkt));
    ui->inn1_striker->setText(A[bat1].Player_Name);
    ui->inn1_NonStriker->setText(A[bat2].Player_Name);
    ui->inn1_striker_run->setText(QString::number(A[bat1].Runs_Scored));
    ui->inn1_striker_bowl->setText(QString::number(A[bat1].Ball_Faced));
    ui->inn1_nonstriker_run->setText(QString::number(A[bat2].Runs_Scored));
    ui->inn1_nonStriker_bowl->setText(QString::number(A[bat2].Ball_Faced));
    ui->inn1_overs->setText(QString("Overs %1.%2(%3)").arg(inn_1_Overs).arg(ball_in_over).arg(Total_Overs_per_inn));
    ui->inn1_bowler->setText(B[bowl1].Player_Name);
    ui->inn1_bowler_run->setText(QString("%1/%2 (%3.%4)").arg(B[bowl1].Runs_Conc).arg(B[bowl1].wicket_taken).arg(B[bowl1].Over_Bowl_by_player).arg(ball_in_over));
  /*  if(inn_1_score>0 && (ball_in_over+inn_1_Overs)>0)
    {
        ui->inn1_RR->setText(QString("RR %1 ").arg((inn_1_score/(inn_1_Overs+ball_in_over))*6));
    }
*/
    ui->Wide->setChecked(false);
    ui->No_Ball->setChecked(false);
    ui->Byes->setChecked(false);
    ui->Leg_Byes->setChecked(false);
}
void TeamData::ShowInn2()
{
    ui->inn2_Bat_Name->setText(TeamB_Name);
    ui->inn2_Bowl_Name->setText(TeamA_Name);
    ui->inn2_runs->setText(QString("%1 / %2").arg(inn_2_score).arg(inn_2_wkt));
    ui->inn2_striker->setText(B[b1].Player_Name);
    ui->inn2_NonStriker->setText(B[b2].Player_Name);
    ui->inn2_striker_run->setText(QString::number(B[b1].Runs_Scored));
    ui->inn2_striker_bowl->setText(QString::number(B[b1].Ball_Faced));
    ui->inn2_nonstriker_run->setText(QString::number(B[b2].Runs_Scored));
    ui->inn2_nonStriker_bowl->setText(QString::number(B[b2].Ball_Faced));
    ui->inn2_overs->setText(QString("Overs %1.%2 (%3)").arg(inn_2_Overs).arg(ball_in_over1).arg(Total_Overs_per_inn));
    ui->inn2_bowler->setText(A[A1].Player_Name);
    ui->inn2_bowler_run->setText(QString("%1/%2 (%3.%4)").arg(A[A1].Runs_Conc).arg(A[A1].wicket_taken).arg(A[A1].Over_Bowl_by_player).arg(ball_in_over1));
   // ui->inn2_RR->setText(QString("RR %1 ").arg((inn_2_score/(inn_2_Overs+ball_in_over1))*6));
}

void swap()
{   int c=bat1;
    bat1=bat2;
    bat2=c;
}

void TeamData::on_pushButton_10_clicked()
{  if(bowl1==ui->bowler->currentIndex())
    //if(B[bowl1].isBowling==true)
    {
        QMessageBox::warning(this, "Input Error", "Please Select Different Bowler");
        return;
    }
    bowl1=ui->bowler->currentIndex();
    ui->Scrore_process->setCurrentIndex(2);
    B[bowl1].isBowling=true;
    show();
}

void ball()
{
    B[bowl1].Balls_Bowled++;
    ball_in_over++;
    A[bat1].Ball_Faced++;
}

void Run(int r,int e)
{
    A[bat1].Runs_Scored += r;
    inn_1_extra +=e;
}

void wide_ball()
{
    B[bowl1].Balls_Bowled--;
    inn_1_extra++;
    A[bat1].Ball_Faced--;
    ball_in_over--;
    B[bowl1].Runs_Conc++;
}

void No_ball()
{
    B[bowl1].Balls_Bowled--;
    inn_1_extra++;
    ball_in_over--;
    B[bowl1].Runs_Conc++;
}
void TeamData::Runs(int s)
{
    if(ui->Wide->isChecked())
    {
        wide_ball();
        Run(0,s);
    }else if(ui->No_Ball->isChecked())
    {
        No_ball();
        if(ui->Byes->isChecked() || ui->Leg_Byes->isChecked())
        {
            Run(0,s);
        }else{
            Run(s,0);
        }
    }else if(ui->Byes->isChecked() || ui->Leg_Byes->isChecked())
    {
        Run(0,s);
    }
    else{
        Run(s,0);
    }
    B[bowl1].Runs_Conc+=s;
}

void TeamData::Change_Bowler()
{
    if(ball_in_over % 6 == 0)
    {
        ball_in_over=0;
        B[bowl1].Over_Bowl_by_player++;
        inn_1_Overs++;
        if(inn_1_Overs==Total_Overs_per_inn || inn_1_wkt==10 || (inn_1_score>inn_2_score && Chase==true))
        {
          Result();
        }else
          {ui->Scrore_process->setCurrentIndex(1);
            swap();
           }
    }
}
void TeamData::Result(){
    if(inn_1_Overs==Total_Overs_per_inn || inn_1_wkt==10 || (inn_1_score>inn_2_score && Chase==true))
    {
        // if(ball_in_over1==0 && inn_2_Overs==0 && inn_2_score==0)
        if(Chase==false)
        {
            SwapInn();
            Chase=true;
            ui->Scrore_process->setCurrentIndex(0);
            QMessageBox::warning(this, "End Of Inning", QString("inn 1 Score: %1 : %2/%3 \n%4 Needs %5 Runs In %6 balls to Win The Match").arg(TeamB_Name).arg(inn_2_score).arg(inn_2_wkt).arg(TeamA_Name).arg(inn_2_score+1).arg(Total_Overs_per_inn*6));
        }else if(Chase==true && inn_1_score>inn_2_score)
        {   End=true;
            QMessageBox::warning(this, "End Of Match", QString("%1 Win the Match By %2 Wickets.").arg(TeamA_Name).arg(10-inn_1_wkt));
            ui->Wid2->setCurrentIndex(1);
            QString Res= QString("%1 Win the Match By %2 Wickets.").arg(TeamA_Name).arg(10-inn_1_wkt);
            ui->Final_Result->setText(Res);
            summery();

        }else
        {   End=true;
            QMessageBox::warning(this, "End Of Match", QString("%1 Win the Match By %2 Runs.").arg(TeamB_Name).arg(inn_2_score-inn_1_score));
            ui->Wid2->setCurrentIndex(1);
            QString Res= QString("%1 Win the Match By %2 Runs.").arg(TeamB_Name).arg(inn_2_score-inn_1_score);
            ui->Final_Result->setText(Res);
            summery();

        }
        ui->stackedWidget_2->setCurrentIndex(0);


    }
}
void TeamData::Score_process(int s)
{
    ball();
    Runs(s);
    if(s%2!=0)
    {
    swap();
    }
    show();
    Result();
    Change_Bowler();
}

void TeamData::on_dot_clicked()
{
    Score_process(0);
}


void TeamData::on_One_run_clicked()
{
    //ui->ss->setStyleSheet("background: url(:/h.png) no-repeat center center; background-size: cover; ");
    Score_process(1);
}

void TeamData::on_Two_run_clicked()
{
   Score_process(2);
}

void TeamData::on_Three_run_clicked()
{
    Score_process(3);
}

void TeamData::on_Four_run_clicked()
{
    Score_process(4);
}

void TeamData::on_Six_run_clicked()
{
    Score_process(6);
}


void TeamData::on_Wide_clicked()
{
    ui->No_Ball->setChecked(false);
    ui->Byes->setChecked(false);
    ui->Leg_Byes->setChecked(false);
}


void TeamData::on_No_Ball_clicked()
{
    ui->Wide->setChecked(false);
}


void TeamData::on_Byes_clicked()
{
    ui->Leg_Byes->setChecked(false);
    ui->Wide->setChecked(false);
}


void TeamData::on_Leg_Byes_clicked()
{
     ui->Wide->setChecked(false);
    ui->Byes->setChecked(false);
}


void TeamData::on_pushButton_clicked()
{
    A[bat1].Ball_Faced++;
    A[bat1].Out=true;
    //B[bowl1].wicket_taken++;
    ball_in_over++;
    inn_1_wkt++;

    show();
    ui->Scrore_process->setCurrentIndex(3);

}


void TeamData::on_Next_batsman_clicked()
{   //if(bat1==ui->Batsman1->currentIndex())
    if(A[ui->Batsman1->currentIndex()].isBatting==true)
    {
        QMessageBox::warning(this, "Input Error", "Please Select Different Batsman");
        return;
    }
    //up:
    if(ui->Run_Out->isChecked() || ui->Bowled->isChecked())
    {   //QString r=ui->Runout_Run->currentText();
        int ro= ui->Runout_Run->currentText().toInt();
        if(ui->Bowled->isChecked())
        {
            B[bowl1].wicket_taken++;
        }
        if(ui->Run_Out->isChecked())
        {
            A[bat1].Runs_Scored+=ro;
        }
    }
    else
    {
        QMessageBox::warning(this, "Input Error", "Please Fill Wicket Details");
        return;
    }

    bat1=ui->Batsman1->currentIndex();
    A[bat1].isBatting=true;
    show();
    ui->Scrore_process->setCurrentIndex(2);
    Change_Bowler();
}

void TeamData::on_Strike_Change_clicked()
{
    swap();
    show();
}

void swapTeams(Team_Data A[], Team_Data B[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::swap(A[i], B[i]);
    }

}
void TeamData::Remove()
{   for(int i = 0; i < 11 ;i++)
    {
    /*ui->firstbat->setItemText(index, "New Player Name");
    ui->firstbat->removeItem(i);
    ui->secondbat->removeItem(i);
    ui->bowler->removeItem(i);
    ui->Batsman1->removeItem(i);
*/
        ui->firstbat->setItemText(i,A[i].Player_Name);
        ui->secondbat->setItemText(i,A[i].Player_Name);
        ui->bowler->setItemText(i,B[i].Player_Name);
        ui->Batsman1->setItemText(i,A[i].Player_Name);
    }
}
void TeamData::SwapInn()
{
    swapTeams(A,B,i);
    b1=bat1;
    b2=bat2;
    A1=bowl1;
    bowl1=11;

    std::swap(ball_in_over,ball_in_over1);
    std::swap(inn_1_score, inn_2_score);
    std::swap(inn_1_extra, inn_2_extra);
    std::swap(inn_1_wkt, inn_2_wkt);
    std::swap(inn_1_Overs, inn_2_Overs);
    std::swap(TeamA_Name,TeamB_Name);
    std::swap(TeamA_Short,teamB_Short);
    Remove();
    ShowInn2();
    //ui->Scrore_process->setCurrentIndex(0);
}

void TeamData::on_Next_Inn_clicked()
{
    SwapInn();
    ui->Scrore_process->setCurrentIndex(0);
}


void TeamData::on_pushButton_2_clicked()
{
    QApplication::quit();
}

void TeamData::on_pushButton_3_clicked()
{
    summery();
    ui->Wid2->setCurrentIndex(1);
    ui->stackedWidget_2->setCurrentIndex(1);

}

void TeamData::summery()
{


    if(Chase==true)
    {
        ui->Final_Sheet->setTabText(0,"INNING 2");
        ui->Final_Sheet->setTabText(1,"INNING 1");
    }
    ui->A1Name->setText(QString("        %1").arg(A[0].Player_Name));
    ui->A2Name->setText(QString("        %1").arg(A[1].Player_Name));
    ui->A3Name->setText(QString("        %1").arg(A[2].Player_Name));
    ui->A4Name->setText(QString("        %1").arg(A[3].Player_Name));
    ui->A5Name->setText(QString("        %1").arg(A[4].Player_Name));
    ui->A6Name->setText(QString("        %1").arg(A[5].Player_Name));
    ui->A7Name->setText(QString("        %1").arg(A[6].Player_Name));
    ui->A8Name->setText(QString("        %1").arg(A[7].Player_Name));
    ui->A9Name->setText(QString("        %1").arg(A[8].Player_Name));
    ui->A10Name->setText(QString("        %1").arg(A[9].Player_Name));
    ui->A11Name->setText(QString("        %1").arg(A[10].Player_Name));

    if(A[0].isBatting==true){ui->A1R->setText(QString::number(A[0].Runs_Scored)); ui->A1B->setText(QString("  %1 ").arg(A[0].Ball_Faced));}
    if(A[1].isBatting==true){ui->A2R->setText(QString::number(A[1].Runs_Scored)); ui->A2B->setText(QString("  %1 ").arg(A[1].Ball_Faced));}
    if(A[2].isBatting==true){ui->A3R->setText(QString::number(A[2].Runs_Scored)); ui->A3B->setText(QString("  %1 ").arg(A[2].Ball_Faced));}
    if(A[3].isBatting==true){ui->A4R->setText(QString::number(A[3].Runs_Scored)); ui->A4B->setText(QString("  %1 ").arg(A[3].Ball_Faced));}
    if(A[4].isBatting==true){ui->A5R->setText(QString::number(A[4].Runs_Scored)); ui->A5B->setText(QString("  %1 ").arg(A[4].Ball_Faced));}
    if(A[5].isBatting==true){ui->A6R->setText(QString::number(A[5].Runs_Scored)); ui->A6B->setText(QString("  %1 ").arg(A[5].Ball_Faced));}
    if(A[6].isBatting==true){ui->A7R->setText(QString::number(A[6].Runs_Scored)); ui->A7B->setText(QString("  %1 ").arg(A[6].Ball_Faced));}
    if(A[7].isBatting==true){ui->A8R->setText(QString::number(A[7].Runs_Scored)); ui->A8B->setText(QString("  %1 ").arg(A[7].Ball_Faced));}
    if(A[8].isBatting==true){ui->A9R->setText(QString::number(A[8].Runs_Scored)); ui->A9B->setText(QString("  %1 ").arg(A[8].Ball_Faced));}
    if(A[9].isBatting==true){ui->A10R->setText(QString::number(A[9].Runs_Scored)); ui->A10B->setText(QString("  %1 ").arg(A[9].Ball_Faced));}
    if(A[10].isBatting==true){ui->A11R->setText(QString::number(A[10].Runs_Scored)); ui->A11B->setText(QString("  %1 ").arg(A[10].Ball_Faced));}


    ui->Bowl_info->clear();
    ui->Bowl_info->append("             BOWLING STATS            \n");
    QString header = QString("%1%2%3%4")
                         .arg("PLAYER NAME", -15)
                         .arg("Overs", -10)
                         .arg("Wickets", -10)
                         .arg("Runs", -10);
    ui->Bowl_info->append(header);

    for (int i = 0; i < 11; i++) {
        if (B[i].isBowling) {
            if(i==bowl1)
            {
                QString line2 = QString("%1%2.%3%4%5")
                .arg(B[i].Player_Name, -15)  // Player name, left-aligned
                    .arg(B[i].Over_Bowl_by_player)
                    .arg(ball_in_over,-10)                // Overs, left-aligned
                    .arg(B[i].wicket_taken, -10)  // Wickets, left-aligned
                    .arg(B[i].Runs_Conc, -10);  // Runs, left-aligned
                ui->Bowl_info->append(line2);
            }else{
            QString line2 = QString("%1%2%3%4")
            .arg(B[i].Player_Name, -15)  // Player name, left-aligned
                .arg(B[i].Over_Bowl_by_player, -12)  // Overs, left-aligned
                .arg(B[i].wicket_taken, -10)  // Wickets, left-aligned
                .arg(B[i].Runs_Conc, -10);  // Runs, left-aligned
            ui->Bowl_info->append(line2);
            }
        }
    }

    ui->Final_teamA->setText(TeamA_Short);
    ui->Final_Inn1R->setText(QString("%1/%2").arg(inn_1_score).arg(inn_1_wkt));
    ui->Final_Inn1O->setText(QString("%1.%2").arg(inn_1_Overs).arg(ball_in_over));

    ui->A1Name_2->setText(QString("        %1").arg(B[0].Player_Name));
    ui->A2Name_2->setText(QString("        %1").arg(B[1].Player_Name));
    ui->A3Name_2->setText(QString("        %1").arg(B[2].Player_Name));
    ui->A4Name_2->setText(QString("        %1").arg(B[3].Player_Name));
    ui->A5Name_2->setText(QString("        %1").arg(B[4].Player_Name));
    ui->A6Name_2->setText(QString("        %1").arg(B[5].Player_Name));
    ui->A7Name_2->setText(QString("        %1").arg(B[6].Player_Name));
    ui->A8Name_2->setText(QString("        %1").arg(B[7].Player_Name));
    ui->A9Name_2->setText(QString("        %1").arg(B[8].Player_Name));
    ui->A10Name_2->setText(QString("        %1").arg(B[9].Player_Name));
    ui->A11Name_2->setText(QString("        %1").arg(B[10].Player_Name));

    if(B[0].isBatting==true){ui->A1R_2->setText(QString::number(B[0].Runs_Scored)); ui->A1B_2->setText(QString("  %1 ").arg(B[0].Ball_Faced));}
    if(B[1].isBatting==true){ui->A2R_2->setText(QString::number(B[1].Runs_Scored)); ui->A2B_2->setText(QString("  %1 ").arg(B[1].Ball_Faced));}
    if(B[2].isBatting==true){ui->A3R_2->setText(QString::number(B[2].Runs_Scored)); ui->A3B_2->setText(QString("  %1 ").arg(B[2].Ball_Faced));}
    if(B[3].isBatting==true){ui->A4R_2->setText(QString::number(B[3].Runs_Scored)); ui->A4B_2->setText(QString("  %1 ").arg(B[3].Ball_Faced));}
    if(B[4].isBatting==true){ui->A5R_2->setText(QString::number(B[4].Runs_Scored)); ui->A5B_2->setText(QString("  %1 ").arg(B[4].Ball_Faced));}
    if(B[5].isBatting==true){ui->A6R_2->setText(QString::number(B[5].Runs_Scored)); ui->A6B_2->setText(QString("  %1 ").arg(B[5].Ball_Faced));}
    if(B[6].isBatting==true){ui->A7R_2->setText(QString::number(B[6].Runs_Scored)); ui->A7B_2->setText(QString("  %1 ").arg(B[6].Ball_Faced));}
    if(B[7].isBatting==true){ui->A8R_2->setText(QString::number(B[7].Runs_Scored)); ui->A8B_2->setText(QString("  %1 ").arg(B[7].Ball_Faced));}
    if(B[8].isBatting==true){ui->A9R_2->setText(QString::number(B[8].Runs_Scored)); ui->A9B_2->setText(QString("  %1 ").arg(B[8].Ball_Faced));}
    if(B[9].isBatting==true){ui->A10R_2->setText(QString::number(B[9].Runs_Scored)); ui->A10B_2->setText(QString("  %1 ").arg(B[9].Ball_Faced));}
    if(B[10].isBatting==true){ui->A11R_2->setText(QString::number(B[10].Runs_Scored)); ui->A11B_2->setText(QString("  %1 ").arg(B[10].Ball_Faced));}

    /*ui->Bowl_info->append()*/
    ui->Bowl_info_2->clear();
    ui->Bowl_info_2->append("             BOWLING STATS            \n");
    QString header_2 = QString("%1%2%3%4")
                         .arg("PLAYER NAME", -15)
                         .arg("Overs", -10)
                         .arg("Wickets", -10)
                         .arg("Runs", -10);
    ui->Bowl_info_2->append(header_2);

    for (int i = 0; i < 11; i++) {
        if (A[i].isBowling) {
            if(i==A1)
            {
                QString line2 = QString("%1%2.%3%4%5")
                .arg(A[i].Player_Name, -15)  // Player name, left-aligned
                    .arg(A[i].Over_Bowl_by_player)
                    .arg(ball_in_over1,-10)                // Overs, left-aligned
                    .arg(A[i].wicket_taken, -10)  // Wickets, left-aligned
                    .arg(A[i].Runs_Conc, -10);  // Runs, left-aligned
                ui->Bowl_info_2->append(line2);
            }else{
            QString line_2 = QString("%1%2%3%4")
            .arg(A[i].Player_Name, -15)  // Player name, left-aligned
                .arg(A[i].Over_Bowl_by_player, -12)  // Overs, left-aligned
                .arg(A[i].wicket_taken, -10)  // Wickets, left-aligned
                .arg(A[i].Runs_Conc, -10);  // Runs, left-aligned
            ui->Bowl_info_2->append(line_2);
            }
        }
    }

    ui->Final_teamA_2->setText(teamB_Short);
    ui->Final_Inn1R_2->setText(QString("%1/%2").arg(inn_2_score).arg(inn_2_wkt));
    ui->Final_Inn1O_2->setText(QString("%1.%2").arg(inn_2_Overs).arg(ball_in_over1));

}

void TeamData::on_pushButton_4_clicked()
{
     ui->Wid2->setCurrentIndex(0);
}

