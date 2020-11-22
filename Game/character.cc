#include "character.hh"
#include "Utils/helpers.hh"

#include <QDebug>

namespace Model {

Character::Character() : loc_(Interface::Location()), image_(nullptr)
{

}

Character::Character(Interface::Location loc, QString imgPath) :
    loc_(loc), imgPath_(imgPath), image_(nullptr)
{

}

Character::~Character()
{
    delete image_;
}

void Character::setImage(QGraphicsScene* map, int offX, int offY)
{
    const QImage img(imgPath_);
    auto image = QPixmap::fromImage(img);
    image_ = map->addPixmap(image);
    image_->setOffset(offX, offY);
    image_->setPos(loc_.giveX(), loc_.giveY());
}

void Character::setImage(QGraphicsScene* map, QString imgPath, int offX, int offY)
{
    const QImage img(imgPath);
    auto image = QPixmap::fromImage(img);
    image_ = map->addPixmap(image);
    image_->setOffset(offX, offY);
    image_->setPos(loc_.giveX(), loc_.giveY());
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
    image_->setPos(loc.giveX(), loc.giveY());
}

QRectF Character::boundingRect() const
{
    return QRectF(0, 0, 15, 15);
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

}
