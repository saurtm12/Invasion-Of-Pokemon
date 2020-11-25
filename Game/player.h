#ifndef PLAYER_H
#define PLAYER_H
#include "../Course/CourseLib/interfaces/iactor.hh"
#include "../Course/CourseLib/core/location.hh"

class player: public Interface::IActor
{
public:
  player();
  ~player();
  Interface::Location giveLocation() const;
  void move(Interface::Location loc);
};

#endif // PLAYER_H
