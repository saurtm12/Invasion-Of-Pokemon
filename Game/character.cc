#include "character.hh"

namespace Model {

Character::Character(int x, int y, QString imgPath) :
    CourseSide::SimpleActorItem(x, y, 0), x_(x), y_(y)
{
    setImage(imgPath);
}

Character::~Character() {

}

void Character::setImage(QString imgPath) {
    const QImage img(imgPath);
    image_ = QPixmap::fromImage(img);
}

QPixmap Character::getPixmapItem() {
    return image_;
}

}
