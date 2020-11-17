#include "../Course/CourseLib/graphics/simplemainwindow.hh"
#include "../Course/CourseLib/creategame.hh"
#include <QApplication>
#include <mainwindow.hh>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    Interface::createGame();
    MainWindow w;
    w.show();

    return a.exec();
}
