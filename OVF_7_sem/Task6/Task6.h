#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class Task6; }
QT_END_NAMESPACE

class Task6 : public QMainWindow
{
    Q_OBJECT

public:
    Task6(QWidget *parent = nullptr);

    void setStep();

    double func(double);
    void reload();
    double Eiler();

    void RK2();
    void RK4();

    void drawGraphs();

    ~Task6();

private slots:
    void on_eilerBox_stateChanged(int arg1);

    void on_rk2Box_stateChanged(int arg1);

    void on_alphaSpinBox_valueChanged(double arg1);

    void on_rk4Box_stateChanged(int arg1);

private:
    Ui::Task6 *ui;

    QCustomPlot *plot_;

    QCPGraph * Eiler_;
    QCPGraph * Rynge_Kytt2_;
    QCPGraph * Rynge_Kytt4_;
    QCPGraph * EXP;

    const double h_ = 1e-3;
    double mech_epsilon = h_;

    //for plot
    double t_max_ = 3;
    double t_min_ = 0;
    //double y_scale_ = 1;
    double x_max_ = 1.1;
    double x_min_ = 0;

    double t_0_ = 0;
    double x_0_ = 1;

    int n_ = 100;

    QVector<double> t_n_E_;
    QVector<double> x_n_E_;

    QVector<double> t_n_RK2_;
    QVector<double> x_n_RK2_;

    QVector<double> t_n_RK4_;
    QVector<double> x_n_RK4_;

    QVector<double> t_n_exp_;
    QVector<double> x_n_exp_;

    double step_ = (t_max_ - t_min_) / n_;
    //QVector <double> step_n_;
    double alpha_ = 1;
};
#endif // MAINWINDOW_H
