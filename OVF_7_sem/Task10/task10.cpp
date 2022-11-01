#include "task10.h"
#include "ui_task10.h"

Task10::Task10(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Task10)
{
    ui->setupUi(this);

    graph = ui->widget->addGraph();
    graph->setLineStyle(QCPGraph::lsNone);
    graph->setScatterStyle(QCPScatterStyle::ssCross);
    QPen pen;
    pen.setWidth(3);
    graph->setPen(pen);
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    isDraw = false;
    ui->NBox->setMaximum(100000);
    ui->TBox->setMaximum(100000);
    ui->NBox->setValue(N);
    ui->TBox->setValue(T);
    isDraw = true;
    draw();
}

Task10::~Task10()
{
    delete ui;
}

void Task10::draw()
{
    a_.clear();
    b_.clear();
    c_.clear();
    d_.clear();

    t_.clear();
    x_.clear();
    y_.clear();
    u_.clear();
    u_max_.clear();
    task();
    graph->setData(t_, u_max_);
    graph->rescaleAxes();
    ui->widget->replot();
}

void Task10::run_through(){
    QVector<double> a_temp(a_);
    QVector<double> b_temp(b_);
    QVector<double> c_temp(c_);
    QVector<double> d_temp(d_);

    y_.clear();

    for(int i =0 ; i < N - 1; i++){
        y_.append(0);
    }
    //Forward
    double xi = 0;
    for (int i = 1; i < N-2; i++)
    {
        xi = a_temp[i] / b_temp[i - 1];
        b_temp[i] -= xi * c_temp[i - 1];
        d_temp[i] -= xi * d_temp[i - 1];
    }

    //Backward
    y_[N - 2] = d_temp[N - 2] / b_temp[N - 2];
    for(int i = N - 3; i >= 0; i--)
    {
        y_[i] = (d_temp[i] - c_temp[i] * y_[i + 1]) / b_temp[i];
    }
}

double Task10::u_x0(double x)
{
    double tmp = (1 - x / x_L);
    return x * tmp * tmp;
}

double Task10::Lu(int m, int j){
    return (u_[m][j + 1] - 2 * u_[m][j] + u_[m][j - 1]) / (h * h);
}

void Task10::task()
{
    for(int i = 0; i <  N - 1; i++){
        a_.append(-0.5 * tau / (h * h));
        b_.append(1 + tau / (h * h));
        c_.append(-0.5 * tau / (h * h));
    }

    a_[0] = 0;
    c_[N - 2] = 0;
    //return [a, b, c]

    //u = [[u_x0(x_0 + j * h) for j in range(N + 1)]]
    QVector <double> tmp;
    for(int i = 0; i < N + 1; i++){
        tmp.append(u_x0(x_0 + i * h));//x(t = 0)
    }
    u_.append(tmp);

    for(int m = 0; m < T; m++){//time
        d_.clear();
        for(int j = 1; j < N; j++){//x
            //d_ = [u_[m][j] + 0.5 * tau * Lu(m, j) for j in range(1, N)]
            d_.append(u_[m][j] + 0.5 * tau * Lu(m, j));
        }
        run_through();//return y_
        y_.insert(0, u_0t);
        y_.append(u_Lt);
        u_.append(y_);
    }

    //u_max = [max(u[i]) for i in range(len(u))]:
    int ex_size = u_.size();
    int in_size = u_[0].size();
    double u_max_tmp = 0;
    double tmp_val = 0;
    for(int i = 0; i < ex_size; i++){
        u_max_tmp = -1e6;
        for(int j = 0; j < in_size; j++){//find max T
            tmp_val = u_[i][j];
            if(u_max_tmp < tmp_val){
                u_max_tmp = tmp_val;
            }
        }
        u_max_.append(u_max_tmp);
    }
    //printf("u_max_tmp  %d\n", y_.size());

    //t = [t_0 + tau * i for i in range(len(u))]
    for(int i = 0; i < ex_size; i++){
        t_.append(t_0 + tau * i);
    }
}

void Task10::on_NBox_valueChanged(int arg1)
{
    N = arg1;
    if(isDraw) draw();
}

void Task10::on_TBox_valueChanged(int arg1)
{
    T = arg1;
    if(isDraw) draw();
}
