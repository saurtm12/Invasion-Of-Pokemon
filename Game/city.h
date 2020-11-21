#ifndef CITY_H
#define CITY_H

#include "../Course/CourseLib/interfaces/icity.hh"
#include "../Course/CourseLib/interfaces/iactor.hh"
#include "../Course/CourseLib/errors/initerror.hh"
#include "../Course/CourseLib/errors/gameerror.hh"
#include "../Course/CourseLib/offlinereader.hh"
#include "character.hh"
#include "../Course/CourseLib/actors/stop.hh"
#include "../Course/CourseLib/core/location.hh"
#include <Utils/helpers.hh>

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

class City : public Interface::ICity, public QGraphicsScene
{
public:
    City(QWidget *parent = 0);
    virtual ~City();
    void setBackground(QImage &basicbackground, QImage &bigbackground);
    void setClock(QTime clock);
    void addStop(std::shared_ptr<IStop> stop);
    void startGame();
    QGraphicsScene* getMap();
    void addActor(std::shared_ptr<IActor> newactor);
    void removeActor(std::shared_ptr<IActor> actor);
    void actorRemoved(std::shared_ptr<IActor> actor);
    bool findActor(std::shared_ptr<IActor> actor) const;
    void actorMoved(std::shared_ptr<IActor> actor);
    std::vector<std::shared_ptr<IActor>> getNearbyActors(Location loc) const;
    bool isGameOver() const;
public slots:
    void keyPress(int command);
private:
    const QString BUSFILE = QString(":/offlinedata/offlinedata/final_bus_liteN.json");
    const QString STOPFILE = QString(":/offlinedata/offlinedata/full_stations_kkj3.json");
    const QString BACKGROUND = QString(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    const QString BUSICON = QString(":/characters/characters/busStop.png");

    void readOfflineData(const QString& busFile, const QString& stopFile);
    void addCharacter(Character& character);
    QTime *clock_;
    std::vector< std::shared_ptr<Stop> > stops_;
    std::vector< std::shared_ptr<BusData> > buses_;

    std::vector< QGraphicsPixmapItem* > stopItems_;
    void addBusStops();

    QGraphicsScene* map_;
};

const auto HANDLEFUNCT = &City::keyPress;
}


#endif // CITY_H
