#include "city.h"

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

void City::readOfflineData(QString busFile, QString stopsFile)
{

}
