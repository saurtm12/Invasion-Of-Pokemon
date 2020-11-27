#include "character.hh"
#include "Utils/helpers.hh"

#include <QDebug>

namespace Model {

Character::Character(QGraphicsPixmapItem* item, Interface::Location loc) :
    item_(item)
{
    setCoord(loc);
}

Character::~Character()
{
    delete item_;
}

int Character::getX()
{
    return loc_.giveX();
}

int Character::getY()
{
    return loc_.giveY();
}

Interface::Location Character::getLocation() const
{
    return loc_;
}

void Character::setCoord(Interface::Location loc)
{
    loc_ = Utils::convertLocation(loc);
    item_->setPos(loc_.giveX(), loc_.giveY());
}

void Character::setTrueCoord(Interface::Location trueLoc)
{
    loc_ = trueLoc;
    item_->setPos(loc_.giveX(), loc_.giveY());
}

void Character::setOffset(int offX, int offY)
{
    item_->setOffset(offX, offY);
}

void Character::setItem(QGraphicsPixmapItem *item)
{
    item_ = item;
}

}
