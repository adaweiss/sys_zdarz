#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGridLayout>
#include<QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
namespace Ui {
class MainWindow;
}

class Machine {
    int buffer_capacity;
    QTimer *timer;
    public:
    Machine(){timer=new QTimer;}
    void setBuffer(int i){buffer_capacity=i;}
};

class Process {
public:
    int *machine_order;
    int *times_at_machines;
    void setProcess(int size);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QGridLayout *mainLayout;
    QSpinBox *nr_of_machines;
    QSpinBox *nr_of_processes;
    QLineEdit *processes_description[5];
    QLabel *processes_description_label[5];
    QLabel *nr_of_machines_label;
    QLabel *nr_of_processes_label;
    QSpinBox *machine_buffers_spinBox[5];
    QLabel *machine_buffers_label[5];
    QLabel *time_at_machines_label[5][10];
    QLineEdit *time_at_machines[5][10];
    Machine *machine_table;
    Process *process_table;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int am_of_machines=5;
    int am_of_processes=5;
    int acctual_amount_of_machines;
    int acctual_amount_of_processes;
public slots:
    void display_machines(int n);
    void display_process0_input();
    void display_processes(int n);
    void display_process1_input();
    void display_process2_input();
    void display_process3_input();
    void display_process4_input();

private slots:
    void on_set_initials_clicked();
};

#endif // MAINWINDOW_H
