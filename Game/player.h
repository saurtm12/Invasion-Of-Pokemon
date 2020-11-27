#ifndef PLAYER_H
#define PLAYER_H
#include "../Course/CourseLib/interfaces/iactor.hh"
#include "../Course/CourseLib/core/location.hh"
#include "character.hh"

namespace Model
{

class Player: public Interface::IActor, Character
{
public:
  Player(QGraphicsPixmapItem* item, Interface::Location loc);
  ~Player();

  Interface::Location giveLocation() const;
  void move(Interface::Location loc);

  bool isRemoved() const;

  void remove();
};

}

#endif // PLAYER_H
