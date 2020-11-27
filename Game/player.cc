#include "player.h"

namespace Model
{

Player::Player(QGraphicsPixmapItem* item, Interface::Location loc):
    Character(item, loc), fuel_(MAX_FUEL)
{
    giveStep(4);
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
    int x = getX() + horizontalMultiplier * getStep();
    int y = getY() - verticalMultiplier * getStep();
    if (x < 0 || x > WITDH || y < 0 || y > HEIGHT)
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
