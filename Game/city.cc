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

    for (auto& element : busItems_)
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

void City::startGame()
{
    QImage backgroundImage = QImage(BACKGROUND);
    // Fix this line
    setBackground(backgroundImage,backgroundImage);
    readOfflineData(BUS_FILE, STOP_FILE);
    initBusStops();
    initBuses();
}

QGraphicsScene* City::getMap() {
    return map_;
}

void City::addStop(std::shared_ptr<IStop> stop)
{

}

void City::addBus(std::shared_ptr<BusData> busData)
{
    // transform bus' location to fit large map
    for (auto iter = busData->timeRoute2.begin(); iter != busData->timeRoute2.end(); ++iter) {
        iter->second = std::make_pair(Utils::convertLocation(iter->second.first), iter->second.second);
    }
    std::shared_ptr<Bus> bus = std::make_shared<Bus>(busData);
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
    stops_ = data->stops;
    buses_.reserve(data->buses.size());
    for (auto iter = data->buses.begin(); iter != data->buses.end(); iter++)
    {
        addBus(*iter);
    }

    // Let's transform all the locations for the large map
    for (auto& stop: stops_) {
        stop->setLocation(Utils::convertLocation(stop->getLocation()));
    }
}

void City::initBusStops()
{
    stopItems_.reserve(stops_.size());
    for (auto& stop : stops_)
    {
        Character newStop(stop->getLocation(), BUS_STOP_ICON);
        // (-8, -24) is the offset for bus stop icon
        QGraphicsPixmapItem* newItem = newStop.setImage(map_, -8, -24);
        stopItems_.push_back(newItem);
    }
}

void City::initBuses()
{
    for (auto& bus : buses_)
    {
        // bus icon size is 15 x 15, so offset is (-7, -7)
        QGraphicsPixmapItem* busImg = bus->setImage(map_, BUS_ICON, -7, -7);
        busItems_.push_back(busImg);
        bus->moveToNextPosition(bus->advanceTime());
        bus->moveToNextPosition(bus->advanceTime());
        bus->moveToNextPosition(bus->advanceTime());
        Location newLoc = bus->moveToNextPosition(bus->advanceTime());
        qDebug() << newLoc.giveX();
        bus->move(newLoc);
    }
}

}
