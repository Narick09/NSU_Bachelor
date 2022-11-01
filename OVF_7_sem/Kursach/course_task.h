#ifndef COURSE_TASK_H
#define COURSE_TASK_H

#include <QMainWindow>
#include <QTextStream>
//#include <QDate>
//#include <QTime>
#include <QFile>
#include <QDir>
#include"qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Course_task; }
QT_END_NAMESPACE

class Course_task : public QMainWindow
{
    Q_OBJECT

    void saveData();
    void printData();
    void findRR();
    void findDer();

    void setRRIntarvals();

    void approximate(QVector<double> & xSource, QVector<double> & ySource, QVector<double> & xDest, QVector<double> & yDest);

    void fullApproximate(QVector<double> & xSource, QVector<double> & ySource, QVector<double> & xDest, QVector<double> & yDest);

    void setApproximates();

public:
    Course_task(QWidget *parent = nullptr);
    ~Course_task();


    void getLagrangeFi(QVector<double> &x_k);
    double getLagrange(double x, QVector<double> &x_k, QVector<double> &y_k);
private slots:
    void on_ECG_stateChanged(int arg1);

    void on_ECG_2_stateChanged(int arg1);

    void on_ECG_3_stateChanged(int arg1);

    void on_drawBut_clicked();

    void on_findRROnDerBox_valueChanged(double arg1);

    void on_wavesBox_stateChanged(int arg1);

    void on_RRStepsBox_stateChanged(int arg1);

    void on_RR_AprBox_stateChanged(int arg1);

    void on_R_AprBox_stateChanged(int arg1);

private:
    Ui::Course_task *ui;
    QCPGraph * ECG;
    QCPGraph * ECG_Der;
    QCPGraph * ECG_RR;

    QCPGraph * RRIntervals;
    QCPGraph * RRApproximate;
//    QCPGraph * RAmplAppoximate;

    int stepToFindDer = 1;

    double derMinRR = 150; //порог для производной, выше которой смотрим Р пик
    double timeRR = 40;//+- время, где искать максимум в сигнале

    QCustomPlot * seeData;
    QCustomPlot * waveData;

    QVector <double> xQVectorECG;
    QVector <double> yQVectorECG;

    QVector <double> xDer;
    QVector <double> yDer;

    QVector <double> t_RR;
    QVector <double> RR_peaks;

    QVector <double> RR_ints;

    QVector <double> RR_apr_x;
    QVector <double> RR_apr_y;

    QVector <double> R_apr_x;
    QVector <double> R_apr_y;

    QVector <double> L_Fi_;
};
#endif // COURSE_TASK_H
