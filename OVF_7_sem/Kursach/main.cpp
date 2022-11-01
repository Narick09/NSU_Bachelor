#include "course_task.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Course_task w;
    w.show();
    return a.exec();
}
