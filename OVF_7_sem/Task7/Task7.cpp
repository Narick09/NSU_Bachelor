#include "Task7.h"
#include "Task7.h"
#include "ui_Task7.h"

Task7::Task7(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Task7)
{
    ui->setupUi(this);

    plot_ = ui->widget;

    Rynge_Kytt2_ = plot_->addGraph();

    plot_->xAxis->setRange(0, 15);
    plot_->yAxis->setRange(0, 15);

    QPen pen;
    pen.setWidth(1);
    Rynge_Kytt2_->setPen(pen);
    Rynge_Kytt2_->setLineStyle(QCPGraph::lsNone);
    Rynge_Kytt2_->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssStar, 1));

    plot_->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->spinBox->setMaximum(1000000000);

//    for(double i = 6.0; i >= 3.0; i -= 0.25){
//        x_0_.append(i);
//        y_0_.append(i);
//    }

    x_0_.append(5.1);
    y_0_.append(4.9);

    change_N(n_);

    ui->endTimeBox->setMaximum(10000);
    ui->endTimeBox->setValue(t_max_);
}

Task7::~Task7()
{
    delete ui;
}
double Task7::x_derivative(double x, double y) {
    return a_ * x - b_ * x * y;
}
double Task7::y_derivative(double x, double y) {
    return c_ * x * y - d_ * y;
}

void Task7::reload()
{
    x_n_RK2_.clear();
    y_n_RK2_.clear();

//    x_n_RK2_.append(x_0_);
//    y_n_RK2_.append(y_0_);
}

void Task7::RK2()
{
    double tmpX, tmpY = 0;
    double k1x, k2x, k1y, k2y;

    tmpX = x_n_RK2_[0];//x_derivative(x_n_RK2_[count - 1], y_n_RK2_[count - 1]);
    tmpY = y_n_RK2_[0];

    step_ = (t_max_ - t_min_) / n_;

    int count = 1;
    for(double t = t_min_ + step_; t <= t_max_; t += step_) {
        k1x = x_derivative(tmpX, tmpY);//f(t, y^); y^ = (x_n, y_n)
        k1y = y_derivative(tmpX, tmpY);
        k2x = x_derivative(tmpX + k1x * step_ / (2 * alpha_), tmpY + k1y*step_ / (2 * alpha_));
        k2y = y_derivative(tmpX + step_ / (2 * alpha_)*k1x      , tmpY + k1y * step_ / (2 * alpha_));

        x_n_RK2_.append(tmpX + step_ * ((1-alpha_) * k1x + alpha_ * k2x));
        y_n_RK2_.append(tmpY + step_ * ((1-alpha_) * k1y + alpha_ * k2y));

        tmpX = x_n_RK2_[count - 1];
        tmpY = y_n_RK2_[count - 1];

        if (tmpX < x_min_axe_) x_min_axe_ = tmpX;
        if (tmpX > x_max_axe_) x_max_axe_ = tmpX;
        if (tmpY < y_min_axe_) y_min_axe_ = tmpY;
        if (tmpY > y_max_axe_) y_max_axe_ = tmpY;

        count++;
    }
}

void Task7::drawGraphs()
{
    int tmp = x_0_.size();
    reload();
    Rynge_Kytt2_->data().clear();
    Rynge_Kytt2_->setData(x_n_RK2_, y_n_RK2_);
    for(int i = 0; i < tmp; i++){
        reload();
        x_n_RK2_.append(x_0_[i]);
        y_n_RK2_.append(y_0_[i]);
        RK2();
        Rynge_Kytt2_->addData(x_n_RK2_, y_n_RK2_);
    }

    plot_->xAxis->setRange(x_min_axe_, x_max_axe_);
    plot_->yAxis->setRange(y_min_axe_, y_max_axe_);
    plot_->replot();
}

void Task7::on_spinBox_valueChanged(int arg1)
{
    n_ = arg1;
    x_min_axe_ = 100000;
    x_max_axe_ = -100000;
    y_min_axe_ = 100000;
    y_max_axe_ = -100000;
    drawGraphs();
}

void Task7::change_N(int arg)
{
    ui->spinBox->setValue(arg);
    //emit changeAmountPoints(arg);
}

void Task7::on_endTimeBox_valueChanged(double arg1)
{
    t_max_ = arg1;
    x_min_axe_ = 100000;
    x_max_axe_ = -100000;
    y_min_axe_ = 100000;
    y_max_axe_ = -100000;
    drawGraphs();
}
