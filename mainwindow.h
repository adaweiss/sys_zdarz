#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGridLayout>
#include<QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <Vector>
namespace Ui {
class MainWindow;
}

class Machine {
    int buffer_capacity;
    QTimer *timer;
    public:
    Machine(){timer=new QTimer;}
    void setBuffer(int i){buffer_capacity=i;}
    int getBuffer(){return buffer_capacity;}

};

class Process {
public:
    int *machine_order;
    int *times_at_machines;
    int size;
    void setProcess(int len);
};


class Element{
    int nr_procesu;
    int process_state; //na ktorej maszynie ma być teraz robiony
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
    QLabel *nr_of_details_in_label[5];
    QLineEdit  *nr_of_details_in[5];
    QGridLayout *process_layout;
    Machine *machine_table;
    Process *process_table;
    QLabel *machine_pic[5];
    QLabel *machine_buf_pic[5][10];


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int am_of_machines=5;
    int am_of_processes=5;
    int acctual_amount_of_machines;
    int acctual_amount_of_processes;
    int *amount_of_details;
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
