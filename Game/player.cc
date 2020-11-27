#include "player.h"

namespace Model
{

Player::Player(QGraphicsPixmapItem* item, Interface::Location loc):
    Character(item, loc),
    fuel_(MAX_FUEL)
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

void Player::remove()
{


}

void Player::move(Interface::Location loc)
{

}

}
