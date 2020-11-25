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
    std::shared_ptr<Character> newStop = std::make_shared<Character>(BUS_STOP_ICON);

    newStop->setItem(map_->addPixmap(newStop->pixmap()));
    newStop->setOffset(-8, -24);
    newStop->setCoord(stop->getLocation());
    stopsMap_.insert({ stop, newStop });
}

void City::addActor(std::shared_ptr<IActor> newactor)
{
    QString imgPath = BUS_ICON;
    std::string type = typeid(*newactor).name();
    if (type == "N10CourseSide5NysseE") {
        imgPath = BUS_ICON;
    }

    std::shared_ptr<Character> actorGraphic = std::make_shared<Character>(imgPath);
    actorGraphic->setItem(map_->addPixmap(actorGraphic->pixmap()));
    actorGraphic->setOffset(-10, -10);
    actorGraphic->setCoord(newactor->giveLocation());
    actorsMap_.insert({ newactor, actorGraphic });
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
