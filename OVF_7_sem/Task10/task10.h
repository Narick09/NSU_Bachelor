#ifndef TASK10_H
#define TASK10_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class Task10; }
QT_END_NAMESPACE

class Task10 : public QMainWindow
{
    Q_OBJECT

public:
    Task10(QWidget *parent = nullptr);
    ~Task10();

    void draw();

private slots:
    void on_NBox_valueChanged(int arg1);

    void on_TBox_valueChanged(int arg1);

private:
    Ui::Task10 *ui;
    QCPGraph * graph;

    int N = 10;
    double x_0 = 0;
    double x_L = 5;
    double h = (x_L - x_0) / N;

    int T = 50;
    double t_0 = 0;
    double t_end = 5;
    double tau = (t_end - t_0) / T;

    double u_0t = 0;
    double u_Lt = 0;

    QVector<double> a_;
    QVector<double> b_;
    QVector<double> c_;
    QVector<double> d_;

    QVector<double> t_;
    QVector<double> x_;
    QVector<double> y_;
    QVector<QVector<double>> u_;
    QVector<double> u_max_;

    bool isDraw = false;

    double u_x0(double x);
    double Lu(int m, int j);
    void run_through();

    void task();
};
#endif // TASK10_H
