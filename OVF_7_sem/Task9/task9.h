#ifndef TASK9_H
#define TASK9_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class Task9; }
QT_END_NAMESPACE

class Task9 : public QMainWindow
{
    Q_OBJECT

public:
    Task9(QWidget *parent = nullptr);
    ~Task9();

    double ySecDer(double x);
    double analiticF(double x);

    void draw();
private slots:
    void on_xMinBox_valueChanged(double arg1);
    void on_xMaxBox_valueChanged(double arg1);
    void on_yMinBox_valueChanged(double arg1);
    void on_yMaxBox_valueChanged(double arg1);

private:
    Ui::Task9 *ui;

    QCPGraph * graph;
    QCPGraph * graph_er;

    double x_n = 10000;
    double x_left_border = 0;
    double x_right_border = 10 * M_PI;
    double x_step = (x_right_border - x_left_border) / x_n;

    double y_0 = 0;
    double y_n = 10;

    double c2 = (y_0 - y_n) / (x_left_border - x_right_border);
    double c1 = y_0 + ySecDer(x_left_border) - c2 * x_left_border;

    QVector<double> a_;
    QVector<double> b_;
    QVector<double> c_;
    QVector<double> d_;
    QVector<double> y_;
    QVector<double> x_;
    QVector<double> y_er_;


    bool isDrowable = false;

    void init();
    void PryamoyHod();
    void ObratniyHod();
    void find_y();
};
#endif // TASK9_H
