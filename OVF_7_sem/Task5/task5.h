#ifndef TASK5_H
#define TASK5_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class task5; }
QT_END_NAMESPACE

class task5 : public QMainWindow
{
    Q_OBJECT

public:
    task5(QWidget *parent = nullptr);

    void setStep();

    ~task5();

    double graph();
    void fillRow();
    void getLagrangeFi();
    double getLagrange(double x);

    void getNewtonFi();
    double getNewton(double x);
private slots:
    void on_pushButton_clicked();

    void on_doubleSpinBoxMin_valueChanged(double arg1);

    void on_doubleSpinBoxMax_valueChanged(double arg1);

    void on_doubleSpinBoxMin_y_valueChanged(double arg1);

    void on_doubleSpinBoxMax_y_valueChanged(double arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_L_stateChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_checkBox_Pn_stateChanged(int arg1);

    void on_checkBox_Pn_Ln_stateChanged(int arg1);

    void on_pushButton_3_clicked();

    void on_spinBox_p_valueChanged(int arg1);

    void on_checkBox_N_stateChanged(int arg1);

private:
    Ui::task5 *ui;

    QCustomPlot *plot_;

    QCPGraph * Points;
    QCPGraph * L_polinom;
    QCPGraph * Dif_L_polinom;

    QCPGraph * N_polinom;
    QCPGraph * Dif_N_polinom;

    const double init_step_ = 1e-3;
    double mech_epsilon = init_step_;

    //for plot
    double scale_ = 30;//range for graph
    //double x_scale_box_ = 1;//range for boxes
    double x_max_ = 3 * scale_;
    double x_min_ = -1 * scale_;
    //double y_scale_ = 1;
    double y_max_ = 1 * scale_;
    double y_min_ = -0.5 * scale_;

    int n_ = 4;
    int k_ = 0;

    QVector<double> x_k_;
    QVector<double> y_k_;

    QVector<double> L_Fi_;//коэффициенты для Лагранжа
    QVector<double> N_Fi_;

};
#endif // task5_H
