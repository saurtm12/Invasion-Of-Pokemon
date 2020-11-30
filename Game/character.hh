#ifndef CHARACTER_HH
#define CHARACTER_HH

#include "../Course/CourseLib/core/location.hh"
#include <QGraphicsItem>
#include <QImage>
#include <QString>
#include <QToolTip>

/**
 * @file character.hh
 * @brief Define Character class which is a graphics of a moving actor on city map.
 */
namespace Model {
// Mainwindow constants
const int WIDTH = 1095;
const int HEIGHT = 592;

/**
 * @brief The Character class - defines items on the map
 * @inherits GraphicsPixmapItem
 */
class Character : public QGraphicsPixmapItem
{
public:
    /**
     * @brief Character constructor
     * @param pixmap pixmap to a image for the graphic item
     * @param loc initial location to be moved to
     * @post exception guarantee: no throw.
     */
    Character(const QPixmap& pixmap, Interface::Location loc);

    /**
     * @brief Character destructor.
     */
    ~Character();

    /**
     * @brief getX
     * @return X location in city map.
     * @pre -
     * @post Exception guarantee: No throw
     */
    int getX();

    /**
     * @brief getY
     * @return Y location in city map
     * @pre -
     * @post Exception guarantee: No throw
     */
    int getY();

    /**
     * @brief get current Location
     * @return location in city map
     * @pre -
     * @post Exception guarantee: No throw
     */
    Interface::Location getLocation() const;

    /**
     * @brief get step (or speed of the item)
     * @return speed of the item
     * @pre Setting is set before the game start
     * @post Exception guarantee: No throw
     */
    int getStep() const;

    /**
     * @brief set location for item
     * @param loc location to be set
     * @pre provided location must be location for small map (500x500). This method would convert to big map
     * @post Exception guarantee: No throw
     */
    void setCoord(Interface::Location loc);

    /**
     * @brief set location for item (this is overload method)
     * @param x horizontal coord
     * @param y vertical coord
     * @pre x and y are coord in small map
     * @post Exception guarantee: No throw
     */
    void setCoord(int x, int y);

    /**
     * @brief set true(in big map) location for item
     * @param trueLoc location to be set
     * @pre provided location must be location for big map (1095x592)
     * @post Exception guarantee: No throw
     */
    void setTrueCoord(Interface::Location trueLoc);

    /**
     * @brief set tooltip text for use when hovering over the item
     * @param text the text will be shown, can be in form of rich text. Empty text will not show tooltip
     * @pre -
     * @post Exception guarantee: No throw
     */
    void setTooltipText(QString text);

    /**
     * @brief set step/speed for the item when moving on map
     * @param step step to be set
     * @pre game setting should be set before init the class
     * @post Exception guarantee: No throw
     */
    void giveStep(int step);

    /**
     * @brief move the item on the map with axis multipliers
     * @param horizontalMultiplier multiplier for item's step on horizontal direction
     * @param verticalMultiplier multiplier for item's step on vertical direction
     * @pre item's step should be set in advanced
     * @post Exception guarantee: No throw
     */
    bool move(int horizontalMultiplier, int verticalMultiplier);
protected:
    // override hover events to show and hide tooltip
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
private:
    const int WIDTH = 1095;
    const int HEIGHT = 592;
    int step_;
    Interface::Location loc_;
    QString tooltipText_;
};

};

#endif // CHARACTER_HH
