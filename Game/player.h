#ifndef PLAYER_H
#define PLAYER_H
#include "../Course/CourseLib/interfaces/iactor.hh"
#include "../Course/CourseLib/core/location.hh"
#include "character.hh"
#include "pokemon.h"
#include <vector>

namespace Model
{

class Player: public Interface::IActor, Character
{
public:
    Player(QGraphicsPixmapItem* item, Interface::Location loc);
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
};

}

#endif // PLAYER_H
