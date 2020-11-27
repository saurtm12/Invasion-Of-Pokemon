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
//  void move(int horizontalMultiplier, int verticalMultiplier);

  bool isRemoved() const;

  void remove();

private:
};

}

#endif // PLAYER_H
