#ifndef CHARACTER_HH
#define CHARACTER_HH

#include "../Course/CourseLib/core/location.hh"
#include <QGraphicsItem>
#include <QImage>
#include <QString>

namespace Model {

class Character : public QGraphicsPixmapItem
{
public:
    Character(const QPixmap& pixmap, Interface::Location loc);
    ~Character();

    int getX();
    int getY();
    Interface::Location getLocation() const;
    int getStep() const;

    void setCoord(Interface::Location loc);
    void setCoord(int x, int y);
    void setTrueCoord(Interface::Location trueLoc);
    void giveStep(int step);

    bool move(int horizontalMultiplier, int verticalMultiplier);
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
private:
    const int WIDTH = 1095;
    const int HEIGHT = 592;
    int step_;
    Interface::Location loc_;
};

};

#endif // CHARACTER_HH
