#include "character.hh"

namespace Model {

Character::Character(int x, int y, QString imgPath) :
    CourseSide::SimpleActorItem(x, y, 0), x_(x), y_(y)
{
    image_ = new QGraphicsPixmapItem();
    setImage(imgPath);
}

Character::~Character() {
    delete image_;
}

void Character::setImage(QString imgPath) {
    const QImage img(imgPath);
    image_->setPixmap(QPixmap::fromImage(img));
}

QGraphicsPixmapItem* Character::getPixmapItem() {
    return image_;
}

}
