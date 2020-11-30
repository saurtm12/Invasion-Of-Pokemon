#ifndef PLAYER_H
#define PLAYER_H
#include "../Course/CourseLib/interfaces/iactor.hh"
#include "../Course/CourseLib/core/location.hh"
#include "character.hh"
#include "pokemon.h"
#include <QGridLayout>
#include <vector>

/**
 * @file player.h : define Player class.
 */
namespace Model
{

/**
 * @brief The Player class - define our main player
 * @inherits Charactor
 * @inherits IActor
 */
class Player: public Interface::IActor, public Character
{
public:
    /**
   * @brief Player constructor
   * @param pixmap : to be copied.
   * @param loc : location to be set.
   * @param max_fuel : max_fuel to be set
   * @param speed : speed to be set
   * @post Player is not in removed state.
   */
  Player(const QPixmap& pixmap, Interface::Location loc, int max_fuel, int speed);

  /**
   * @brief Player destructor
   */
  ~Player();

  /**
   * @brief giveLocation
   * @return  location of this character in city map.
   * @post exception : no throw.
   */
  Interface::Location giveLocation() const;

  /**
   * @brief remove - override virtual function.
   */
  void remove();

  /**
   * @brief move to the given location
   * @param loc : location to be moved to
   * @post : exception guarantee: no throw.
   */
  void move(Interface::Location loc);

  /**
   * @brief isRemoved - override virtual function.
   */
  bool isRemoved() const ;

  /**
   * @brief : add current fuel to the bonus.
   * @param bonus
   * @post : exception guarantee: strong.
   */
  void bonusFuel(int bonus);

  /**
   * @brief addPokemon to bag
   * @param pokemon
   * @post : exception guarantee: no throw.
   * @exception std::vector::push_back guarantee rollback property.
   */
  void addPokemon(Pokemon pokemon);

  /**
   * @brief moveDirection
   * @param horizontalMultiplier
   * @param verticalMultiplier
   * @pre move up: (0, -1), move down (0, 1), move left (-1,0), move right (0,1)
   * @post exception gurantee: strong
   * @exception if the player move beyond the edge of the map, the location is not changed.
   */
  void moveDirection(int horizontalMultiplier, int verticalMultiplier);

  /**
   * @brief getFuel
   * @return current fuel
   * @post : exception guarantee : no throw
   */
  int getFuel() const;

  /**
   * @brief getBag
   * @param parent
   * @return dialog contains all the catched pokemon.
   */
  QDialog* getBag(QWidget* parent = 0) const;

private:
    int max_fuel_ = 3000;
    int fuel_;
    int speed_;
    std::vector<Pokemon> bag_;
};

}

#endif // PLAYER_H
