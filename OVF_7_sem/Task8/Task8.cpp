#include "Task8.h"
#include "ui_Task8.h"

Task8::Task8(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Task8)
{
    isDrawable = false;

    ui->setupUi(this);

    plot_ = ui->widget;
    plot_Imp_ = ui->widget_Imp;

    Explicit_Euler_u_ = plot_->addGraph();
    Explicit_Euler_v_ = plot_->addGraph();
    Implicit_Euler_u_ = plot_Imp_->addGraph();
    Implicit_Euler_v_ = plot_Imp_->addGraph();


    QPen pen;
    pen.setWidth(1);
    Explicit_Euler_u_->setPen(pen);
    Explicit_Euler_u_->setLineStyle(QCPGraph::lsLine);
    Explicit_Euler_u_->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssStar, 1));

    pen.setColor(QColor(255, 0, 0));
    Implicit_Euler_u_->setPen(pen);
    Implicit_Euler_u_->setLineStyle(QCPGraph::lsLine);
    Implicit_Euler_u_->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssStar, 1));

    plot_->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot_Imp_->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->spinBox->setMaximum(1000000000);
    ui->spinBox->setValue(n_);
    ui->timeBox->setMaximum(1000000000);
    ui->timeBox->setValue(t_max_);

    isDrawable = true;
    drawGraphs();
}

Task8::~Task8()
{
    delete ui;
}
double Task8::u_derivative(double u, double v) {
    return a_ * u + b_ * v;
}
double Task8::v_derivative(double u, double v) {
    return c_ * u  + d_ * v;
}

void Task8::reload()
{
    u_E_exp_.clear();
    v_E_exp_.clear();

    u_E_imp_.clear();
    v_E_imp_.clear();

    t_E_.clear();
    t_E_.append(t_min_);

    u_E_exp_.append(u_0_);
    v_E_exp_.append(v_0_);

    u_E_imp_.append(u_0_);
    v_E_imp_.append(v_0_);
}

void Task8::Eiler()
{
    int count = 1;
    double tmp1 = 0;
    double tmp2 = 0;

    for(double i = t_min_ + step_; i <= t_max_; i += step_){
        t_E_.append(i);
        tmp1 = u_E_exp_[count - 1];
        tmp2 = v_E_exp_[count - 1];
        u_E_exp_.append(tmp1 + step_ * u_derivative(tmp1, tmp2));
        v_E_exp_.append(tmp2 + step_ * v_derivative(tmp1, tmp2));
        //fu - a fv - b gu - c gv - d
        tmp1 = u_E_imp_[count - 1];
        tmp2 = v_E_imp_[count - 1];
        u_E_imp_.append( (tmp1 * (1-step_) + tmp2 * step_ * b_) / (1 - step_ * (a_ + step_ * b_ * c_ + d_)) );
        v_E_imp_.append( (tmp1 * step_ * c_ + tmp2 * (1 - step_ * a_)) /  (1 - step_ * (a_ + step_ * b_ * c_ + d_)) );

        count++;
    }
}

void Task8::drawGraphs()
{
    reload();
    Eiler();
    Explicit_Euler_u_->setData(t_E_, u_E_exp_);
    Implicit_Euler_u_->setData(t_E_, u_E_imp_);
    Explicit_Euler_v_->setData(t_E_, v_E_exp_);
    Implicit_Euler_v_->setData(t_E_, v_E_imp_);

    plot_->rescaleAxes();
    plot_Imp_->rescaleAxes();
    plot_->replot();
    plot_Imp_->replot();
}

void Task8::on_spinBox_valueChanged(int arg1)
{
    n_ = arg1;
    step_ = (t_max_ - t_min_) / n_;
    if (isDrawable) drawGraphs();
}

void Task8::on_timeBox_valueChanged(int arg1)
{
    t_max_ = arg1;
    step_ = (t_max_ - t_min_) / n_;
    if (isDrawable) drawGraphs();
}
