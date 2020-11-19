#include "city.h"
namespace Model {

City::City(QWidget *parent):
    QGraphicsScene(parent)
{

}

void City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    //TODO: need to implement this
    this->setBackgroundBrush(basicbackground);
}

void City::setClock(QTime clock)
{

}

void City::addStop(std::shared_ptr<IStop> stop)
{

}

void City::startGame()
{
    readOfflineData(BUSFILE, STOPFILE);
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

void City::readOfflineData(const QString &busFile, const QString &stopFile)
{
    auto offlineReader = CourseSide::OfflineReader();
    auto data = offlineReader.readFiles(busFile, stopFile);
    stops_ = data->stops;
    buses_.reserve( data->buses.size() );
    for (auto iter = data->buses.begin(); iter != data->buses.end(); iter++)
    {
        buses_.push_back(*iter);
    }
}

}
