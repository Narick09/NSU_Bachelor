#include "Task4.h"
#include "ui_Task4.h"
#include <cmath>

Task4::Task4(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Task4)
{
    ui->setupUi(this);
    plot_ = ui->graphWidget;
    Points = plot_->addGraph();
    plot_d_ = ui->graphWidget_2;
    Der = plot_d_->addGraph();

    plot_->xAxis->setRange(x_min_, x_max_);
    plot_->yAxis->setRange(y_min_, y_max_);

    plot_->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot_d_->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    plot_d_->xAxis->setScaleType(QCPAxis::stLogarithmic);
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    plot_d_->xAxis->setTicker(logTicker);

    plot_d_2_ = ui->graphWidget_3;
    Der2 = plot_d_2_->addGraph();

    plot_d_2_->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    plot_d_2_->xAxis->setScaleType(QCPAxis::stLogarithmic);
    plot_d_2_->xAxis->setTicker(logTicker);

    ui->doubleSpinBoxMin->setMinimum(x_min_);
    ui->doubleSpinBoxMin->setValue(x_min_);
    ui->doubleSpinBoxMin->setMaximum(x_max_);

    ui->doubleSpinBoxMax->setMinimum(x_min_);
    ui->doubleSpinBoxMax->setValue(x_max_);
    ui->doubleSpinBoxMax->setMaximum(x_max_);

    QPen pen;
    pen.setColor(QColor(255, 0, 0));
    pen.setWidth(2);

    Points->setPen(pen);
    Points->setLineStyle(QCPGraph::lsImpulse);
    Points->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssStar, 8));
    //this->graph();// - в спин боксе
    //this->graph_on_der();
    ui->doubleSpinBoxMax->setSingleStep(1);
    ui->doubleSpinBoxMin->setSingleStep(1);

    setStep();
    delta_ = 1e-10;

    ui->spinBox->setMaximum(1000);
    ui->spinBox->setValue(n_);
    ui->spinBox->setMinimum(0);

    ui->spinBox_p->setMaximum(16);
    ui->spinBox_p->setValue(1);
}

void Task4::setStep()
{
    double a = 0.5;
    __int64 n = *((__int64*)&a);
    double b = *((double*)&(++n));
    this->mech_epsilon = (b - a)*2;
}

Task4::~Task4()
{
    delete ui;
}

double Task4::func(double x, double t, double m)
{
    return 1 / M_PI * cos(m * t - x * sin(t));
}

double Task4::simpson(double x, double a, double b, double m)
{
    return (b - a) / 6 * (func(x, a, m) + 4 * func(x, (a + b) / 2, m) + func(x, b, m));
}

double Task4::method(double x, int m) {
    double res = 0;
    double a = left_border_t_;
    double b = left_border_t_ + method_step_;

    while(a < right_border_t_){
        res += simpson(x, a, b, m);
        a += method_step_;
        b += method_step_;
    }
    return res;
}

double Task4::getBessel(double x, int m){
    return method(x, m);
}

double Task4::derivative_bessel(double x, int m) {
    double delta = delta_;
    return (getBessel(x + delta, m) - getBessel(x - delta, m)) / (2 * delta);
}

double Task4::derivative_bessel2(double x, int m) {
    double delta = delta_;
    return (getBessel(x + delta, m) - getBessel(x - delta, m));
}

void Task4::graph_on_der()
{
    double delta_der_min = delta_;
    double delta_der_max = 0.1;

    double x = 0;
    double tmp1 = 0;
    double tmp2 = 0;

    ui->textBrowser->clear();

    der_step_.clear();
    max_val_method_.clear();
    max_val_method_2_.clear();

    int steps_on_iteration = 100;

    double max_er1 = 0;
    double max_er2 = 0;

    while(delta_ <= delta_der_max){
        max_er1 = 0;
        max_er2 = 0;
        for (int i = 0; i < steps_on_iteration; ++i)
        {
            x = i * 2 * M_PI / static_cast<double>(steps_on_iteration);
            tmp1 = abs(derivative_bessel(x, 0) + getBessel(x, 1));
            tmp2 = abs(derivative_bessel2(x, 0) + getBessel(x, 1) * delta_ );
            if (tmp1 > max_er1) max_er1 = tmp1;
            if (tmp2 > max_er2) max_er2 = tmp2;
        }
        der_step_.append(delta_);
        max_val_method_.append(max_er1);
        max_val_method_2_.append(max_er2);


        delta_ *= 10;
    }

    Der->setData(der_step_, max_val_method_);
    Der2->setData(der_step_, max_val_method_2_);

    ui->textBrowser->insertPlainText(QString::number(der_step_.size()) + "\n");
    ui->textBrowser->insertPlainText(QString::number(max_val_method_.size()) + "\n");
    ui->textBrowser->insertPlainText(QString::number(max_val_method_2_.size()) + "\n");

    delta_ = delta_der_min;

    plot_d_->rescaleAxes();
    plot_d_2_->rescaleAxes();

    Der->rescaleAxes();
    Der2->rescaleAxes();

    plot_d_->replot();
    plot_d_2_->replot();
}

void Task4::graph()
{
    int delta = 100;
    double x = 0;

    x_k_.clear();
    y_k_.clear();

    for (int i = 0; i < delta; ++i)
    {
        x = i * 2 * M_PI / static_cast<double>(delta);
        x_k_.append(x);
        y_k_.append(derivative_bessel(x, 0) + getBessel(x, 1));
    }
    Points->setData(x_k_, y_k_);
}

void Task4::on_pushButton_clicked()
{
    plot_->replot();
}

void Task4::on_pushButton_3_clicked()
{
    ui->doubleSpinBoxMin->setValue(-1);
    ui->doubleSpinBoxMax->setValue(2 * M_PI + 1);

    ui->spinBox_p->setValue(9);
    plot_->replot();
}

void Task4::on_doubleSpinBoxMin_valueChanged(double arg1)
{
    this->x_min_ = arg1;
    plot_->xAxis->setRange(x_min_, x_max_);
    plot_->replot();
}

void Task4::on_doubleSpinBoxMax_valueChanged(double arg1)
{
    this->x_max_ = arg1;
    plot_->xAxis->setRange(x_min_, x_max_);
    plot_->replot();
}

void Task4::on_spinBox_valueChanged(int arg1)
{
    n_ = arg1;
    method_step_ = (right_border_t_ - left_border_t_) / n_;
    graph_on_der();
    double tmp = delta_;
    delta_ = 1e-6;
    this->graph();
    delta_ = tmp;
}

void Task4::on_spinBox_p_valueChanged(int arg1)
{
    ui->doubleSpinBoxMin->setValue(-1);
    ui->doubleSpinBoxMax->setValue(2 * M_PI + 1);

    plot_->yAxis->setRange(-1.0 * pow(10.0, -1.0 * arg1), 1.0 * pow(10.0, -1.0 * arg1));
    plot_->replot();
}
