#include "inc/mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include<iostream>
#include <QMessageBox>
#include <QPixmap>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainLayout=new QGridLayout(this);
    nr_of_machines=new QSpinBox(this);
    nr_of_machines_label= new QLabel;
    nr_of_machines_label->setText("Amount of machines: ");
    mainLayout->addWidget(nr_of_machines_label,0,0);
    mainLayout->addWidget(nr_of_machines,0,1);
    for(int i=0;i<am_of_machines; i++){
        machine_buffers_spinBox[i]=new QSpinBox(this);
        machine_buffers_label[i]=new QLabel(this);
        machine_buffers_label[i]->setText(QString::fromLatin1("Capacity of machine %1 buffer:").arg(i+1));
        machine_buffers_spinBox[i]->setVisible(false);
        machine_buffers_label[i]->setVisible(false);
        machine_buffers_spinBox[i]->setMinimum(2);
        mainLayout->addWidget(machine_buffers_label[i],i+2,0);
        mainLayout->addWidget(machine_buffers_spinBox[i],i+2,1);
    }

    nr_of_processes=new QSpinBox(this);
    nr_of_processes_label=new QLabel(this);
    nr_of_processes_label->setText("Amount of processes:");
    mainLayout->addWidget(nr_of_processes_label,0,2);
    mainLayout->addWidget(nr_of_processes,0,3);
    for(int i=0;i<am_of_machines; i++){
        processes_description[i]=new QLineEdit(this);
        processes_description_label[i]=new QLabel(this);
        processes_description_label[i]->setText(QString::fromLatin1("Process %1:").arg(i+1));
        processes_description[i]->setVisible(false);
        processes_description_label[i]->setVisible(false);
        mainLayout->addWidget(processes_description_label[i],i+2,2);
        mainLayout->addWidget(processes_description[i],i+2,3);
    }
    ui->mainWidget->setLayout(mainLayout);
    connect(nr_of_machines, SIGNAL (valueChanged(int)), this, SLOT (display_machines(int)));
    connect(nr_of_processes, SIGNAL (valueChanged(int)), this, SLOT (display_processes(int)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

int** MainWindow::build_incident_matrix()
{
    int all_processes_length=0;
    for(int i=0;i<acctual_amount_of_processes;i++){
        all_processes_length+=process_table[i].size;
    }
    int trans_no=3*all_processes_length+acctual_amount_of_processes; //no. of translations
    int state_no = 2*acctual_amount_of_machines+3*all_processes_length+2;//no. of states
    int** tab = new int* [state_no]; //nb of translations and states in one machine and one transport robot

    for(int i =0;i<state_no;i++)
        tab[i] = new int [trans_no];
    for(int i =0;i<state_no;i++)
        for(int j =0;j<trans_no;j++)
            tab[i][j]=0;

    int a=acctual_amount_of_machines*2-1;
    int b=0;
    for(int i=0;i<acctual_amount_of_processes;i++){
        for(int j=0;j<process_table[i].size;j++){
            int tmp_machine = process_table[i].machine_order[j]+1;

            tab[tmp_machine*2-1][b]=-1;
            tab[a][b]=1;
            tab[a][b+1]=-1;
            tab[tmp_machine*2-2][b+1]=-1;
            tab[a+1][b+1]=1;
            tab[a+1][b+2]=-1;
            tab[a+2][b+2]=1;
            tab[tmp_machine*2-2][b+2]=1;
            tab[a+2][b+3]=-1;
            tab[tmp_machine*2-1][b+3]=1;
            if(j==0){//poczatek procesu
                tab[state_no-2][b]=-1;
                tab[(process_table[i].machine_order[j+1]+1)*2-1][b+3]=-1;
                tab[process_table[i].machine_order[j+1]+1][b+3]=1;
            }else if(j==process_table[i].size-1){//ostatnia czesc procesu
                tab[(process_table[i].machine_order[j-1]+1)*2-1][b]=1;
                tab[process_table[i].machine_order[j-1]+1][b]=-1;
                tab[state_no-1][b+3]=1;
            }else{
                tab[(process_table[i].machine_order[j-1]+1)*2-1][b]=1;
                tab[process_table[i].machine_order[j-1]+1][b]=-1;
                tab[(process_table[i].machine_order[j+1]+1)*2-1][b+3]=-1;
                tab[process_table[i].machine_order[j+1]+1][b+3]=1;
            }
            a+=3; b+=3;
        }
        b+=1;
    }

   /* for(int i =0;i<state_no;i++){
        for(int j =0;j<trans_no;j++)
          cout<< tab[i][j]<< "\t";
        cout<<endl;
    }*/


    return tab;
}

void MainWindow::display_machines(int n)
{
    acctual_amount_of_machines=nr_of_machines->value();
    for(int i=0;i<n; i++)  {
        machine_buffers_spinBox[i]->setVisible(true);
        machine_buffers_label[i]->setVisible(true);
    }
    for(int i=n;i<am_of_machines; i++)  {
        machine_buffers_spinBox[i]->setVisible(false);
        machine_buffers_label[i]->setVisible(false);
    }


}

void MainWindow::display_processes(int n)
{
    acctual_amount_of_processes=nr_of_processes->value();

    for(int i=0;i<n; i++)  {
        processes_description[i]->setVisible(true);
        processes_description_label[i]->setVisible(true);
    }
    for(int i=n;i<am_of_processes; i++)  {
        processes_description[i]->setVisible(false);
        processes_description_label[i]->setVisible(false);
    }
    connect(processes_description[0], SIGNAL (editingFinished()), this, SLOT (display_process0_input()));
    connect(processes_description[1], SIGNAL (editingFinished()), this, SLOT (display_process1_input()));
    connect(processes_description[2], SIGNAL (editingFinished()), this, SLOT (display_process2_input()));
    connect(processes_description[3], SIGNAL (editingFinished()), this, SLOT (display_process3_input()));
    connect(processes_description[4], SIGNAL (editingFinished()), this, SLOT (display_process4_input()));


}

void MainWindow::display_process0_input(){
    QString order = processes_description[0]->text();
    for(int i=0;i<order.length();i++){
    QString a ;
    a=order[i];
    time_at_machines_label[0][i]=new QLabel(this);
    time_at_machines[0][i]=new QLineEdit(this);
    time_at_machines_label[0][i]->setText(QString::fromLatin1("Time on machine %1:").arg(a));
    time_at_machines[0][i]->setText("1");

    mainLayout->addWidget(time_at_machines_label[0][i],2,4+2*i);
    mainLayout->addWidget(time_at_machines[0][i],2,4+2*i+1);
    }
    nr_of_details_in_label[0]=new QLabel(this);
    nr_of_details_in[0]=new QLineEdit(this);
    nr_of_details_in_label[0]->setText(QString::fromLatin1("No of details in process 1"));
    mainLayout->addWidget(nr_of_details_in_label[0],8,4);
    mainLayout->addWidget(nr_of_details_in[0],8,5);

}
void MainWindow::display_process1_input(){
    QString order = processes_description[1]->text();
    for(int i=0;i<order.length();i++){
    QString a ;
    a=order[i];
    time_at_machines_label[1][i]=new QLabel(this);
    time_at_machines[1][i]=new QLineEdit(this);
    time_at_machines_label[1][i]->setText(QString::fromLatin1("Time on machine %1:").arg(a));
    time_at_machines[1][i]->setText("1");

    mainLayout->addWidget(time_at_machines_label[1][i],3,4+2*i);
    mainLayout->addWidget(time_at_machines[1][i],3,4+2*i+1);
    }
    nr_of_details_in_label[1]=new QLabel(this);
    nr_of_details_in[1]=new QLineEdit(this);
    nr_of_details_in_label[1]->setText(QString::fromLatin1("No of details in process 2"));
    mainLayout->addWidget(nr_of_details_in_label[1],9,4);
    mainLayout->addWidget(nr_of_details_in[1],9,5);

}
void MainWindow::display_process2_input(){
    QString order = processes_description[2]->text();
    for(int i=0;i<order.length();i++){
    QString a ;
    a=order[i];
    time_at_machines_label[2][i]=new QLabel(this);
    time_at_machines[2][i]=new QLineEdit(this);
    time_at_machines_label[2][i]->setText(QString::fromLatin1("Time on machine %1:").arg(a));
    time_at_machines[2][i]->setText("1");


    mainLayout->addWidget(time_at_machines_label[2][i],4,4+2*i);
    mainLayout->addWidget(time_at_machines[2][i],4,4+2*i+1);

    }
    nr_of_details_in_label[2]=new QLabel(this);
    nr_of_details_in[2]=new QLineEdit(this);
    nr_of_details_in_label[2]->setText(QString::fromLatin1("No of details in process 3"));
    mainLayout->addWidget(nr_of_details_in_label[2],10,4);
    mainLayout->addWidget(nr_of_details_in[2],10,5);
}
void MainWindow::display_process3_input(){
    QString order = processes_description[3]->text();
    for(int i=0;i<order.length();i++){
    QString a ;
    a=order[i];
    time_at_machines_label[3][i]=new QLabel(this);
    time_at_machines[3][i]=new QLineEdit(this);
    time_at_machines_label[3][i]->setText(QString::fromLatin1("Time on machine %1:").arg(a));
    time_at_machines[3][i]->setText("1");


    mainLayout->addWidget(time_at_machines_label[3][i],5,4+2*i);
    mainLayout->addWidget(time_at_machines[3][i],5,4+2*i+1);

    }
    nr_of_details_in_label[3]=new QLabel(this);
    nr_of_details_in[3]=new QLineEdit(this);
    nr_of_details_in_label[3]->setText(QString::fromLatin1("No of details in process 4"));
    mainLayout->addWidget(nr_of_details_in_label[3],11,4);
    mainLayout->addWidget(nr_of_details_in[3],11,5);
}
void MainWindow::display_process4_input(){
    QString order = processes_description[4]->text();
    for(int i=0;i<order.length();i++){
    QString a ;
    a=order[i];
    time_at_machines_label[4][i]=new QLabel(this);
    time_at_machines[4][i]=new QLineEdit(this);
    time_at_machines_label[4][i]->setText(QString::fromLatin1("Time on machine %1:").arg(a));
    time_at_machines[4][i]->setText("1");

    mainLayout->addWidget(time_at_machines_label[4][i],6,4+2*i);
    mainLayout->addWidget(time_at_machines[4][i],6,4+2*i+1);
    }
    nr_of_details_in_label[4]=new QLabel(this);
    nr_of_details_in[4]=new QLineEdit(this);
    nr_of_details_in_label[4]->setText(QString::fromLatin1("No of details in process 5"));
    mainLayout->addWidget(nr_of_details_in_label[4],12,4);
    mainLayout->addWidget(nr_of_details_in[4],12,5);
}


void Process::setProcess(int len)
{
    machine_order=new int[len];
    times_at_machines= new int[len];
    size=len;

}




void MainWindow::on_set_initials_clicked()
{

    QMessageBox msgBox;
    msgBox.setText("Error in process desctiption.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);


    machine_table=new Machine[acctual_amount_of_machines];
    for(int i=0; i<acctual_amount_of_machines;i++){
        machine_table[i].setBuffer(machine_buffers_spinBox[i]->value());
      //  cout<<"Machines"<<endl;
       // cout<<machine_table[i].getBuffer();
    }
    process_table=new Process[acctual_amount_of_processes];
    for(int i=0; i<acctual_amount_of_processes;i++){
        process_table[i].setProcess(processes_description[i]->text().length());
        QString order = processes_description[i]->text();
      //  cout<<"Proces "<<i<<endl;
        for(int j=0;j<order.length();j++){
        QString a ;
        a=order[j];
        if(a.toInt()>acctual_amount_of_machines) {msgBox.exec(); return;}
        process_table[i].machine_order[j]=a.toInt()-1;
        process_table[i].times_at_machines[j]=time_at_machines[i][j]->text().toInt();
       // cout<<process_table[i].machine_order[j]<<"  "<<process_table[i].times_at_machines[j]<<endl;
        }
    }

    ui->tabWidget->setCurrentIndex(1);
    amount_of_details=new int[acctual_amount_of_processes];
    for(int i=0;i<acctual_amount_of_processes;i++){
        amount_of_details[i]=nr_of_details_in[i]->text().toInt();
    }


    //Gosia
    int all_processes_length_2=0;
    for(int i=0;i<acctual_amount_of_processes;i++){
        all_processes_length_2+=process_table[i].size;
    }
    int trans_no_2=3*all_processes_length_2+acctual_amount_of_processes; //no. of translations
    int state_no_2 = 2*acctual_amount_of_machines+3*all_processes_length_2+2;//no. of states
    int** tab_2 = new int* [state_no_2];
    for(int i =0;i<state_no_2;i++)
       tab_2[i] = new int [trans_no_2];
    tab_2=build_incident_matrix();



    QPixmap m=QPixmap("C:/Users/Ada/Documents/sys_zdarz/images/machine.png");

   QPixmap b("C:/Users/Ada/Documents/sys_zdarz/images/bufor.png");

   process_layout= new QGridLayout(this);
    int k=0;
    int l=0;
   for(int i=0;i<acctual_amount_of_machines;i++){
       machine_pic[i]=new QLabel(this);
       machine_pic_label[i]=new QLabel(this);
       machine_pic_label[i]->setText(" ");
       machine_pic[i]->setPixmap(m);
       for(int j=0;j<machine_table[i].getBuffer();j++)
       {
           machine_buf_pic[i][j]=new QLabel(this);
           machine_buf_pic[i][j]->setPixmap(b);
           machine_buf_pic_label[i][j]=new QLabel(this);
           machine_buf_pic_label[i][j]->setText(" ");
           process_layout->addWidget(machine_buf_pic[i][j],l,k);
           process_layout->addWidget(machine_buf_pic_label[i][j],l,k);

           k++;
       }
       process_layout->addWidget(machine_pic[i],l,k);
       process_layout->addWidget(machine_pic_label[i],l,k);
       k++;
   }
   ui->process_widget->setLayout(process_layout);
   if(acctual_amount_of_machines>0)    connect(machine_table[0].timer, SIGNAL (timeout()), this, SLOT(timer1_runout()));
   if(acctual_amount_of_machines>1)    connect(machine_table[1].timer, SIGNAL (timeout()), this, SLOT(timer2_runout()));
   if(acctual_amount_of_machines>2)    connect(machine_table[2].timer, SIGNAL (timeout()), this, SLOT(timer3_runout()));
   if(acctual_amount_of_machines>3)    connect(machine_table[3].timer, SIGNAL (timeout()), this, SLOT(timer4_runout()));
   if(acctual_amount_of_machines>4)    connect(machine_table[4].timer, SIGNAL (timeout()), this, SLOT(timer5_runout()));
   QGridLayout *no_layout=new QGridLayout(this);
   ui->no_widget->setLayout(no_layout);
   for(int i=0;i<acctual_amount_of_processes;i++){
       no[i]=new QLabel(this);
       no_label[i]=new QLabel(this);
       no[i]->setText("0");
       no_label[i]->setText(QString::fromLatin1("No of elements produced in %1:").arg(i));
       no_layout->addWidget(no_label[i],0,2*i);
       no_layout->addWidget(no[i],0,2*i+1);

   }

}

void MainWindow::on_start_clicked()
{
    for(int i=0;i<acctual_amount_of_processes;i++){
       for(int j=0;j<amount_of_details[i];j++)        {Element a=Element(j,i,0); elements_list[i].push_back(a);}
    }

// initiale
    for(int i=0;i<acctual_amount_of_processes;i++){
        int j=machine_table[process_table[i].machine_order[0]].getBuffer()-1;
       // cout<<"proc "<<i;
        if(machine_pic_label[process_table[i].machine_order[0]]->text()==" ") {
            cout<<"proc "<<i;
        machine_table[process_table[i].machine_order[0]].setCurrentlyMade(elements_list[i].last());
        machine_pic_label[process_table[i].machine_order[0]]->setText(QString::fromLatin1("        p%1_%2").arg(machine_table[process_table[i].machine_order[0]].currently_made->nr_procesu).arg(machine_table[process_table[i].machine_order[0]].currently_made->nr));
        elements_list[i].pop_back();
        machine_table[process_table[i].machine_order[0]].timer->start(process_table[i].times_at_machines[0]*1000);
        }
        if(machine_buf_pic_label[process_table[i].machine_order[0]][j]->text()==" ") {
            cout<<"proc "<<i;
        machine_table[process_table[i].machine_order[0]].elements_in_buffer.push_back(elements_list[i].last());
        machine_buf_pic_label[process_table[i].machine_order[0]][j]->setText(QString::fromLatin1("  p%1_%2").arg(machine_table[process_table[i].machine_order[0]].elements_in_buffer.last().nr_procesu).arg(machine_table[process_table[i].machine_order[0]].elements_in_buffer.last().nr));
        elements_list[i].pop_back();
        }
    }
}

void MainWindow::machine_actions(int machine_no){
    machine_table[machine_no].timer->stop();
    if(machine_table[machine_no].currently_made!=nullptr) {
    int proces_no=machine_table[machine_no].currently_made->nr_procesu;
    if(process_table[proces_no].size==machine_table[machine_no].currently_made->process_state+1) //is it the last stage
    {
        machine_pic_label[machine_no]->setText(" ");
        machine_table[machine_no].currently_made=nullptr;
        no[proces_no]->setText(QString::fromLatin1("%1").arg(no[proces_no]->text().toInt()+1));
        bool flag=true;
        for (int i=0;i<acctual_amount_of_processes;i++) {
            if(no[i]->text().toInt()!=amount_of_details[i]) flag=false;
            cout<<"Jest: "<<no[i]->text().toInt()<<" powinno:"<<amount_of_details[i]<<endl;
        }
        if(flag){
            QMessageBox msgBox;
            msgBox.setText("Production completed.");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
            ui->statusBar->showMessage("Finished");
        }
        //just throw it away
    }
    else {
        Element e=Element(machine_table[machine_no].currently_made->nr,machine_table[machine_no].currently_made->nr_procesu,machine_table[machine_no].currently_made->process_state+1);
        int next_machine=process_table[e.nr_procesu].machine_order[e.process_state];
        if(machine_table[next_machine].elements_in_buffer.size()<machine_table[next_machine].buffer_capacity){// if there is a place to put it
            machine_table[next_machine].elements_in_buffer.push_back(e);
            machine_table[machine_no].currently_made=nullptr;
            if(is_Safe()){ //if new state is safe
                int k=1;
                for(int i=0;i<machine_table[next_machine].buffer_capacity&&k==1;i++){
                    if(machine_buf_pic_label[next_machine][i]->text()==" ") {
                        machine_buf_pic_label[next_machine][i]->setText(QString::fromLatin1("  p%1_%2").arg(proces_no).arg(e.nr));
                        machine_pic_label[machine_no]->setText(" ");
                        //machine_table[machine_no].currently_made=nullptr;
                        k=0;
                    }
                }
                ui->statusBar->showMessage("Busy");
                cout<<"Bezpieczny"<<endl;

            }
            else {
                ui->statusBar->showMessage("Waiting");
                machine_table[next_machine].elements_in_buffer.pop_back();
                machine_table[machine_no].setCurrentlyMade(e);
                machine_table[machine_no].timer->start(500);

                //return;

            }
        }
        else {machine_table[machine_no].timer->start(500);}
        if(!machine_table[next_machine].timer->isActive()) machine_actions(next_machine);

    }

    }
    int k=1;
    if(machine_table[machine_no].currently_made==nullptr){
    for(int j=0;j<acctual_amount_of_processes&&k==1;j++){
        if(process_table[j].machine_order[0]==machine_no){
            if(machine_table[machine_no].elements_in_buffer.size()==0&&elements_list[j].size()>0){
                Element tmp=elements_list[j].last();
                machine_table[machine_no].elements_in_buffer.push_back(tmp);
                elements_list[j].pop_back();
                for(int i=0;i<machine_table[machine_no].buffer_capacity&&k==1;i++){
                if(machine_buf_pic_label[machine_no][i]->text()==" ") {
                    machine_buf_pic_label[machine_no][i]->setText(QString::fromLatin1("  p%1_%2").arg(tmp.nr_procesu).arg(tmp.nr));
                    machine_pic_label[machine_no]->setText(" ");
                    machine_table[machine_no].currently_made=nullptr;
                    k=0;
                }
                }

            }
        }

    }

    if(machine_table[machine_no].elements_in_buffer.size()>0) {
        int index=prioritize(machine_table[machine_no].elements_in_buffer);
       Element a=machine_table[machine_no].elements_in_buffer.at(index);
       machine_table[machine_no].setCurrentlyMade(a);
       machine_table[machine_no].elements_in_buffer.remove(index);
       machine_pic_label[machine_no]->setText(QString::fromLatin1("        p%1_%2").arg(a.nr_procesu).arg(a.nr));
       for(int i=0;i<machine_table[machine_no].buffer_capacity;i++){
       if(machine_buf_pic_label[machine_no][i]->text()==QString::fromLatin1("  p%1_%2").arg(a.nr_procesu).arg(a.nr)) {
           machine_buf_pic_label[machine_no][i]->setText(" ");
        }
       }
       machine_table[machine_no].timer->start(process_table[a.nr_procesu].times_at_machines[a.process_state]*1000);
    }
    }
    for(int i=0;i<acctual_amount_of_processes;i++){
        //if(!machine_table[i].timer->isActive()) machine_actions(i);
        if(!machine_table[process_table[i].machine_order[0]].timer->isActive()&& machine_table[process_table[i].machine_order[0]].getBuffer()==0) machine_actions(process_table[i].machine_order[0]);
    }

}

void MainWindow::timer1_runout(){
machine_actions(0);
}

void MainWindow::timer2_runout()
{
    machine_actions(1);
}
void MainWindow::timer3_runout()
{
    machine_actions(2);

}
void MainWindow::timer4_runout()
{
    machine_actions(3);

}
void MainWindow::timer5_runout()
{
    machine_actions(4);

}

int MainWindow::prioritize(QVector<Element> elem_v){
    int ind=0;
    if(elem_v.size()==1) return 0;
    else{
        int t=100000;
        for(int i=0;i<elem_v.size();i++){
            int state=elem_v[i].process_state;
            int pr_no=elem_v[i].nr_procesu;
            int tmp_t=0;
            for(int j=state;j<process_table[pr_no].size;j++) tmp_t+=process_table[pr_no].times_at_machines[j];
            if(tmp_t<t) ind=i;
        }
    }
    return ind;
}

bool MainWindow::is_Safe(){
    QVector<Element> all_processes;
    QVector<bool> koniec;
    int *robocze=new int[acctual_amount_of_machines];
    for(int i=0;i<acctual_amount_of_machines;i++) {
        int k=0;
        for(int j=0;j<machine_table[i].elements_in_buffer.size();j++) {
            //all_processes.push_back(machine_table[i].elements_in_buffer.at(j));
            //koniec.push_back(false);
            ++k;
        }
        if(machine_table[i].currently_made!=nullptr) {
            all_processes.push_back(Element(machine_table[i].currently_made->nr, machine_table[i].currently_made->nr_procesu, machine_table[i].currently_made->process_state));
            koniec.push_back(false);
            ++k;
        }
        robocze[i]=machine_table[i].getBuffer()+1-k;
    }
    int size=all_processes.size();
    if(size>0){
    int **przydzial= new int*[size];
    int **zadane= new int*[size];
    for(int i=0;i<size;i++) {
        przydzial[i]=new int[acctual_amount_of_machines];
        zadane[i]=new int[acctual_amount_of_machines];
        for(int j=0;j<acctual_amount_of_machines;j++) {przydzial[i][j]=0; zadane[i][j]=0;}
    }

    for(int i=0;i<size;i++){
    int machine=process_table[all_processes.at(i).nr_procesu].machine_order[all_processes.at(i).process_state];
    przydzial[i][machine]=1;
        for(int j=all_processes.at(i).process_state+1;j<process_table[all_processes.at(i).nr_procesu].size;j++){
            zadane[i][process_table[all_processes.at(i).nr_procesu].machine_order[j]]=1;
        }
    }
   /* cout<<"control"<<endl;
   for(int i=0;i<size;i++) {
        for(int j=0;j<acctual_amount_of_machines;j++) cout<<zadane[i][j]<<" ";
    cout<<endl;
    }
    cout<<"przydzial"<<endl;
    for(int i=0;i<size;i++) {
        for(int j=0;j<acctual_amount_of_machines;j++) cout<<przydzial[i][j]<<" ";
    cout<<endl;
    }
    cout<<"robocze"<<endl;
    for(int i=0;i<acctual_amount_of_machines;i++) cout<<robocze[i]<<endl;
*/
    int i=0;
    int changed=0;
   // cout<<"size: "<<size<<endl;
    for(;;){
        //cout<<"i"<<i<<endl;
        if(koniec[i]==false){
            bool flag=false;
           /* cout<<"robocze"<<endl;
            for(int k=0;k<acctual_amount_of_machines;k++) cout<<robocze[k]<<" ";
            cout<<endl;
            cout<<"zadane"<<endl;
            for(int k=0;k<acctual_amount_of_machines;k++) cout<<zadane[i][k]<<" ";
            cout<<endl;*/
            for(int j=0;j<acctual_amount_of_machines;j++) {
                if(zadane[i][j]<=robocze[j])  flag=true;
                else {flag=false; break;}
            }
            if(flag){
                for(int l=0;l<acctual_amount_of_machines;l++) robocze[l]=robocze[l]+przydzial[i][l];
                koniec[i]=true;
                changed+=1;
                cout<<"changed"<<endl;


            }
        }
        bool flag1=true;
        for(int j=0;j<size;j++) if(koniec[j]!=true) flag1=false;
        if(flag1) return true;

        if(i==(size-1)&&changed==0) return false;
        else if(i==size-1) changed=0;
        i=i+1;
        i=i%size;

    }
    }
    else {
        return true;
    }


}
