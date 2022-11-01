#ifndef TASK2_H
#define TASK2_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class Task2; }
QT_END_NAMESPACE

class Task2 : public QMainWindow
{
    Q_OBJECT

public:
    Task2(QWidget *parent = nullptr);

    void setStep();

    double func(double E);//our function
    double derr_func(double E_n);
    double graph();
    double tmpFunc(double x);

    void dihotomyMethod();

    ~Task2();

private slots:
    void on_pushButton_clicked();

    void on_doubleSpinBoxMin_valueChanged(double arg1);

    void on_doubleSpinBoxMax_valueChanged(double arg1);

    void on_doubleSpinBoxMin_y_valueChanged(double arg1);

    void on_doubleSpinBoxMax_y_valueChanged(double arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_lambda_valueChanged(double arg1);

private:
    Ui::Task2 *ui;

    QCustomPlot *plot_;

    const double init_step_ = 1e-7;
    double mech_epsilon = init_step_;
    const double U0_ = 50*1e6*1.6e-12;//5e9;
    const double a_ = 1e-12;//1e-6;
    const double m_ = 9.1e-28;
    const double h_ = 1.054e-27;//1.054e-34/1.6e-19;//1.054e-27;
    const double m_2_a_sqwared_devided_h_sqwared_ = 2*a_*a_*m_/(h_*h_);//a_*a_*m_/(2*h_*h_);

    double lambda_ = 100000;

    //for plot
    double x_scale_ = 1e-7;//range for graph
    double x_scale_box_ = 1e2;//range for boxes
    double x_max_ = 0;
    double x_min_ = -8.0;//e-5;
    double y_max_ = 25;
    double y_min_ = -20;

    QVector<double> energies;
    QVector<double> eq;

    double dih = 0;

};
#endif // TASK2_H
