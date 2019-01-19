#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

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
    ui->centralWidget->setLayout(mainLayout);
    connect(nr_of_machines, SIGNAL (valueChanged(int)), this, SLOT (display_machines(int)));
    connect(nr_of_processes, SIGNAL (valueChanged(int)), this, SLOT (display_processes(int)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display_machines(int n)
{
    int nr=nr_of_machines->value();
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
    int nr=nr_of_processes->value();
    for(int i=0;i<n; i++)  {
        processes_description[i]->setVisible(true);
        processes_description_label[i]->setVisible(true);
    }
    for(int i=n;i<am_of_processes; i++)  {
        processes_description[i]->setVisible(false);
        processes_description_label[i]->setVisible(false);
    }
    connect(processes_description[0], SIGNAL (editingFinished()), this, SLOT (display_process0_input()));

}

void MainWindow::display_process0_input(){
    QString order = processes_description[0]->text();
    for(int i=0;i<order.length();i++){
    QString a ;
    a=order[i];
    time_at_machines_label[0][i]=new QLabel(this);
    time_at_machines[0][i]=new QLineEdit(this);
    time_at_machines_label[0][i]->setText(a);

    mainLayout->addWidget(time_at_machines_label[0][i],2,4+2*i);
    mainLayout->addWidget(time_at_machines[0][i],2,4+2*i+1);

    }
}
