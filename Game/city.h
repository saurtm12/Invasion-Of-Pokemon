#ifndef CITY_H
#define CITY_H

#include "../Course/CourseLib/interfaces/icity.hh"
#include "../Course/CourseLib/interfaces/iactor.hh"
#include "../Course/CourseLib/errors/initerror.hh"
#include "../Course/CourseLib/errors/gameerror.hh"
#include "../Course/CourseLib/actors/stop.hh"
#include "../Course/CourseLib/core/location.hh"
#include "bus.hh"

#include <QGraphicsScene>
#include <QtWidgets>
#include <QTime>
#include <vector>
#include <memory>
#include <QString>
#include <QGraphicsPixmapItem>
#include <vector>
using namespace Interface;
using namespace CourseSide;

namespace Model {

class City : public Interface::ICity, public QObject
{
public:
    City(QWidget *parent = 0);
    virtual ~City();
    void setBackground(QImage &basicbackground, QImage &bigbackground);
    void setClock(QTime clock);
    void startGame();
    QGraphicsScene* getMap();

    void addStop(std::shared_ptr<IStop> stop);
    void addStop(std::shared_ptr<Stop> stop);
    void addBus(std::shared_ptr<Bus> bus);
    void addActor(std::shared_ptr<IActor> newactor);
    void removeActor(std::shared_ptr<IActor> actor);

    void actorRemoved(std::shared_ptr<IActor> actor);
    bool findActor(std::shared_ptr<IActor> actor) const;
    void actorMoved(std::shared_ptr<IActor> actor);
    std::vector<std::shared_ptr<IActor>> getNearbyActors(Location loc) const;

    bool isGameOver() const;

public slots:
    void keyPress(int command);
    void changeTime();

private:
    const QString BACKGROUND = QString(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    const QString BUS_STOP_ICON = QString(":/characters/characters/busStop.png");
    const QString BUS_ICON = QString(":/characters/characters/bus.png");

    void initBusStops();

    std::vector<std::shared_ptr<Character>> stopImgs_;

    QGraphicsScene* map_;

    bool pause_;
};

const auto HANDLEFUNCT = &City::keyPress;
}


#endif // CITY_H
