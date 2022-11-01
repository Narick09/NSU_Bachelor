#include "task2.h"

#include <QApplication>

#include<iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;
double funct(double value, double u, double a){
    return value + u + a;
}

int main(int argc, char *argv[])
{
    QApplication ap(argc, argv);
    Task2 w;
    w.show();
    //--------------------------------------------
    //General parameters
    /*    cout << "SETTING GENERAL PARAMETERS" << endl;
        double u, a;
        cout << "Insert the depth (U) and the width (A) of the hole:" << endl;
        cin >> u >> a;
        double e, el, er;
        cout << "Insert the search region (left and right border):" << endl;
        cin >> el >> er;
        if (el > er)
        {
            er = el + er;
            el = er - el;
        }
        double eq = el;

        //Method 1
        cout << endl << "COMPUTING ROOT WITH METHOD 1" << endl;
        double p;
        cout << "Insert the precision:" << endl;
        cin >> p;
        int n = 0;

        while (er - el > p)
        {
            if (funct((er + el) / 2, u, a) * funct(er, u, a) < 0)
                el = (er + el) / 2;
            else
                er = (er + el) / 2;
            n++;
        }

        e = (er + el) / 2;

        cout << "Method 1 found root " << e << " with precision " << p << " in " << n << " steps." << endl;

        //Method 2
        cout << endl << "COMPUTING ROOT WITH METHOD 2" << endl;
        double es;
        cout << "Insert the starting point:" << endl;
        cin >> es;
        cout << "Insert the precision:" << endl;
        cin >> p;
        n = 0;
        el = eq;

        while (funct(es, u, a) > p)
        {
            es = es + funct(es, u, a) / funct(el, u, a);
            n++;
        }

        e = es;

        cout << "Method 2 found root " << e << " with precision " << p << " in " << n << " steps." << endl;*/
    //--------------------------------------------
    return ap.exec();
}
