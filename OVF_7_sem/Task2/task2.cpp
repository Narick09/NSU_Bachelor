#include "task2.h"
#include "ui_task2.h"
#include <cmath>

Task2::Task2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Task2)
{
    ui->setupUi(this);
    plot_ = ui->graphWidget;
    plot_->addGraph();
    plot_->xAxis->setRange(x_min_* x_scale_ * x_scale_box_, x_max_ * x_scale_ * x_scale_box_);
    plot_->yAxis->setRange(y_min_, y_max_);

    ui->doubleSpinBoxMin->setMinimum(x_min_ * x_scale_box_);
//printf("10 %e\n", x_min_);
    ui->doubleSpinBoxMin->setValue(x_min_ * x_scale_box_);//x_min_ changed here wtf??? - setValue calls on_doubleSpinBoxMax/Min_valueChanged
//printf("11 %e\n", x_min_);
    ui->doubleSpinBoxMin->setMaximum(x_max_ * x_scale_box_);

    ui->doubleSpinBoxMax->setMinimum(x_min_ * x_scale_box_);
    ui->doubleSpinBoxMax->setValue(x_max_ * x_scale_box_);
    ui->doubleSpinBoxMax->setMaximum(x_max_ * x_scale_box_);

    ui->doubleSpinBoxMin_y->setMinimum(y_min_);
    ui->doubleSpinBoxMin_y->setValue(y_min_);
    ui->doubleSpinBoxMin_y->setMaximum(y_max_);

    ui->doubleSpinBoxMax_y->setMaximum(y_max_);
    ui->doubleSpinBoxMax_y->setValue(y_max_);
    ui->doubleSpinBoxMax_y->setMinimum(y_min_);

    plot_->addGraph();
    plot_->addGraph();
    plot_->addGraph();
    plot_->addGraph();

    this->graph();
    ui->doubleSpinBoxMax->setSingleStep(x_scale_box_);
    ui->doubleSpinBoxMin->setSingleStep(x_scale_box_);

    ui->lambda->setMaximum(1000000000000);
    ui->lambda->setValue(lambda_);
}

void Task2::setStep()
{
    double a = 0.5;
    __int64 n = *((__int64*)&a);
    double b = *((double*)&(++n));
    this->mech_epsilon = (b - a)*2;
}

Task2::~Task2()
{
    delete ui;
}

double Task2::func(double E){
    double ksi = -1.0 * E / U0_;
    double var = sqrt(m_2_a_sqwared_devided_h_sqwared_ * U0_ * (1 - ksi));
    double left_cotan = tan((M_PI/2) - var);
    double right_sqr = sqrt((1 / ksi) - 1);
    return left_cotan - right_sqr;
}

double Task2::derr_func(double E_n)
{
    return (this->func(E_n + this->mech_epsilon) - this->func(E_n - this->mech_epsilon)) / (2 * this->mech_epsilon);
}


double Task2::graph()
{
    QPen pen;
    pen.setColor(QColor(255, 0, 0));
    pen.setWidth(3);
    for(double i = -1e-12; i >= -1 * U0_; i-=this->init_step_){
        energies.append(i);
        eq.append(this->func(i));
        //printf("%e,   %e\n", i, this->func(i));
    }
    plot_->graph(0)->setData(energies, eq);
    plot_->graph(0)->setPen(pen);
    //plot_->graph(0)->setBrush(QBrush(QColor(255,0,0,255)));//QColor(r,g,b, непрозрачность)
    return 0;
}

double Task2::tmpFunc(double x)
{
    return 0.0;
}

void Task2::dihotomyMethod()
{
    double min = -1 * U0_;
    double max = 0;
    this->setStep();

    ui->Dihotomy_val->clear();

    while(max-min > mech_epsilon){
        if(this->func(min) * this->func(0.5*(min + max)) <= 0){
            max = 0.5*(min + max);
        } else {
            min = 0.5*(min + max);
        }
    }

    this->dih = min;
    //plot_->addGraph();
    plot_->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 9));
    plot_->graph(1)->addData(min, func(min));
    plot_->graph(1)->addData(max, func(max));
    ui->Dihotomy_val->insertPlainText(QString::number((min + max) / 2, 'f', 20));
}

void Task2::on_pushButton_clicked()
{
    this->dihotomyMethod();
    plot_->replot();
}

void Task2::on_doubleSpinBoxMin_valueChanged(double arg1)
{
    this->x_min_ = arg1 / x_scale_box_;
    plot_->xAxis->setRange(x_min_ * x_scale_ * x_scale_box_, x_max_ * x_scale_ * x_scale_box_);
    plot_->replot();
}

void Task2::on_doubleSpinBoxMax_valueChanged(double arg1)
{
    this->x_max_ = arg1 / x_scale_box_;
    plot_->xAxis->setRange(x_min_ * x_scale_ * x_scale_box_, x_max_ * x_scale_ * x_scale_box_);
    plot_->replot();
}

void Task2::on_doubleSpinBoxMin_y_valueChanged(double arg1)
{
    this->y_min_ = arg1;
    plot_->yAxis->setRange(y_min_, y_max_);
    plot_->replot();
}

void Task2::on_doubleSpinBoxMax_y_valueChanged(double arg1)
{
    this->y_max_ = arg1;
    plot_->yAxis->setRange(y_min_, y_max_);
    plot_->replot();
}

void Task2::on_pushButton_2_clicked()
{
    double x_0 = -8e-6;//dih;//-1 * U0_/2;
    double lambda = 1 / derr_func(dih);
    QPen pen;
    pen.setColor(QColor(0, 0, 255));

    ui->Iterations_val->clear();
    double x_next = x_0;
    double x_prev = 0;
    printf("%e, %e\n", x_next, lambda);
    QVector<double> appr;
    QVector<double> en;

    while(abs(x_next - x_prev) >= mech_epsilon){
        //tmp = x_prev;
        x_prev = x_next;
        x_next = x_prev - this->func(x_prev) * lambda;
        //printf("%e, %e\n", x_next, x_prev);
    }
    printf("END: %e, %e\n", x_next, x_prev);

    ui->Iterations_val->insertPlainText(QString::number(x_prev, 'f', 20));

    plot_->graph(2)->setData(en, appr);
    plot_->graph(2)->setPen(pen);
    plot_->graph(2)->setLineStyle(QCPGraph::lsImpulse);
    plot_->replot();
    printf("\n===\n");
}

void Task2::on_pushButton_3_clicked()
{
    QPen pen;
    pen.setColor(QColor(0, 0, 255));
    pen.setWidth(1);
//    pen.setStyle(QCP);

    double x_0 = -2e-6;//dih;//-85 * 1e-7;
    //printf("Г0: %e, %e\n", U0_, x_0);
    double tmp = 0;
    double x_next = x_0;
    double x_prev = 0;

    QVector<double> appr;
    QVector<double> en;
    tmp = this->func(x_next);
    en.append(x_next + 2 * mech_epsilon);
    appr.append(0);
    en.append(x_next);
    appr.append(tmp);

    ui->Newton_val->clear();

    while(abs(x_next - x_prev) >= mech_epsilon){
        x_prev = x_next;
        //tmp = func(x_next);
        x_next = x_next - tmp / derr_func(x_next);

        en.append(x_next + 2 * mech_epsilon);
        appr.append(0);

        tmp = func(x_next);
        en.append(x_next);
        appr.append(tmp);
        //printf("%e, %e\n", x_next, x_prev);
    }
    //printf("%d, %d  &&\n\n", en.size(), appr.size());

    ui->Newton_val->insertPlainText(QString::number(x_prev, 'f', 20));

//    for(int i = 0; i < en.size(); i++){
//        printf("%e, %e\n", en[i], appr[i]);
//    }


    plot_->graph(3)->setPen(pen);
    plot_->graph(3)->setLineStyle(QCPGraph::lsLine);
    plot_->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCrossSquare, 5));
    plot_->graph(3)->setData(en, appr);

    plot_->replot();
    printf("\n===\n");
}

void Task2::on_lambda_valueChanged(double arg1)
{
    lambda_ = arg1;
}
