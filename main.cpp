#include "QtApplication.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtApplication w;
    w.resize(1024, 800);
    w.setWindowTitle("TIC-TAC-TOE!");
    w.setWindowIcon(QIcon("C:/Users/Lenovo/Pictures/Icons/games.ico"));
    w.show();
    return a.exec();
}
