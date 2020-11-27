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
  void move(int horizontalMultiplier, int verticalMultipler);

  bool isRemoved() const;

  void remove();

private:
  const int STEP = 4;
};

}

#endif // PLAYER_H
