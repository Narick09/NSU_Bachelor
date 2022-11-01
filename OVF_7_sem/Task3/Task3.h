#ifndef TASK3_H
#define TASK3_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QVector>

//доп задание:
//функцию 3б от 0 до 1 нарисовать на 3х плотах
//на них же нарисовать методом трапеций (на каждом шаге) ступеньки для случаев 4, 16, 32
//с соответствующим шагом (для 4, н-р, 0-0.25; 0.25-0.5; 0.5-0.75; 0.75-1) - и на каждом шаге значение метода трапеций


QT_BEGIN_NAMESPACE
namespace Ui { class Task3; }
QT_END_NAMESPACE

class Task3 : public QMainWindow
{
    Q_OBJECT

public:
    Task3(QWidget *parent = nullptr);
    void setStep();

    double func_3a(double x);
    double func_3b(double x);

    double trapezoid_3a();
    double trapezoid_3b();
    double simpson_3a();
    double simpson_3b();

    void graph();
    void fillTraps();

    void replotAll();

    ~Task3();
private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_but_gr_1_clicked();

    void on_but_step_1_clicked();

    void on_but_gr_2_clicked();

    void on_but_step_2_clicked();

    void on_but_gr_3_clicked();

    void on_but_step_3_clicked();

private:
    Ui::Task3 *ui;

    const double init_step_ = 1e-3;
    double mech_epsilon_ = init_step_;

    double x_max_a_ = 1;
    double x_min_a_ = -1;
    //double y_scale_ = 1;
    double x_max_b_ = 1;
    double x_min_b_ = 0;

    int n_3a_ = 2;
    int n_3b_ = 2;

    double step_3a = (x_max_a_ - x_min_a_) / n_3a_;
    double step_3b = (x_max_b_ - x_min_b_) / n_3b_;

    QVector<double> x_k_;
    QVector<double> y_k_;

    QVector<double> L_Fi_;//коэффициенты для Лагранжа
    QVector<double> N_Fi_;

    QCustomPlot * plot1_;
    QCustomPlot * plot2_;
    QCustomPlot * plot3_;

    QCPGraph * func1_;
    QCPGraph * func2_;
    QCPGraph * func3_;

    QCPGraph * trap4_;
    QCPGraph * trap16_;
    QCPGraph * trap32_;

    QVector<double> tmpX_;
    QVector<double> tmpY_;
    bool isGraph_ = false;
};
#endif // Task3_H
