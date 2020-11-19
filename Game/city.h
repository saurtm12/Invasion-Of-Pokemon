#ifndef CITY_H
#define CITY_H

#include "../Course/CourseLib/interfaces/icity.hh"
#include "../Course/CourseLib/interfaces/iactor.hh"
#include "../Course/CourseLib/errors/initerror.hh"
#include "../Course/CourseLib/errors/gameerror.hh"
#include "../Course/CourseLib/offlinereader.hh"

#include <QGraphicsScene>
#include <QtWidgets>
#include <QTime>
#include <vector>
#include <memory>
#include <QString>
using namespace Interface;
class City : public Interface::ICity, public QGraphicsScene
{
public:
    City(QWidget *parent = 0);
    void setBackground(QImage &basicbackground, QImage &bigbackground);
    void setClock(QTime clock);
    void addStop(std::shared_ptr<IStop> stop);
    void startGame();
    void addActor(std::shared_ptr<IActor> newactor);
    void removeActor(std::shared_ptr<IActor> actor);
    void actorRemoved(std::shared_ptr<IActor> actor);
    bool findActor(std::shared_ptr<IActor> actor) const;
    void actorMoved(std::shared_ptr<IActor> actor);
    std::vector<std::shared_ptr<IActor>> getNearbyActors(Location loc) const;
    bool isGameOver() const;

    void readOfflineData(QString busFile, QString stopsFile);
private:


};

#endif // CITY_H
