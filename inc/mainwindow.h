#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGridLayout>
#include<QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QVector>
namespace Ui {
class MainWindow;
}

class Element{
public:
    int nr;
    int nr_procesu;
    int process_state; //na ktorej maszynie ma być teraz robiony
    Element(int n,int nr_p, int state){nr=n; nr_procesu=nr_p; process_state=state;}
    Element(){}
};

class Machine {
    public:
    int buffer_capacity;
    Element *currently_made;
    QVector<Element> elements_in_buffer;
    QTimer *timer;
    Machine(){timer=new QTimer;}
    void setBuffer(int i){buffer_capacity=i; currently_made=nullptr;}
    int getBuffer(){return buffer_capacity;}
    void setCurrentlyMade(Element e){currently_made=new Element(e.nr,e.nr_procesu,e.process_state);}

};

class Process {
public:
    int *machine_order;
    int *times_at_machines;
    int size;
    void setProcess(int len);
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
    QLabel *machine_pic_label[5];
    QLabel *machine_buf_pic_label[5][10];
    QLabel *no[5];
    QLabel *no_label[5];




public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int** build_incident_matrix();

    void machine_actions(int machine_no);
private:
    Ui::MainWindow *ui;
    int am_of_machines=5;
    int am_of_processes=5;
    int acctual_amount_of_machines;
    int acctual_amount_of_processes;
    int *amount_of_details;
    QVector<Element> elements_list[5];
public slots:
    void display_machines(int n);
    void display_process0_input();
    void display_processes(int n);
    void display_process1_input();
    void display_process2_input();
    void display_process3_input();
    void display_process4_input();
    void timer1_runout();
    void timer2_runout();
    void timer3_runout();
    void timer4_runout();
    void timer5_runout();


private slots:
    void on_set_initials_clicked();
    void on_start_clicked();
};

#endif // MAINWINDOW_H
