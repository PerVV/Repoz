#include "mainwindow.h"
#include "ui_mainwindow.h"


#define PATH ("C:\\Qt\\Mp_Pract\\00.dot")
#define BUF ("C:\\Qt\\Mp_Pract\\buffer.txt")
#define SORT_AUTO ("C:\\Qt\\Mp_Pract\\sort_auto.txt")
#define SORT_INSIDE ("C:\\Qt\\Mp_Pract\\sort_inside.txt")
#define SORT_OUTSIDE ("C:\\Qt\\Mp_Pract\\sort_outside.txt")


using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow:: on_comboBox_currentIndexChanged()
{
//--------------------------------beg_1t_Filter--------------------------------

ifstream dot (PATH, ios::in | ios::out | ios::binary);
if (!dot.is_open()) cout <<"File did't open";
fstream buf (BUF, ios::in| ios::out| ios::trunc| ios:: binary);
if (!buf.is_open()) cout <<"File did't open";

char ok[]={'A','B','C','D','E','F','J','H','I','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','_','.','1','2','3','4','5','6','7','8','9','0'};
char no[]={'1','2','3','4','5','6','7','8','9','0',' '};
bool flag=0;
int n=0;
while (dot.peek()!=EOF)
{
    n++;
    char ch;
    ch=dot.get();
    if ((ch=='"')and(flag==1))
    {
        flag=0;
        buf<<'\n';

    }
    if ((ch=='"')and(flag==0)) flag=1;
    for(int i=0;i<37;i++)
    {

        if ((ch==ok[i])and(flag==1)and(ch!=' '))
        {
            buf<<ch;

        }
    }

}
dot.close();
//-------------------------------------end_1t_Filter---------------

//--------------------------------------beg_2nd_Filter-----------------------------
 vector <string> STRMAS;
string str;
int ac;
buf.seekg(ios::beg);
while (buf.peek()!=EOF)
{

    ac=0;
    buf>>str;
    for(int i=0;i<11;i++)
    {
        if(str[0]!=no[i]) ac++;

    }
    if(ac==11)
    {
        bool contains=false;
        for (unsigned k=0;k<STRMAS.size();k++)
        {
            if (str==STRMAS[k]) contains=true;
        }
        if (!contains) STRMAS.push_back(str);
    }

ui->Stat->setText("Пожалуйста подождите...");
}
buf.close();

//-----------------------------------end_2nd_Filter----------------------------------



if(ui->comboBox->currentText()==ui->comboBox->itemText(1))
{
//======================beg_AUTO SORT===================="<<endl;
 ui->textEdit->clear();

 ofstream sr_A (SORT_AUTO, ios::in | ios::out |ios::trunc| ios::binary);
 if (!sr_A.is_open()) cout <<"File did't open";

 int time = QDateTime::currentMSecsSinceEpoch();

sort(STRMAS.begin(),STRMAS.end());
for(unsigned i=0;i<STRMAS.size();i++)
{
   sr_A<<STRMAS[i]<<endl;

      ui->textEdit->append(QString("%1").arg(STRMAS[i].c_str()));
}

time= QDateTime::currentMSecsSinceEpoch()-time;

ui->time_SORT->clear();
ui->time_SORT->setText(QString("%1").arg(time));

sr_A<<endl<<"time Work (AutoSort): "<<time<<" ms";
sr_A.close();
ui->Stat->setText("Авто сортировка");
//======================end_AUTO SORT====================
}



if(ui->comboBox->currentText()==ui->comboBox->itemText(2))
{
    //======================beg_ISIDE SORT*====================
ofstream sr_I (SORT_INSIDE, ios::in | ios::out |ios::trunc| ios::binary);
if (!sr_I.is_open()) cout <<"File did't open";

ui->textEdit->clear();
int time = QDateTime::currentMSecsSinceEpoch();


time= QDateTime::currentMSecsSinceEpoch()-time;

ui->time_INSIDE->clear();
ui->time_INSIDE->setText(QString("%1").arg(time));

sr_I<<endl<<"time Work (InsideSort): "<<time<<" ms";
sr_I.close();
ui->Stat->setText("Внутренняя сортировка");
//======================end_ISIDE SORT==================
}



if(ui->comboBox->currentText()==ui->comboBox->itemText(3))
{
//======================beg_OutsideSort=====================
ofstream sr_O (SORT_OUTSIDE, ios::in | ios::out |ios::trunc| ios::binary);
if (!sr_O.is_open()) cout <<"File did't open";

ui->textEdit->clear();
int time = QDateTime::currentMSecsSinceEpoch();



time= QDateTime::currentMSecsSinceEpoch()-time;

ui->time_OUTSIDE->clear();
ui->time_OUTSIDE->setText(QString("%1").arg(time));

sr_O<<endl<<"time Work (OutsideSort): "<<time<<" ms";
sr_O.close();
ui->Stat->setText("Внешняя сортировка");
//======================end_OutsideSort====================
}

}


