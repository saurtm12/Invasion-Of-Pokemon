#include "character.hh"
#include "Utils/helpers.hh"

#include <QDebug>

namespace Model {

Character::Character(Interface::Location loc, QString imgPath) :
    QGraphicsPixmapItem(), loc_(Utils::convertLocation(loc))
{
    setPixmap(QPixmap::fromImage(QImage(imgPath)));
}

int Character::getX()
{
    return loc_.giveX();
}

int Character::getY()
{
    return loc_.giveY();
}

void Character::setCoord(Interface::Location loc)
{
    loc_ = Utils::convertLocation(loc);
    this->setPos(loc_.giveX(), loc_.giveY());
}

}
