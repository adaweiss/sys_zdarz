#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include<iostream>
#include <QMessageBox>
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

    mainLayout->addWidget(time_at_machines_label[0][i],2,4+2*i);
    mainLayout->addWidget(time_at_machines[0][i],2,4+2*i+1);

    }
}
void MainWindow::display_process1_input(){
    QString order = processes_description[1]->text();
    for(int i=0;i<order.length();i++){
    QString a ;
    a=order[i];
    time_at_machines_label[1][i]=new QLabel(this);
    time_at_machines[1][i]=new QLineEdit(this);
    time_at_machines_label[1][1]->setText(QString::fromLatin1("Time on machine %1:").arg(a));

    mainLayout->addWidget(time_at_machines_label[1][i],3,4+2*i);
    mainLayout->addWidget(time_at_machines[1][i],3,4+2*i+1);

    }
}
void MainWindow::display_process2_input(){
    QString order = processes_description[2]->text();
    for(int i=0;i<order.length();i++){
    QString a ;
    a=order[i];
    time_at_machines_label[2][i]=new QLabel(this);
    time_at_machines[2][i]=new QLineEdit(this);
    time_at_machines_label[2][i]->setText(QString::fromLatin1("Time on machine %1:").arg(a));

    mainLayout->addWidget(time_at_machines_label[2][i],4,4+2*i);
    mainLayout->addWidget(time_at_machines[2][i],4,4+2*i+1);

    }
}
void MainWindow::display_process3_input(){
    QString order = processes_description[3]->text();
    for(int i=0;i<order.length();i++){
    QString a ;
    a=order[i];
    time_at_machines_label[3][i]=new QLabel(this);
    time_at_machines[3][i]=new QLineEdit(this);
    time_at_machines_label[3][i]->setText(QString::fromLatin1("Time on machine %1:").arg(a));

    mainLayout->addWidget(time_at_machines_label[3][i],5,4+2*i);
    mainLayout->addWidget(time_at_machines[3][i],5,4+2*i+1);

    }
}
void MainWindow::display_process4_input(){
    QString order = processes_description[4]->text();
    for(int i=0;i<order.length();i++){
    QString a ;
    a=order[i];
    time_at_machines_label[4][i]=new QLabel(this);
    time_at_machines[4][i]=new QLineEdit(this);
    time_at_machines_label[4][i]->setText(QString::fromLatin1("Time on machine %1:").arg(a));

    mainLayout->addWidget(time_at_machines_label[4][i],6,4+2*i);
    mainLayout->addWidget(time_at_machines[4][i],6,4+2*i+1);


    }
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
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);


    machine_table=new Machine[acctual_amount_of_machines];
    for(int i=0; i<acctual_amount_of_machines;i++){
        machine_table[i].setBuffer(machine_buffers_spinBox[i]->value());
        cout<<"Machines"<<endl;
        cout<<machine_buffers_spinBox[i]->value()<<endl;
    }
    process_table=new Process[acctual_amount_of_processes];
    for(int i=0; i<acctual_amount_of_processes;i++){
        process_table[i].setProcess(processes_description[i]->text().length());
        QString order = processes_description[i]->text();
        cout<<"Proces "<<i<<endl;
        for(int j=0;j<order.length();j++){
        QString a ;
        a=order[j];
        if(a.toInt()>acctual_amount_of_machines) {msgBox.exec(); return;}
        process_table[i].machine_order[j]=a.toInt();
        process_table[i].times_at_machines[j]=time_at_machines[i][j]->text().toInt();
        cout<<process_table[i].machine_order[j]<<"  "<<process_table[i].times_at_machines[j]<<endl;
        }
    }

    ui->tabWidget->setCurrentIndex(1);

}
