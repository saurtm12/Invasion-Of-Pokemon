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
    setTrueCoord(loc);
}

void Player::move(int horizontalMultiplier, int verticalMultipler)
{
    Interface::Location loc = getLocation();
    loc.setXY(loc.giveX() + horizontalMultiplier * STEP, loc.giveY() + verticalMultipler * STEP);
    setTrueCoord(loc);
}

bool Player::isRemoved() const
{

}

void Player::remove()
{

}

}
