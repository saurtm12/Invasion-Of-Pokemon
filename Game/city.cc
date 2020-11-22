#include "city.h"
namespace Model {

City::City(QWidget *parent):
    QGraphicsScene(parent), map_(new QGraphicsScene(parent))
{

}

City::~City()
{
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

void City::startGame()
{
    QImage backgroundImage = QImage(BACKGROUND);
    // Fix this line
    setBackground(backgroundImage,backgroundImage);
    readOfflineData(BUS_FILE, STOP_FILE);
}

QGraphicsScene* City::getMap() {
    return map_;
}

void City::addStop(std::shared_ptr<IStop> stop)
{
    // Bus stops do not move, so we don't need to deal with their graphics much
    Character newStop(stop->getLocation(), BUS_STOP_ICON);
    // (-8, -24) is the offset for bus stop icon
    newStop.setImage(map_, -8, -24);
    stops_.push_back(stop);
}

void City::addBus(std::shared_ptr<BusData> busData)
{
    // transform bus' location to fit large map
    for (auto iter = busData->timeRoute2.begin(); iter != busData->timeRoute2.end(); ++iter) {
        iter->second = std::make_pair(Utils::convertLocation(iter->second.first), iter->second.second);
    }
    std::shared_ptr<Bus> bus = std::make_shared<Bus>(busData);
    // bus icon size is 20 x 20, so offset is (-10, -10)
    bus->setImage(map_, BUS_ICON, -10, -10);
    bus->setCoord(bus->giveLocation());
    buses_.push_back(bus);
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

    stops_.reserve(data->stops.size());
    // Let's transform all the locations for the large map
    for (auto& stop: data->stops) {
        stop->setLocation(Utils::convertLocation(stop->getLocation()));
        addStop(stop);
    }

    buses_.reserve(data->buses.size());
    for (auto iter = data->buses.begin(); iter != data->buses.end(); iter++)
    {
        addBus(*iter);
    }


}

}
