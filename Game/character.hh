#ifndef CHARACTER_HH
#define CHARACTER_HH

#include "../Course/CourseLib/core/location.hh"
#include <QGraphicsItem>
#include <QImage>
#include <QString>

namespace Model {

// ?????????????????
//const int WIDTH = 15;
//const int HEIGHT = 15;

class Character
{
public:
    Character(QGraphicsPixmapItem* item, Interface::Location loc);
    ~Character();

    int getX();
    int getY();
    Interface::Location getLocation() const;
    QGraphicsPixmapItem* getItem() const;

    void setCoord(Interface::Location loc);
    void setCoord(int x, int y);
    void setTrueCoord(Interface::Location trueLoc);
    void setOffset(int offX, int offY);
    void setItem(QGraphicsPixmapItem* item);
    void move(int horizontalMultiplier, int verticalMultiplier);
    void giveStep(int step);
    int getStep() const;
protected:
    const int WITDH = 1095;
    const int HEIGHT = 592;
private:
    int step_;
    Interface::Location loc_;
    QGraphicsPixmapItem* item_;
};

};

#endif // CHARACTER_HH
