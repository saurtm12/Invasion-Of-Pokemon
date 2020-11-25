#include "city.h"
namespace Model {

City::City(QWidget *parent):
    map_(new QGraphicsScene(parent)), pause_(false)
{

}

City::~City()
{

}

void City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    //TODO: need to implement this
    map_->setBackgroundBrush(basicbackground);
}

void City::setClock(QTime clock)
{

}

void City::startGame()
{
    QImage backgroundImage = QImage(BACKGROUND);
    // Fix this line
    setBackground(backgroundImage,backgroundImage);
}

QGraphicsScene* City::getMap() {
    return map_;
}

void City::addStop(std::shared_ptr<IStop> stop)
{

}

void City::addStop(std::shared_ptr<Stop> stop)
{
    std::shared_ptr<Character> newStop = std::make_shared<Character>(stop->getLocation(), BUS_STOP_ICON);
    // (-8, -24) is the offset for bus stop icon
    newStop->setImage(map_, -8, -24);
    stopImgs_.push_back(newStop);
}

void City::addBus(std::shared_ptr<Bus> bus)
{
    // bus icon size is 20 x 20, so offset is (-10, -10)
    bus->setImage(map_, BUS_ICON, -10, -10);
    bus->setCoord(bus->giveLocation());
}

void City::addActor(std::shared_ptr<IActor> newactor)
{

}

void City::removeActor(std::shared_ptr<IActor> actor)
{

}

void City::actorRemoved(std::shared_ptr<IActor> actor)
{

}

bool City::findActor(std::shared_ptr<IActor> actor) const
{

}

void City::actorMoved(std::shared_ptr<IActor> actor)
{

}

std::vector<std::shared_ptr<IActor> > City::getNearbyActors(Location loc) const
{

}

bool City::isGameOver() const
{
    // TODO: implement game over criteria
    return false;
}

void City::keyPress(int command)
{
  if (command == Qt::Key_W)
  {
    qDebug()<< "W pressed";
    return;
  }
  if (command == Qt::Key_S)
  {
    qDebug()<< "S pressed";
    return;
  }
  if (command == Qt::Key_A)
  {
    qDebug()<< "A pressed";
    return;
  }
  if (command == Qt::Key_D)
  {
    qDebug()<< "D pressed";
    return;
  }
  if (command == Qt::Key_Space)
  {
    qDebug()<< "Space pressed";
    return;
  }
}

}
