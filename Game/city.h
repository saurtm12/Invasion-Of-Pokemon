#ifndef CITY_H
#define CITY_H

#include "../Course/CourseLib/interfaces/icity.hh"
#include "../Course/CourseLib/interfaces/iactor.hh"
#include "../Course/CourseLib/errors/initerror.hh"
#include "../Course/CourseLib/errors/gameerror.hh"
#include "../Course/CourseLib/actors/stop.hh"
#include "../Course/CourseLib/core/location.hh"
#include "character.hh"
#include "player.h"
#include "Utils/helpers.hh"
#include "./pokemon.h"

#include <QGraphicsScene>
#include <QtWidgets>
#include <QWidget>
#include <QTime>
#include <vector>
#include <memory>
#include <QString>
#include <QGraphicsPixmapItem>
#include <vector>
#include <unordered_map>

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
    void addActor(std::shared_ptr<IActor> newactor);
    void addMainActor();
    void removeActor(std::shared_ptr<IActor> actor);

    void addBall();
    void generateBalls();

    void actorRemoved(std::shared_ptr<IActor> actor);
    bool findActor(std::shared_ptr<IActor> actor) const;
    void actorMoved(std::shared_ptr<IActor> actor);
    std::vector<std::shared_ptr<IActor>> getNearbyActors(Location loc) const;

    bool isGameOver() const;

public slots:
    void keyPress(int command);
    void changeTime();
signals:
    void updateFuel(int fuel);
private:
    const QString BACKGROUND = QString(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    const QString BUS_STOP_ICON = QString(":/characters/characters/busStop.png");
    const QString BUS_ICON = QString(":/characters/characters/bus.png");
    const QString BALL_ICON = QString(":/characters/characters/ballIcon.png");
    const QString STEWIE_ICON = QString(":/characters/characters/stewie25.png");

    const int BALLS_PER_TURN = 5;

    // FIX THIS
    const QString PASSENGER_ICON = QString(":/characters/characters/passengerIcon.png");
    int WITDH = 1095;
    int HEIGHT = 592;

    QTime clock_;

    std::unordered_map<std::shared_ptr<IActor>, std::shared_ptr<Character>> actorsMap_;
    std::unordered_map<std::shared_ptr<IStop>, std::shared_ptr<Character>> stopsMap_;
    std::vector< std::shared_ptr<Character> > ballsMap_;

    QGraphicsScene* map_;
    std::shared_ptr<Player> player_;
    std::vector<Pokemon> pokemons_;
    bool pause_;
};

const auto HANDLEFUNCT = &City::keyPress;
}


#endif // CITY_H
