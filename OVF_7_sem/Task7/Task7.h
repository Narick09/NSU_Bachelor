#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class Task7; }
QT_END_NAMESPACE

class Task7 : public QMainWindow
{
    Q_OBJECT

public:
    Task7(QWidget *parent = nullptr);

    double x_derivative(double, double);
    double y_derivative(double, double);

    void reload();

    void RK2();

    void drawGraphs();

    ~Task7();
signals:
    //void changeAmountPoints(int);
private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_endTimeBox_valueChanged(double arg1);

private:
    Ui::Task7 *ui;

    QCustomPlot *plot_;

    QCPGraph * Rynge_Kytt2_;

    QVector<double> x_0_;// = 4.9;
    QVector<double> y_0_;// = 5.1;

    int n_ = 3000;

    const double a_ = 10;
    const double b_ = 2;
    const double c_ = 2;
    const double d_ = 10;

    double x_min_axe_ = 100000;
    double x_max_axe_ = -100000;
    double y_min_axe_ = 100000;
    double y_max_axe_ = -100000;

    double t_max_ = 3;
    double t_min_ = 0;

    QVector<double> t_n_RK2_;
    QVector<double> x_n_RK2_;
    QVector<double> y_n_RK2_;

    double step_ = (t_max_ - t_min_) / n_;
    double alpha_ = 3.0/4;

    //methods
    void change_N(int arg);
};
#endif // MAINWINDOW_H
