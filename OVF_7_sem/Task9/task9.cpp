#include "task9.h"
#include "ui_task9.h"

Task9::Task9(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Task9)
{
    ui->setupUi(this);
    graph = ui->widget->addGraph();
    graph_er = ui->widget_er->addGraph();

    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->widget_er->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    isDrowable = false;
    ui->xMinBox->setMaximum(100000000);
    ui->xMaxBox->setMaximum(100000000);
    ui->yMinBox->setMaximum(100000000);
    ui->yMaxBox->setMaximum(100000000);

    ui->xMinBox->setMinimum(-100000000);
    ui->xMaxBox->setMinimum(-100000000);
    ui->yMinBox->setMinimum(-100000000);
    ui->yMaxBox->setMinimum(-100000000);

    ui->yMinBox->setValue(y_0);
    ui->yMaxBox->setValue(y_n);
    ui->xMinBox->setValue(x_left_border);
    ui->xMaxBox->setValue(x_right_border);

    isDrowable = true;
    draw();
}

Task9::~Task9()
{
    delete ui;
}

double Task9::ySecDer(double x)
{
    return sin(x);
}

double Task9::analiticF(double x)
{
    return c1 + c2 * x - sin(x);
}

void Task9::init() {
    x_step = (x_right_border - x_left_border) / x_n;
    double h2 = x_step * x_step;

    y_.clear();
    y_er_.clear();
    x_.clear();
    a_.clear();
    b_.clear();
    c_.clear();
    d_.clear();

    for (int i = 0; i < x_n; i++) {
        y_.append(0);
        y_er_.append(0);
        x_.append(x_left_border + x_step*i);
        a_.append(1);
        b_.append(-2);
        c_.append(1);
        d_.append(h2 * ySecDer(x_.last()));
    }
    a_[0] = 0;
    c_[x_n - 1] = 0;
    d_[0] = ySecDer(x_left_border) * h2 - y_0;
    d_[x_n - 1]= ySecDer(x_right_border) * h2 - y_n;

    c2 = (y_0 - y_n) / (x_left_border - x_right_border);
    c1 = y_0 + ySecDer(x_left_border) - c2 * x_left_border;
}

void Task9::PryamoyHod() {
    double k = 0;
    for (int j = 1; j < x_n; j++) {
        k = a_[j] / b_[j - 1];
        a_[j] = 0;
        b_[j] = b_[j] - k * c_[j - 1];
        d_[j] = d_[j] - k * d_[j - 1];
    }
}

void Task9::ObratniyHod() {
    y_[x_n - 1] = d_[x_n-1] / b_[x_n-1];
    for (int j = x_n - 2; j >= 0; j--) {
        y_[j] =  (d_[j] - c_[j] * y_[j + 1]) / b_[j];
    }
}

void Task9::find_y() {
    init();
    PryamoyHod();
    ObratniyHod();
}

void Task9::draw(){
    find_y();
    graph->setData(x_, y_);
    for(int i = 0; i < y_.size(); i++){
        y_er_[i] = abs(y_[i] - analiticF(x_[i]));
    }
    graph_er->setData(x_, y_er_);
    graph_er->rescaleAxes();
    ui->widget->xAxis->rescale();
    ui->widget->yAxis->rescale();
    ui->widget->replot();
    ui->widget_er->replot();
}

void Task9::on_xMinBox_valueChanged(double arg1)
{
    x_left_border = arg1;
    if(isDrowable) draw();
}

void Task9::on_xMaxBox_valueChanged(double arg1)
{
    x_right_border = arg1;
    if(isDrowable) draw();
}

void Task9::on_yMinBox_valueChanged(double arg1)
{
    y_0 = arg1;
    if(isDrowable) draw();
}

void Task9::on_yMaxBox_valueChanged(double arg1)
{
    y_n = arg1;
    if(isDrowable) draw();
}
