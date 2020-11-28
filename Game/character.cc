#include "character.hh"
#include "Utils/helpers.hh"

#include <QDebug>

namespace Model {

Character::Character(QGraphicsPixmapItem* item, Interface::Location loc) :
    item_(item), step_(4)
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

QGraphicsPixmapItem* Character::getItem() const
{
    return item_;
}

void Character::setCoord(Interface::Location loc)
{
    loc_ = Utils::convertLocation(loc);
    item_->setPos(loc_.giveX(), loc_.giveY());
}

void Character::setCoord(int x, int y)
{
    loc_.setXY(x, y);
    item_->setPos(x, y);
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


void Character::move(int horizontalMultiplier, int verticalMultiplier)
{
    int x = getX() + horizontalMultiplier * step_;
    int y = getY() + verticalMultiplier * step_;
    int offX = -item_->offset().x();
    int offY = -item_->offset().y();
    if (x < offX || x >= WITDH - offX || y < offY || y >= HEIGHT - offY)
    {
        return;
    }
    loc_.setXY(x, y);
    item_->setPos(x, y);
}

void Character::giveStep(int step)
{
    step_ = step;
}

int Character::getStep() const
{
    return step_;
}

}
