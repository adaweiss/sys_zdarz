#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGridLayout>
#include<QLabel>
#include <QSpinBox>
#include <QLineEdit>
namespace Ui {
class MainWindow;
}

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


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int am_of_machines=5;
    int am_of_processes=5;
public slots:
    void display_machines(int n);
    void display_process0_input();
    void display_processes(int n);
};

#endif // MAINWINDOW_H
