#include "reportbackhome.h"

#include <QtGui/QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Application running";
    ReportBackHome *rbh = new ReportBackHome();

    rbh->show();

    return a.exec();
}
