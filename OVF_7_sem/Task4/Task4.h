#ifndef Task4_H
#define Task4_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QVector>
#include "cmath"

QT_BEGIN_NAMESPACE
namespace Ui { class Task4; }
QT_END_NAMESPACE

class Task4 : public QMainWindow
{
    Q_OBJECT

public:
    Task4(QWidget *parent = nullptr);

    void setStep();

    ~Task4();

    double func(double x, double t, double m);
    double simpson(double x, double a, double b, double m);


    void graph();
    double method(double x, int m);
    double getBessel(double x, int m);
    double derivative_bessel(double x, int m);
    double derivative_bessel2(double x, int m);

    void graph_on_der();
private slots:
    void on_pushButton_clicked();

    void on_doubleSpinBoxMin_valueChanged(double arg1);

    void on_doubleSpinBoxMax_valueChanged(double arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_3_clicked();

    void on_spinBox_p_valueChanged(int arg1);

private:
    Ui::Task4 *ui;

    QCustomPlot * plot_;
    QCPGraph * Points;
    QCustomPlot * plot_d_;
    QCPGraph * Der;
    QCustomPlot * plot_d_2_;
    QCPGraph * Der2;


    const double init_step_ = 1e-3;
    double mech_epsilon = init_step_;

    int n_ = 512;

    double left_border_t_ = 0;
    double right_border_t_ = M_PI;

    double method_step_ = (right_border_t_ - left_border_t_) / n_;

    //for plot
    double x_max_ = (2 * M_PI + 1);
    double x_min_ = (0 - 1);
    double y_max_ = 1;
    double y_min_ = -0.5;

    double delta_ = 1e-10;

    QVector<double> x_k_;
    QVector<double> y_k_;

    QVector<double> der_step_;
    QVector<double> max_val_method_;
    QVector<double> max_val_method_2_;

};
#endif // Task4_H
