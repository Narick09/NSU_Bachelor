#include "Task3.h"
#include "ui_Task3.h"
#include <cmath>

Task3::Task3(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Task3)
{
    ui->setupUi(this);

    ui->spinBox->setValue(n_3a_);
    ui->spinBox->setMinimum(2);

    ui->spinBox_2->setValue(n_3b_);
    ui->spinBox_2->setMinimum(2);

    ui->spinBox->setSingleStep(2);
    ui->spinBox_2->setSingleStep(2);

    plot1_ = ui->widget1;
    plot2_ = ui->widget2;
    plot3_ = ui->widget3;

    func1_ = plot1_->addGraph();
    trap4_ = plot1_->addGraph();

    func2_ = plot2_->addGraph();
    trap16_ = plot2_->addGraph();

    func3_ = plot3_->addGraph();
    trap32_ = plot3_->addGraph();

    plot1_->xAxis->setRange(x_min_b_, x_max_b_);
    plot1_->yAxis->setRange(0, 3);
    plot2_->xAxis->setRange(x_min_b_, x_max_b_);
    plot2_->yAxis->setRange(0, 3);
    plot3_->xAxis->setRange(x_min_b_, x_max_b_);
    plot3_->yAxis->setRange(0, 3);
    QPen pen;

    trap4_->setLineStyle(QCPGraph::lsStepRight);
    trap16_->setLineStyle(QCPGraph::lsStepRight);
    trap32_->setLineStyle(QCPGraph::lsStepRight);

    pen.setColor(QColor(255, 0, 0));
    func1_->setPen(pen);
    func2_->setPen(pen);
    func3_->setPen(pen);

    graph();
    fillTraps();
}

void Task3::setStep()
{
    double a = 0.5;
    __int64 n = *((__int64*)&a);
    double b = *((double*)&(++n));
    this->mech_epsilon_ = (b - a)*2;
}

double Task3::func_3a(double x)
{
    return 1/(1 + x*x);
}

double Task3::func_3b(double x)
{
    return pow(x, 1.0/3) * exp(sin(x));
}

double Task3::trapezoid_3a()
{
    double res = 0;
    double min = x_min_a_;
    while(min < x_max_a_){
        res += (func_3a(min) + func_3a(min + step_3a)) * (step_3a) / 2;
        min += step_3a;
    }
    return res;
}

double Task3::trapezoid_3b()
{
    double res = 0;
    double tmp = 0;
    double min = x_min_b_;
    if(isGraph_){
        tmpX_.clear();
        tmpY_.clear();
        tmpX_.append(0);
        tmpY_.append(0);
    }
    while(min < x_max_b_){
        tmp = (func_3b(min) + func_3b(min + step_3b)) * (step_3b) / 2;
        res += tmp;
        min += step_3b;
        if(isGraph_){
            tmpX_.append(min);
            tmpY_.append(tmp);
        }
    }
    return res;
}

double Task3::simpson_3a()
{
    double res = 0;
    double min = x_min_a_;
    while(min < x_max_a_){
        res += step_3a * (func_3a(min) + 4 * func_3a( (min + min + step_3a) / 2 ) + func_3a(min + step_3a)) / 6;
        min += step_3a;
    }
    return res;
}

double Task3::simpson_3b()
{
    double res = 0;
    double min = x_min_b_;

    while(min < x_max_b_){
        res += step_3b * (func_3b(min) + 4 * func_3b( (min + min + step_3b) / 2 ) + func_3b(min + step_3b)) / 6;
        min += step_3b;
    }
    return res;
}

void Task3::graph()
{
    double delta = 1e-5;
    double a = x_min_b_;
    QVector<double> x;
    QVector<double> y;

    while(a < x_max_b_){
        x.append(a);
        y.append(func_3b(a));
        a += delta;
    }
    func1_->setData(x, y);
    func2_->setData(x, y);
    func3_->setData(x, y);

    replotAll();
}

void Task3::fillTraps()
{
    double tmp = step_3b;
    isGraph_ = true;

    step_3b = (x_max_b_ - x_min_b_) / 4;
    trapezoid_3b();
    trap4_->setData(tmpX_, tmpY_);

    step_3b = (x_max_b_ - x_min_b_) / 16;
    trapezoid_3b();
    trap16_->setData(tmpX_, tmpY_);

    step_3b = (x_max_b_ - x_min_b_) / 32;
    trapezoid_3b();
    trap32_->setData(tmpX_, tmpY_);

    isGraph_ = false;
    step_3b = tmp;

    replotAll();
}

void Task3::replotAll()
{
    plot1_->replot();
    plot2_->replot();
    plot3_->replot();
}

Task3::~Task3()
{
    delete ui;
}

void Task3::on_spinBox_valueChanged(int arg1)
{
    n_3a_ = arg1;
    step_3a = (x_max_a_ - x_min_a_) / n_3a_;
    ui->return_3aT->clear();
    ui->return_3aS->clear();
    ui->return_3aT->insertPlainText(QString::number(trapezoid_3a()));
    ui->return_3aS->insertPlainText(QString::number(simpson_3a()));

    //printf("%e\n", trapezoid_3a());
}

void Task3::on_spinBox_2_valueChanged(int arg1)
{
    n_3b_ = arg1;
    step_3b = (x_max_b_ - x_min_b_) / n_3b_;
    ui->return_3bT->clear();
    ui->return_3bS->clear();
    ui->return_3bT->insertPlainText(QString::number(trapezoid_3b()));
    ui->return_3bS->insertPlainText(QString::number(simpson_3b()));

    //printf("%e\n", trapezoid_3b());
}

void Task3::on_but_gr_1_clicked()
{
    plot1_->yAxis->setRange(0, 3);
    plot1_->replot();
}

void Task3::on_but_step_1_clicked()
{
    plot1_->yAxis->setRange(0, 0.6);
    plot1_->replot();
}

void Task3::on_but_gr_2_clicked()
{
    plot2_->yAxis->setRange(0, 3);
    plot2_->replot();
}

void Task3::on_but_step_2_clicked()
{
    plot2_->yAxis->setRange(0, 0.15);
    plot2_->replot();
}

void Task3::on_but_gr_3_clicked()
{
    plot3_->yAxis->setRange(0, 3);
    plot3_->replot();
}

void Task3::on_but_step_3_clicked()
{
    plot3_->yAxis->setRange(0, 0.08);
    plot3_->replot();
}
