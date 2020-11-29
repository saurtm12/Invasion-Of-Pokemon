#ifndef PLAYER_H
#define PLAYER_H
#include "../Course/CourseLib/interfaces/iactor.hh"
#include "../Course/CourseLib/core/location.hh"
#include "character.hh"
#include "pokemon.h"
#include <QGridLayout>
#include <vector>

namespace Model
{

class Player: public Interface::IActor, public Character
{
public:
    Player(const QPixmap& pixmap, Interface::Location loc, int max_fuel, int speed);
    ~Player();

  Interface::Location giveLocation() const;
  void remove();
  void move(Interface::Location loc);
  bool isRemoved() const ;
  void bonusFuel(int bonus);
  void addPokemon(Pokemon pokemon);
  void moveDirection(int horizontalMultiplier, int verticalMultiplier);

  int getFuel() const;
  QDialog* getBag(QWidget* parent = 0) const;

private:
    int max_fuel_ = 3000;
    int fuel_;
    int speed_;
    std::vector<Pokemon> bag_;
};

}

#endif // PLAYER_H
