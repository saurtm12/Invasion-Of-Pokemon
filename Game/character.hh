#ifndef CHARACTER_HH
#define CHARACTER_HH

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QImage>
#include <QPainter>

namespace Model {

const int WIDTH = 15;
const int HEIGHT = 15;

class Character : public QGraphicsItem
{
public:
    explicit Character(int x, int y);
    virtual ~Character();

    void setImage(QImage& img) const;

signals:

private:
    int x_;
    int y_;
    QImage image_;
};

};

#endif // CHARACTER_HH
