#include "character.hh"
#include "Utils/helpers.hh"

#include <QDebug>

namespace Model {

Character::Character(int x, int y, QString imgPath) :
    x_(x), y_(y), imgPath_(imgPath)
{

}

Character::Character(Interface::Location loc, QString imgPath) :
    imgPath_(imgPath)
{
    Interface::Location newLoc = Utils::convertLocation(loc);
    setCoord(newLoc);
}

Character::~Character()
{

}

QGraphicsPixmapItem* Character::setImage(QGraphicsScene* map, int offX, int offY)
{
    const QImage img(imgPath_);
    image_ = QPixmap::fromImage(img);
    QGraphicsPixmapItem* pm = map->addPixmap(image_);
    pm->setOffset(offX, offY);
    pm->setPos(x_, y_);
    return pm;
}

QPixmap Character::getPixmapItem()
{
    return image_;
}

int Character::getX()
{
    return x_;
}

int Character::getY()
{
    return y_;
}

void Character::setCoord(int x, int y)
{
    x_ = x;
    y_ = y;
}

void Character::setCoord(Interface::Location loc)
{
    x_ = loc.giveX();
    y_ = loc.giveY();
}

QRectF Character::boundingRect() const
{
    return QRectF(0, 0, 15, 15);
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

}
