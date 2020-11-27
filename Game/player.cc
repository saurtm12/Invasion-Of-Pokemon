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

void Player::moveDirection(int horizontalMultiplier, int verticalMultiplier)
{
    Character::move(horizontalMultiplier, verticalMultiplier);
    --fuel_;
}

int Player::getFuel() const
{
    return fuel_;
}

void Player::remove()
{


}

void Player::move(Interface::Location loc)
{
    setTrueCoord(loc);
}

}
