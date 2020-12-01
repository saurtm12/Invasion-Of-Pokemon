#include "mainwindow.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);
    Q_INIT_RESOURCE(images);
    Q_INIT_RESOURCE(pokemon);

    MainWindow w;
    w.show();

    return a.exec();
}
