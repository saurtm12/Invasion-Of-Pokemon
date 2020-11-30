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
#include "pokemon.h"

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

/**
 * @file Define city class
 */

using namespace Interface;
using namespace CourseSide;

namespace Model {

/**
 * @brief The City class
 * @inherits QObject - to use signal - slot mechanism
 * @inherits Icity - used courseSide logic
 */
class City :  public QObject, public Interface::ICity
{
    Q_OBJECT
public:
    /**
     * @brief City constructor
     * @param gameSetting - give game setting has been chosen.
     * @param parent - QObject parent
     * @post the object is not in removed state after constructor
     */
    City(Utils::GameSetting gameSetting, QWidget *parent = 0 );

    /**
     * @brief City destructor
     */
    ~City();



    /**
     * @brief setBackground - override Icity function
     * @param basicbackground - city background
     * @param bigbackground - NOT USED
     * @pre - city is initialized
     * @post - exception guarantee : no throw
     */
    void setBackground(QImage &basicbackground, QImage &bigbackground);

    /**
     * @brief setClock - override ICity function
     * @param clock
     * @pre time change within city minute
     * @post - exception guarantee : no throw
     */
    void setClock(QTime clock);

    /**
     * @brief startGame
     * @pre - logic is initialized
     * @post - exception guarantee : no throw
     * @exception if memory is not available, this might leak out std::bad_alloc
     */
    void startGame();

    /**
     * @brief getMap - get city map
     * @return City map QGraphicScene
     * @post - exception guarantee : no throw
     */
    QGraphicsScene* getMap();

    /**
     * @brief getPlayerBag - display player's bag
     * @param parent - QObject parent
     * @return QDialog
     * @pre - game is started
     * @post - exception guarantee : no throw
     * @exception if memory is not available, this might leak out std::bad_alloc
     */
    QDialog* getPlayerBag(QWidget* parent = 0) const;

    /**
     * @brief addStop to city's map
     * @param stop
     * @pre -
     * @post - exception guarantee: no throw
     */
    void addStop(std::shared_ptr<IStop> stop);

    /**
     * @brief addActor
     * @param newactor
     * @pre -
     * @post - exception guarantee: no throw.
     */
    void addActor(std::shared_ptr<IActor> newactor);
    void addMainActor();
    void removeActor(std::shared_ptr<IActor> actor);

    void addBall();
    void generateBalls();
    Pokemon generatePokemon();

    void actorRemoved(std::shared_ptr<IActor> actor);
    bool findActor(std::shared_ptr<IActor> actor) const;
    void actorMoved(std::shared_ptr<IActor> actor);
    std::vector<std::shared_ptr<IActor>> getNearbyActors(Location loc) const;

    void handleCollision();

    bool isGameOver() const;

public slots:
    /**
     * @brief keyPress
     * @param command
     * @pre -
     * @post exception guarantee : no throw.
     */
    void keyPress(int command);

    /**
     * @brief onTimeIncreased - move the player if he is in the bus and pokemon ball
     * @pre -
     * @post exception guarantee : no throw.
     */
    void onTimeIncreased();
signals:
    void updateFuel(int fuel);
    void collideBall(Pokemon pokemon);
    void gameOver();
    void actorChanged(std::shared_ptr<IActor> actor, int delta);
private:
    const QString BACKGROUND = QString(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    const QString BUS_STOP_ICON = QString(":/characters/characters/busStop.png");
    const QString BUS_ICON = QString(":/characters/characters/bus.png");
    const QString BALL_ICON = QString(":/characters/characters/ballIcon.png");
    const QString STEWIE_ICON = QString(":/characters/characters/stewie25.png");
    const QString PASSENGER_ICON = QString(":/characters/characters/passengerIcon.png");


    int WIDTH = 1095;
    int HEIGHT = 592;

    QTime clock_;
    QTimer timer_;
    std::unordered_map<std::shared_ptr<IActor>, Character*> actorsMap_;
    std::unordered_map<std::shared_ptr<IStop>, Character* > stopsMap_;
    std::vector< Character* > ballsMap_;

    QGraphicsScene* map_;
    Player* player_;
    bool isInStop;
    bool isInBus;
    bool isLocked;
    bool stopNextStop;
    Character* onBus_;
    std::vector<Pokemon> pokemons_;
    bool pause_;
    Utils::GameSetting gameSetting_;
    bool joinStop();
};
const int UPDATE_INTERVAL_MS = 100;
const auto HANDLEFUNCT = &City::keyPress;
const auto SIGNAL_UPDATE_FUEL = &City::updateFuel;
const auto SIGNAL_GAME_OVER = &City::gameOver;
}


#endif // CITY_H
