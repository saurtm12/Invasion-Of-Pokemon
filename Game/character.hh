#ifndef CHARACTER_HH
#define CHARACTER_HH

#include "../Course/CourseLib/graphics/simpleactoritem.hh"
#include "../Course/CourseLib/core/location.hh"
#include <QGraphicsItem>
#include <QImage>
#include <QString>

namespace Model {

const int WIDTH = 15;
const int HEIGHT = 15;

class Character : public QGraphicsPixmapItem
{
public:
    Character(Interface::Location loc, QString imgPath, QGraphicsItem* parent);

    int getX();
    int getY();

    void setCoord(Interface::Location loc);

signals:

private:
    Interface::Location loc_;
};

};

#endif // CHARACTER_HH
