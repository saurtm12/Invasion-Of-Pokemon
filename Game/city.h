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
using namespace CourseSide;

namespace Model {

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


private:
     const QString BUSFILE = QString(":/offlinedata/offlinedata/final_bus_liteN.json");
     const QString STOPFILE = QString(":/offlinedata/offlinedata/full_stations_kkj3.json");

    void readOfflineData(const QString& busFile, const QString& stopFile);

    QTime *clock_;
    std::vector< std::shared_ptr<Stop> > stops_;
    std::vector< std::shared_ptr<BusData> > buses_;

};
}


#endif // CITY_H
