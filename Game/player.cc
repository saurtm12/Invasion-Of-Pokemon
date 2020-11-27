#include "player.h"

namespace Model
{

Player::Player(QGraphicsPixmapItem* item, Interface::Location loc):
    Character(item, loc)
{

}

Player::~Player()
{

}

Interface::Location Player::giveLocation() const
{
    return getLocation();
}

void Player::move(Interface::Location loc)
{

}

bool Player::isRemoved() const
{

}

void Player::remove()
{

}

}
