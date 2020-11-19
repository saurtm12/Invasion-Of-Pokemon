#include "character.hh"

namespace Model {

Character::Character(int x, int y) : x_(x), y_(y)
{

}

void Character::setImage(QString imgPath) {
    const QImage img(imgPath);
    image_.setPixmap(QPixmap::fromImage(img));
}

}
