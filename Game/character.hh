#ifndef CHARACTER_HH
#define CHARACTER_HH

#include "../Course/CourseLib/graphics/simpleactoritem.hh"
#include <QGraphicsItem>
#include <QImage>
#include <QString>

namespace Model {

const int WIDTH = 15;
const int HEIGHT = 15;

class Character : public CourseSide::SimpleActorItem
{
public:
    explicit Character(int x, int y, QString imgPath);
    virtual ~Character();

    void setImage(QString imgPath);
    QPixmap getPixmapItem();

    int getX();
    int getY();

signals:

private:
    int x_;
    int y_;
    QPixmap image_;
};

};

#endif // CHARACTER_HH
