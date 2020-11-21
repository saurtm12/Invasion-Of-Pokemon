#include "city.h"
namespace Model {

City::City(QWidget *parent):
    QGraphicsScene(parent), map_(new QGraphicsScene(parent))
{

}

City::~City()
{
    for (auto& element : stopItems_)
    {
        delete element;
    }

    delete map_;
}

void City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    //TODO: need to implement this
    map_->setBackgroundBrush(basicbackground);
}

void City::setClock(QTime clock)
{

}

void City::addStop(std::shared_ptr<IStop> stop)
{

}

void City::startGame()
{
    QImage backgroundImage = QImage(BACKGROUND);
    // Fix this line
    setBackground(backgroundImage,backgroundImage);
    readOfflineData(BUSFILE, STOPFILE);
    addBusStops();
}

QGraphicsScene* City::getMap() {
    return map_;
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

void City::readOfflineData(const QString &busFile, const QString &stopFile)
{
    auto offlineReader = CourseSide::OfflineReader();
    auto data = offlineReader.readFiles(busFile, stopFile);
    stops_ = data->stops;
    buses_.reserve(data->buses.size());
    for (auto iter = data->buses.begin(); iter != data->buses.end(); iter++)
    {
        buses_.push_back(*iter);
    }
}

void City::addBusStops()
{
    stopItems_.reserve(stops_.size());
    for (auto& stop : stops_)
    {
        Character newStop(stop->getLocation(), BUSICON);
        // (-8, -24) is the offset for bus stop icon
        QGraphicsPixmapItem* newItem = newStop.setImage(map_, -6, -24);
        stopItems_.push_back(newItem);
    }
}

}
