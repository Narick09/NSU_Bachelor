#include "Task6.h"
#include "ui_Task6.h"

Task6::Task6(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Task6)
{
    ui->setupUi(this);

    plot_ = ui->widget;

    EXP = plot_->addGraph();

    Eiler_ = plot_->addGraph();

    Rynge_Kytt2_ = plot_->addGraph();

    Rynge_Kytt4_ = plot_->addGraph();

    plot_->xAxis->setRange(t_min_, t_max_);
    plot_->yAxis->setRange(x_min_, x_max_);

    QPen pen;
    pen.setWidth(2);
    Rynge_Kytt2_->setPen(pen);

    pen.setColor(QColor(255, 0, 255));

    Eiler_->setPen(pen);
    Eiler_->setLineStyle(QCPGraph::lsLine);
    Eiler_->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot, 3));

    pen.setColor(QColor(255, 110, 40));
    Rynge_Kytt4_->setPen(pen);

    plot_->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    reload();

    drawGraphs();

    ui->eilerBox->setChecked(true);
//    ui->rk2Box->setChecked(false);
//    ui->rk4Box->setChecked(false);
    on_rk2Box_stateChanged(0);
    on_rk4Box_stateChanged(0);

    ui->alphaSpinBox->setValue(1);
    ui->alphaSpinBox->setMaximum(1);
    ui->alphaSpinBox->setMinimum(0.01);

    for(double i = t_min_; i <= t_max_; i += step_){
        t_n_exp_.append(i);
        x_n_exp_.append(exp(-1.0*i));
    }
    EXP->setData(t_n_exp_, x_n_exp_);

    pen.setWidth(1);
    pen.setColor(QColor(0, 255, 0));

    EXP->setPen(pen);
}

Task6::~Task6()
{
    delete ui;
}

void Task6::setStep()
{
    double a = 0.5;
    __int64 n = *((__int64*)&a);
    double b = *((double*)&(++n));
    this->mech_epsilon = (b - a)*2;
}

double Task6::func(double x)
{
    return -1.0 * x;
}

void Task6::reload()
{
    t_n_E_.clear();
    x_n_E_.clear();

    t_n_E_.append(t_0_);
    x_n_E_.append(x_0_);

    t_n_RK2_.clear();
    x_n_RK2_.clear();

    t_n_RK2_.append(t_0_);
    x_n_RK2_.append(x_0_);

    t_n_RK4_.clear();
    x_n_RK4_.clear();

    t_n_RK4_.append(t_0_);
    x_n_RK4_.append(x_0_);
}

double Task6::Eiler()
{
    //reload();
    int count = 1;
    double tmp = 0;
    for(double i = t_min_ + step_; i <= t_max_; i += step_){
        t_n_E_.append(i);
        tmp = x_n_E_[count - 1];
        x_n_E_.append(tmp + step_ * func(tmp));
        count++;
        //printf("%e\n", i);
    }
    return 0;
}

void Task6::RK2()
{
    //reload();
    int count = 1;
    double tmp = 0;
    double k1, k2;

    for(double i = t_min_ + step_; i <= t_max_; i += step_){
        t_n_RK2_.append(i);

        tmp = x_n_RK2_[count - 1];
        k1 = func(tmp);
        k2 = func(tmp + step_ / (2 * alpha_) * k1);

        x_n_RK2_.append(tmp + step_ * ((1-alpha_) * k1 + alpha_ * k2));
        count++;
        //printf("%e\n", i);
    }
}

void Task6::RK4()
{
    int count = 1;
    double tmp = 0;
    double k1, k2, k3, k4;

    for(double i = t_min_ + step_; i <= t_max_; i += step_){
        t_n_RK4_.append(i);

        tmp = x_n_RK4_[count - 1];
        k1 = func(tmp);
        k2 = func(tmp + step_ / 2 * k1);
        k3 = func(tmp + step_ / 2 * k2);
        k4 = func(tmp + step_ * k3);
        x_n_RK4_.append(tmp + step_/6 * (k1 + 2*k2 + 2*k3 + k4));
        count++;
        //printf("%e\n", i);
    }
}

void Task6::drawGraphs()
{
    reload();
    Eiler();
    Eiler_->setData(t_n_E_, x_n_E_);
    Eiler_->rescaleValueAxis();

    RK2();
    Rynge_Kytt2_->setData(t_n_RK2_, x_n_RK2_);
    //Rynge_Kytt2_->rescaleValueAxis();

    RK4();
    Rynge_Kytt4_->setData(t_n_RK4_, x_n_RK4_);
    //Rynge_Kytt4_->rescaleValueAxis();

    plot_->replot();


}

void Task6::on_eilerBox_stateChanged(int arg1)
{
    arg1 ? Eiler_->setVisible(true) : Eiler_->setVisible(false);
    plot_->replot();
}

void Task6::on_rk2Box_stateChanged(int arg1)
{
    arg1 ? Rynge_Kytt2_->setVisible(true) : Rynge_Kytt2_->setVisible(false);
    plot_->replot();
}

void Task6::on_alphaSpinBox_valueChanged(double arg1)
{
    this->alpha_ = arg1;
    drawGraphs();
}

void Task6::on_rk4Box_stateChanged(int arg1)
{
    arg1 ? Rynge_Kytt4_->setVisible(true) : Rynge_Kytt4_->setVisible(false);
    plot_->replot();
}
