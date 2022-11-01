#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class Task8; }
QT_END_NAMESPACE

class Task8 : public QMainWindow
{
    Q_OBJECT
public:
    Task8(QWidget *parent = nullptr);

    double u_derivative(double, double);
    double v_derivative(double, double);

    void reload();

    void Eiler();

    void EilerImp();

    void drawGraphs();

    ~Task8();
private slots:
    void on_spinBox_valueChanged(int arg1);
    void on_timeBox_valueChanged(int arg1);

private:
    Ui::Task8 *ui;

    QCustomPlot *plot_;
    QCustomPlot *plot_Imp_;

    QCPGraph * Explicit_Euler_u_;
    QCPGraph * Implicit_Euler_v_;
    QCPGraph * Explicit_Euler_v_;
    QCPGraph * Implicit_Euler_u_;

    double t_max_ = 100;
    double t_min_ = 0;

    double u_0_ = 2;
    double v_0_ = -1;

    int n_ = 50;

    const double a_ = 998;
    const double b_ = 1998;
    const double c_ = -999;
    const double d_ = -1999;

    QVector<double> t_E_;
    QVector<double> u_E_exp_;
    QVector<double> v_E_exp_;
    QVector<double> u_E_imp_;
    QVector<double> v_E_imp_;

    double step_ = (t_max_ - t_min_) / n_;
    //QVector <double> step_n_;
    double alpha_ = 3.0/4;

    bool isDrawable = false;
    //methods
    //void change_N(int arg);
};
#endif // MAINWINDOW_H
