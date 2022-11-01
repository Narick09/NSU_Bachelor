#include "task5.h"
#include "ui_task5.h"
#include <cmath>

task5::task5(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::task5)
{
    ui->setupUi(this);
    plot_ = ui->graphWidget;

    Points = plot_->addGraph();
    L_polinom = plot_->addGraph();
    N_polinom = plot_->addGraph();
    Dif_L_polinom = plot_->addGraph();
    Dif_N_polinom = plot_->addGraph();

    N_polinom->setVisible(false);
    Dif_L_polinom->setVisible(false);
    Dif_N_polinom->setVisible(false);

    plot_->xAxis->setRange(x_min_, x_max_);
    plot_->yAxis->setRange(y_min_, y_max_);

    ui->doubleSpinBoxMin->setMinimum(x_min_);
//printf("10 %e\n", x_min_);
    ui->doubleSpinBoxMin->setValue(x_min_);//x_min_ changed here wtf??? - setValue calls on_doubleSpinBoxMax/Min_valueChanged
//printf("11 %e\n", x_min_);
    ui->doubleSpinBoxMin->setMaximum(x_max_);

    ui->doubleSpinBoxMax->setMinimum(x_min_);
    ui->doubleSpinBoxMax->setValue(x_max_);
    ui->doubleSpinBoxMax->setMaximum(x_max_);

    ui->doubleSpinBoxMin_y->setMinimum(y_min_);
    ui->doubleSpinBoxMin_y->setValue(y_min_);
    ui->doubleSpinBoxMin_y->setMaximum(y_max_);

    ui->doubleSpinBoxMax_y->setMaximum(y_max_);
    ui->doubleSpinBoxMax_y->setValue(y_max_);
    ui->doubleSpinBoxMax_y->setMinimum(y_min_);

    ui->spinBox->setMaximum(15);
    ui->spinBox->setValue(k_);
    ui->spinBox->setMinimum(4);

    ui->spinBox_p->setMaximum(1000000000);

    QPen pen;
    pen.setColor(QColor(255, 0, 0));
    pen.setWidth(2);

    Points->setPen(pen);
    Points->setLineStyle(QCPGraph::lsImpulse);
    Points->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssStar, 8));

    pen.setColor(QColor(0, 255, 0));
    L_polinom->setPen(pen);
    Dif_L_polinom->setPen(pen);
    //Points->setVisible(0);
    //ui->checkBox->setTristate(true); // тройное состояние выбора!
    ui->checkBox->setChecked(true);
    ui->checkBox_L->setChecked(true);
    ui->checkBox_Pn->setChecked(true);

    this->fillRow();
    this->graph();
    ui->doubleSpinBoxMax->setSingleStep(1);
    ui->doubleSpinBoxMin->setSingleStep(1);

}

void task5::setStep()
{
    double a = 0.5;
    __int64 n = *((__int64*)&a);
    double b = *((double*)&(++n));
    this->mech_epsilon = (b - a)*2;
}

task5::~task5()
{
    delete ui;
}

void task5::fillRow(){
    x_k_.clear();
    y_k_.clear();
    Points->data().clear();
    for(k_ = 0; k_ <= n_; k_++){
        //tmp = 1.0* k_ / n_;
        x_k_.append(1.0 + (1.0 * k_ / n_) );//1 + k/n
        y_k_.append(log( x_k_[k_] ));//ln(x_k)
    }
    Points->setData(x_k_, y_k_);
    k_ = 0;
}

void task5::getLagrangeFi()
{
    this->L_Fi_.clear();
    for(int i = 0; i <= n_; i++){
        L_Fi_.append(1.0);
        for(int j = 0; j <= n_; j++){
            if (j == i) continue;
            L_Fi_[i] /= (x_k_[i] - x_k_[j]);
        }
        //L_Fi_[i] = 1 / L_Fi_[i];
    }
    //calculate Fi[i] and append into L_Fi_
}

double task5::getLagrange(double x)
{
    double tmp = 1;
    double ret = 0;
    for(int i =0; i <= n_; i++){
        for(int j = 0; j <= n_; j++){
            if (j == i) continue;
            tmp *= (x - x_k_[j]);
        }
        tmp *= L_Fi_[i] * y_k_[i];
        ret += tmp;
        tmp = 1;
    }
    return ret;
}

void task5::getNewtonFi()
{
    N_Fi_.clear();
    double p = 1;
    double s = 0;
    N_Fi_.append(y_k_[0]);

    for(int k = 1; k <= n_; k++){
        for(int i = 0; i <= k; i++){
            for(int j = 0; j <= k; j++){
                if(i == j) continue;
                p /= (x_k_[i] - x_k_[j]);
            }
            p *= y_k_[i];
            s += p;
            p = 1;
        }
        N_Fi_.append(s);
        s = 0;
    }
}

double task5::getNewton(double x)
{
    double ret = 0;

    double tmp = 1;
    for(int k = 1; k <= n_; k++){
        for(int j = 0; j < k; j++){
            tmp *= (x - x_k_[j]);
        }
        tmp *= N_Fi_[k];
        ret += tmp;
        tmp = 1;
    }

    return N_Fi_[0] + ret;
}

double task5::graph()
{
//Lagrange
    //this->L_polinom->data().clear();
    //this->Dif_L_polinom->data().clear();

    QVector <double> xL;
    QVector <double> yL;

    QVector <double> xN;
    QVector <double> yN;

    //QVector <double> yV_d;

    Dif_L_polinom->setData(xL, yL);
    Dif_N_polinom->setData(xN, yN);

    getLagrangeFi();
    getNewtonFi();

    double tmp = 0;
    double tmpN = 0;
    for(double x = x_min_; x < x_max_; x += init_step_){
        xL.append(x);
        tmp = getLagrange(x);
        yL.append(tmp);

        xN.append(x);
        tmpN = getNewton(x);
        yN.append(tmpN);

        //printf("dif: %e \n", tmp - tmpN);
        Dif_L_polinom->addData(x, tmp - log(x));
        Dif_N_polinom->addData(x, tmpN - log(x));

        //yV_d.append(tmp - log(x));

        //Dif_L_polinom->addData(x, tmp - log(x));
    }

    this->L_polinom->setData(xL, yL);
    this->N_polinom->setData(xN, yN);

    //this->Dif_L_polinom->setData(xV, yV_d);

    return 0;
}

void task5::on_pushButton_clicked()
{
    plot_->replot();
}

void task5::on_pushButton_2_clicked()
{
    this->y_min_ = -0.5;
    this->y_max_ = 1;
    this->x_min_ = -1;
    this->x_max_ = 3;
    plot_->xAxis->setRange(x_min_, x_max_);
    plot_->yAxis->setRange(y_min_, y_max_);

    ui->doubleSpinBoxMin->setValue(x_min_);
    ui->doubleSpinBoxMax->setValue(x_max_);
    ui->doubleSpinBoxMin_y->setValue(y_min_);
    ui->doubleSpinBoxMax_y->setValue(y_max_);

    plot_->replot();
}

void task5::on_pushButton_3_clicked()
{
    plot_->xAxis->setRange(0.95, 2.05);
    plot_->yAxis->setRange(-0.0001, 0.0001);
    plot_->replot();
}



void task5::on_doubleSpinBoxMin_valueChanged(double arg1)
{
    this->x_min_ = arg1;
    plot_->xAxis->setRange(x_min_, x_max_);
    plot_->replot();
}

void task5::on_doubleSpinBoxMax_valueChanged(double arg1)
{
    this->x_max_ = arg1;
    plot_->xAxis->setRange(x_min_, x_max_);
    plot_->replot();
}

void task5::on_doubleSpinBoxMin_y_valueChanged(double arg1)
{
    this->y_min_ = arg1;
    plot_->yAxis->setRange(y_min_, y_max_);
    plot_->replot();
}

void task5::on_doubleSpinBoxMax_y_valueChanged(double arg1)
{
    this->y_max_ = arg1;
    plot_->yAxis->setRange(y_min_, y_max_);
    plot_->replot();
}

void task5::on_spinBox_valueChanged(int arg1)
{
    n_ = arg1;
    this->fillRow();
    this->graph();
}



void task5::on_checkBox_stateChanged(int arg1)
{
    arg1 ? Points->setVisible(1) : Points->setVisible(0);
    plot_->replot();
}

void task5::on_checkBox_L_stateChanged(int arg1)
{
    if(ui->checkBox_Pn->isChecked())
        arg1 ? L_polinom->setVisible(1) : L_polinom->setVisible(0);
    if(ui->checkBox_Pn_Ln->isChecked())
        arg1 ? Dif_L_polinom->setVisible(1) : Dif_L_polinom->setVisible(0);
    plot_->replot();
}

void task5::on_checkBox_N_stateChanged(int arg1)
{
    if(ui->checkBox_Pn->isChecked())
        arg1 ? N_polinom->setVisible(1) : N_polinom->setVisible(0);
    if(ui->checkBox_Pn_Ln->isChecked())
        arg1 ? Dif_N_polinom->setVisible(1) : Dif_N_polinom->setVisible(0);
    plot_->replot();
}

void task5::on_checkBox_Pn_stateChanged(int arg1)
{
    if(ui->checkBox_L->isChecked())
        arg1 ? L_polinom->setVisible(1) : L_polinom->setVisible(0);
    if(ui->checkBox_N->isChecked())
        arg1 ? N_polinom->setVisible(1) : N_polinom->setVisible(0);
    plot_->replot();
}

void task5::on_checkBox_Pn_Ln_stateChanged(int arg1)
{
    if(ui->checkBox_L->isChecked())
        arg1 ? Dif_L_polinom->setVisible(1) : Dif_L_polinom->setVisible(0);
    if(ui->checkBox_N->isChecked())
        arg1 ? Dif_N_polinom->setVisible(1) : Dif_N_polinom->setVisible(0);
    plot_->replot();
}

void task5::on_spinBox_p_valueChanged(int arg1)
{
    plot_->xAxis->setRange(0.95, 2.05);
    plot_->yAxis->setRange(-0.0001 / arg1, 0.0001 / arg1);
    plot_->replot();
}
