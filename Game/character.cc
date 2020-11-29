#include "character.hh"
#include "Utils/helpers.hh"

#include <QDebug>

namespace Model {

Character::Character(const QPixmap& pixmap, Interface::Location loc) :
    QGraphicsPixmapItem(pixmap), step_(4)
{
    setCoord(loc);
    setAcceptHoverEvents(true);
}

Character::~Character()
{

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

int Character::getStep() const
{
    return step_;
}

void Character::setCoord(Interface::Location loc)
{
    loc_ = Utils::convertLocation(loc);
    setPos(loc_.giveX(), loc_.giveY());
}

void Character::setCoord(int x, int y)
{
    loc_.setXY(x, y);
    setPos(x, y);
}

void Character::setTrueCoord(Interface::Location trueLoc)
{
    loc_ = trueLoc;
    setPos(loc_.giveX(), loc_.giveY());
}

void Character::giveStep(int step)
{
    step_ = step;
}

bool Character::move(int horizontalMultiplier, int verticalMultiplier)
{
    int x = getX() + horizontalMultiplier * step_;
    int y = getY() + verticalMultiplier * step_;
    int offX = -offset().x();
    int offY = -offset().y();
    if (x < offX || x >= WIDTH - offX || y < offY || y >= HEIGHT - offY)
    {
        return false;
    }
    loc_.setXY(x, y);
    setPos(x, y);
    return true;
}

void Character::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    qDebug() << "meow";
    QGraphicsPixmapItem::hoverEnterEvent(event);
}

void Character::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    qDebug() << "meow leave";
    QGraphicsPixmapItem::hoverLeaveEvent(event);
}

}
