#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("../ap_final_project/pics/bookshelf.png"));
    MainWindow w;
    w.show();
    return a.exec();
}
