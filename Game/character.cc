#include "character.hh"

namespace Model {

Character::Character(int x, int y, QString imgPath) :
    CourseSide::SimpleActorItem(x, y, 0), x_(x), y_(y), imgPath_(imgPath)
{

}

Character::~Character() {

}

QGraphicsPixmapItem* Character::setImage(QGraphicsScene* map) {
    const QImage img(imgPath_);
    image_ = QPixmap::fromImage(img);
    QGraphicsPixmapItem* pm = map->addPixmap(image_);
    pm->setPos(x_, y_);
    return pm;
}

QPixmap Character::getPixmapItem() {
    return image_;
}

int Character::getX() {
    return x_;
}

int Character::getY() {
    return y_;
}

}
