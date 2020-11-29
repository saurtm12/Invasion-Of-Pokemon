#ifndef CHARACTER_HH
#define CHARACTER_HH

#include "../Course/CourseLib/core/location.hh"
#include <QGraphicsItem>
#include <QImage>
#include <QString>

/**
 * @file character.hh
 * @brief Define Character class which is a moving actor on city map.
 */
namespace Model {
// Mainwindow constants
const int WITDH = 1095;
const int HEIGHT = 592;

class Character : public QGraphicsPixmapItem
{
public:
    Character(const QPixmap& pixmap, Interface::Location loc);

    /**
     * @brief Character destructor.
     */
    ~Character();

    /**
     * @brief getX
     * @return X location in city map.
     * @pre -
     * @post -
     * @exception No throw
     */
    int getX();

    /**
     * @brief getY
     * @return Y location in city map
     * @pre -
     * @post -
     * @exception No throw
     */
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
