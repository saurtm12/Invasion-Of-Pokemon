#ifndef CHARACTER_HH
#define CHARACTER_HH

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
    Character(QString imgPath);
    ~Character();

    int getX();
    int getY();

    void setCoord(Interface::Location loc);
    void setOffset(int offX, int offY);
    void setItem(QGraphicsPixmapItem* item);

signals:

private:
    Interface::Location loc_;
    QGraphicsPixmapItem* item_;
};

};

#endif // CHARACTER_HH
