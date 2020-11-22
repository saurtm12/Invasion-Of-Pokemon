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

class Character : public QGraphicsItem
{
public:
    Character();
    explicit Character(Interface::Location loc, QString imgPath);
    virtual ~Character();

    void setImage(QGraphicsScene* map, int offX = 0, int offY = 0);
    void setImage(QGraphicsScene* map, QString imgPath, int offX = 0, int offY = 0);

    int getX();
    int getY();

    void move(Interface::Location loc);
    virtual void setCoord(Interface::Location loc) = 0;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


signals:

private:
    Interface::Location loc_;
    QString imgPath_;
    QGraphicsPixmapItem* image_;
};

};

#endif // CHARACTER_HH
