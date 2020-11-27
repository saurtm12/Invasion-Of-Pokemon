#ifndef PLAYER_H
#define PLAYER_H
#include "../Course/CourseLib/interfaces/iactor.hh"
#include "../Course/CourseLib/core/location.hh"
#include "character.hh"
#include "pokemon.h"
#include <vector>
#include <QProgressBar>

namespace Model
{

class Player: public Interface::IActor, Character
{
public:
  Player(QGraphicsPixmapItem* item, Interface::Location loc, QProgressBar* bar);
  ~Player();

  Interface::Location giveLocation() const;
  void remove();
  void move(Interface::Location loc);
  bool isRemoved() const ;
  void bonusFuel(int bonus);
  void addPokemon(Pokemon pokemon);

private:
  const int MAX_FUEL = 5000;
  int fuel_;
  std::vector<Pokemon> bag_;
  QProgressBar* fuelBar_;
};

}

#endif // PLAYER_H
