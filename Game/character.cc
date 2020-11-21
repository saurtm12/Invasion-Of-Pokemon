#include "character.hh"
#include "Utils/helpers.hh"

#include <QDebug>

namespace Model {

Character::Character() : loc_(Interface::Location())
{

}

Character::Character(Interface::Location loc, QString imgPath) :
    loc_(loc), imgPath_(imgPath)
{

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
    pm->setPos(loc_.giveX(), loc_.giveY());
    return pm;
}

QGraphicsPixmapItem* Character::setImage(QGraphicsScene* map, QString imgPath, int offX, int offY)
{
    const QImage img(imgPath);
    image_ = QPixmap::fromImage(img);
    QGraphicsPixmapItem* pm = map->addPixmap(image_);
    pm->setOffset(offX, offY);
    pm->setPos(loc_.giveX(), loc_.giveY());
    return pm;
}

QPixmap Character::getPixmapItem()
{
    return image_;
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
    loc_ = loc;
}

QRectF Character::boundingRect() const
{
    return QRectF(0, 0, 15, 15);
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

}
