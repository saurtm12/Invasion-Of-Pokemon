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
 * @file  city.h
 * @brief Define city class
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
     * @param parent - parent widget
     * @post the object is not in removed state after constructor. Exception guarantee: strong
     */
    City(Utils::GameSetting gameSetting, QWidget *parent = 0 );

    /**
     * @brief City destructor
     */
    ~City();

    /**
     * @brief setBackground sets the bitmap picture of the game area.
     * @param basicbackground  Normal sized picture used as the game area. Bottom left position of the picture in pixelcoordinates can be found out using the offset()-method.
     * @param bigbackground  Background of the game that is bigger than normal. Used only if doing Scrolling map-expansion. Bottom left position of the picture in pixelcoordinates can be found out using the offset()-method.
     * @pre City is in init state.
     * @post Picture for the game area is set. Exception guarantee: basic.
     * @exception InitError Setting the picture was unsuccesful or the picture was invalid.
     */
    void setBackground(QImage &basicbackground, QImage &bigbackground);

    /**
     * @brief setClock sets the time of the game clock.
     * @param clock Game clock time at the function call.
     * @pre `kello.isValid() == true`.
     * @post Time is set. Exception guarantee: nothrow.
     */
    void setClock(QTime clock);

    /**
     * @brief startGame
     * @pre logic is initialized
     * @post exception guarantee : strong
     * @exception if memory is not available, this might leak out std::bad_alloc
     */
    void startGame();

    /**
     * @brief Get city map scene
     * @return City map QGraphicsScene
     * @pre map's scene is init
     * @post exception guarantee : no throw
     */
    QGraphicsScene* getMap();

    /**
     * @brief Generate a dialog to display player's bag
     * @param parent parent widget
     * @return QDialog showing player's bag
     * @pre - game is started
     * @post - exception guarantee : basic
     * @exception if memory is not available, this might leak out std::bad_alloc
     */
    QDialog* getPlayerBag(QWidget* parent = 0) const;

    /**
     * @brief Add new stop to city's map
     * @param stop pointer to to be added stop
     * @pre map's scene is init
     * @post Exception guarantee: strong
     */
    void addStop(std::shared_ptr<IStop> stop);

    /**
     * @brief addActor adds a new actor to the city.
     * @param newactor actor to be added to the city that fulfills ActorIF.
     * @pre -
     * @post Actor is added to the city. Exception guarantee: basic.
     * @exception GameError Actor is already in the city.
     */
    void addActor(std::shared_ptr<IActor> newactor);

    /**
     * @brief Add new main player to city's map
     * @pre map's scene is init
     * @post Exception guarantee: strong
     */
    void addMainActor();

    /**
     * @brief removeActor removes the actor from the city.
     * @param actor Actor to be removed.
     * @pre City is in gamestate.
     * @post Actor is removed from the city. Exception guarantee: strong.
     * @exception std::out-of-range - The actor does not persist in city
     */
    void removeActor(std::shared_ptr<IActor> actor);

    /**
     * @brief Add new pokemon ball to city's map
     * @pre map's scene is init
     * @post Exception guarantee: strong
     */
    void addBall();

    /**
     * @brief Generate initial balls into city's map
     * @pre game setting is set
     * @post Exception guarantee: strong
     */
    void generateBalls();

    /**
     * @brief Generate random pokemon when player catches a ball
     * @pre player's item collides with a ball's item
     * @post Exception guarantee: no throw
     */
    Pokemon generatePokemon();

    /**
     * @brief actorRemoved tells the city that actor is removed ingame.
     * @param actor Actor that is set removed ingame.
     * @pre City is in gamestate. Given actor is found in the city. Actor has `actor.isRemoved() == true`.
     * @post Exception guarantee: strong.
     */
    void actorRemoved(std::shared_ptr<IActor> actor);

    /**
     * @brief findActor checks if the given actor is in the city.
     * @param actor Actor that that is looked for in the city.
     * @pre -
     * @return Boolean that tells wether the actor is in the city.
     * @post Exception guarantee: nothrow.
     */
    bool findActor(std::shared_ptr<IActor> actor) const;

    /**
     * @brief actorMoved is an operation that is used to tell wether certain actor has moved.
     * @param actor Actor that has moved.
     * @pre City is in gamestate. Given actor is found in the city.
     * @post Exception guarantee: basic.
     */
    void actorMoved(std::shared_ptr<IActor> actor);

    /**
     * @brief getNearbyActors returns actors that are close to given position.
     * @param loc Location for getting the actors close to it.
     * @pre City is in gamestate.
     * @return Vector containing actors close to the location, that pass `getLocation().isClose(loc) == true`.
     * @post Exception guarantee: strong.
     */
    std::vector<std::shared_ptr<IActor>> getNearbyActors(Location loc) const;

    /**
     * @brief Handle event when player catches a pokemon ball
     * @pre City is in gamestate.
     * @post Exception guarantee: nothrow.
     */
    void handleCollision();

    /**
     * @brief isGameOver tells wether the game is overor not.
     * @pre City is in gamestate.
     * @return `true`, if game is over, else ´false´
     * @post Exception guarantee: nothrow.
     */
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
    /**
     * @brief updateFuel is emitted when the fuel changes
     * @pre City is in gamestate.
     * @post Exception guarantee: nothrow.
     */
    void updateFuel(int fuel);

    /**
     * @brief collideBall is emitted when the player catches a pokemon ball
     * @param pokemon the pokemon that player has caught
     * @pre City is in gamestate.
     * @post Exception guarantee: nothrow.
     */
    void collideBall(Pokemon pokemon);

    /**
     * @brief gameOver is emitted when isGameOver() return true
     * @post Exception guarantee: nothrow.
     */
    void gameOver();

    /**
     * @brief actorChanged is emitted when the actor counts changed
     * @param actor the actor that changes in amount
     * @param delta amount of change
     * @pre City is in gamestate.
     * @post Exception guarantee: nothrow.
     */
    void actorChanged(std::shared_ptr<IActor> actor, int delta);
private:
    const QString BACKGROUND = QString(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    const QString BUS_STOP_ICON = QString(":/characters/characters/busStop.png");
    const QString BUS_ICON = QString(":/characters/characters/bus.png");
    const QString BALL_ICON = QString(":/characters/characters/ballIcon.png");
    const QString STEWIE_ICON = QString(":/characters/characters/stewie25.png");
    const QString BRIAN_ICON = QString(":/characters/characters/brian25.png");
    const QString PASSENGER_ICON = QString(":/characters/characters/passengerIcon.png");

    /**
     * @brief get current fuel. If multiplayer mode is activated, the fuel will be total fuel of two players
     * @pre City is in gamestate.
     * @post Exception guarantee: nothrow.
     */
    int getCurrentFuel() const;

    /**
     * @brief joinStop
     * @return true if the player join a stop successfully, else false
     * @pre -
     * @post exception guarantee: no throw
     */
    bool joinStop();

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
    Character* onBus_;

    Player* player2_;

    std::vector<Pokemon> pokemons_;
    bool pause_;
    Utils::GameSetting gameSetting_;
    bool multiplayer_;

};
const int UPDATE_INTERVAL_MS = 100;
const auto HANDLEFUNCT = &City::keyPress;
const auto SIGNAL_UPDATE_FUEL = &City::updateFuel;
const auto SIGNAL_GAME_OVER = &City::gameOver;
}


#endif // CITY_H
