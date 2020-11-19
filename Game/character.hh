#ifndef CHARACTER_HH
#define CHARACTER_HH

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QString>

namespace Model {

const int WIDTH = 15;
const int HEIGHT = 15;

class Character : public QGraphicsItem
{
public:
    explicit Character(int x, int y);
    virtual ~Character();

    void setImage(QString imgPath);

signals:

private:
    int x_;
    int y_;
    QGraphicsPixmapItem image_;
};

};

#endif // CHARACTER_HH
