#include "mainwindow.h"
#include "preparationwindow.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mw;
    PreparationWindow pw;
    pw.show();

    return a.exec();
}
