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
    explicit Character(int x, int y, QString imgPath);
    explicit Character(Interface::Location loc, QString imgPath);
    virtual ~Character();

    QGraphicsPixmapItem* setImage(QGraphicsScene* map, int offX = 0, int offY = 0);
    QPixmap getPixmapItem();

    int getX();
    int getY();

    void setCoord(int x, int y);
    void setCoord(Interface::Location loc);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


signals:

private:
    int x_;
    int y_;
    QString imgPath_;
    QPixmap image_;
};

};

#endif // CHARACTER_HH
