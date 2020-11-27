#include "player.h"

namespace Model
{

Player::Player(QGraphicsPixmapItem* item, Interface::Location loc):
    Character(item, loc)
//    fuelBar_(bar)
{

}

Player::~Player()
{

}

Interface::Location Player::giveLocation() const
{
    return getLocation();
}

bool Player::isRemoved() const
{

}

void Player::addPokemon(Pokemon pokemon)
{
    bag_.push_back(pokemon);
}

void Player::move(int horizontalMultiplier, int verticalMultiplier)
{
    int x = getX() + horizontalMultiplier * step;
    int y = getY() - verticalMultiplier * step;
    if (x < OFFSET || x > WITDH || y < OFFSET || y > HEIGHT)
    {
        return;
    }
    Character::setCoord(x,y);
    fuel_--;
}

void Player::remove()
{


}

void Player::move(Interface::Location loc)
{
    setTrueCoord(loc);
}

}
