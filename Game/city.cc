#include "city.h"

namespace Model
{

City::City(QWidget *parent):
    map_(new QGraphicsScene(parent)), pause_(false)
{
    pokemons_ = readPokemonData(":/pokemonImg/Pokemon/");
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
    clock_ = clock;
}

void City::startGame()
{
    QImage backgroundImage = QImage(BACKGROUND);
    // Fix this line
    setBackground(backgroundImage,backgroundImage);
    addMainActor();
    generateBalls();
}

QGraphicsScene* City::getMap() {
    return map_;
}

void City::addStop(std::shared_ptr<IStop> stop)
{
    QGraphicsPixmapItem* stopPixmap = map_->addPixmap(QPixmap::fromImage(QImage(BUS_STOP_ICON)));
    std::shared_ptr<Character> newStop = std::make_shared<Character>(stopPixmap, stop->getLocation());
    newStop->setOffset(-8, -24);
    stopsMap_.insert({ stop, newStop });
}

void City::addActor(std::shared_ptr<IActor> newactor)
{
    QString imgPath = BUS_ICON;
    if (typeid(*newactor).name() == Utils::NYSSE_TYPE)
    {
      imgPath = BUS_ICON;
    }
    if (typeid(*newactor).name() == Utils::PASSENGER_TYPE)
    {
      imgPath = PASSENGER_ICON;
    }

    QGraphicsPixmapItem* actorPixmap = map_->addPixmap(QPixmap::fromImage(QImage(imgPath)));
    std::shared_ptr<Character> actorGraphic = std::make_shared<Character>(actorPixmap, newactor->giveLocation());
    actorGraphic->setOffset(-10, -10);
    actorsMap_.insert({ newactor, actorGraphic });
}

void City::addMainActor()
{
    QGraphicsPixmapItem* mainPixmap = map_->addPixmap(QPixmap::fromImage(QImage(STEWIE_ICON)));
    Location mainLoc;
    mainLoc.setXY(200, 200);
    player_ = std::make_shared<Player>(mainPixmap, mainLoc);
}

void City::removeActor(std::shared_ptr<IActor> actor)
{
    actorsMap_.erase(actor);
}

void City::addBall()
{
    // give consistency for the larger map.
    int x = rand() % WITDH - 352;
    int y = 558 - rand() % HEIGHT;
    Location newLoc;
    newLoc.setXY(x,y);

    QGraphicsPixmapItem* ballPixmap = map_->addPixmap(QPixmap::fromImage(QImage(BALL_ICON)));
    std::shared_ptr<Character> newBall = std::make_shared<Character>(ballPixmap,  newLoc );
    newBall->setOffset(-10, -10);
    ballsMap_.push_back(newBall);
}

void City::generateBalls()
{
    ballsMap_.clear();
    for (int i = 0; i < BALLS_PER_TURN; i++){
        addBall();
    }
}

void City::actorRemoved(std::shared_ptr<IActor> actor)
{

}

bool City::findActor(std::shared_ptr<IActor> actor) const
{
    return actorsMap_.find(actor) != actorsMap_.end();
}

void City::actorMoved(std::shared_ptr<IActor> actor)
{
    actorsMap_.at(actor)->setCoord(actor->giveLocation());
}

std::vector<std::shared_ptr<IActor> > City::getNearbyActors(Location loc) const
{
    std::vector< std::shared_ptr<IActor> > result;
    for (auto actor: actorsMap_) {
        if (actor.first->giveLocation().isClose(loc)) {
            result.push_back(actor.first);
        }
    }

    return result;
}

bool City::isGameOver() const
{
    // TODO: implement game over criteria
    return false;
}

void City::keyPress(int command)
{

    switch (command) {
    case Qt::Key_W:
        qDebug()<< "W pressed";
        player_->moveDirection(0, -1);
        break;
    case Qt::Key_S:
        qDebug()<< "S pressed";
        player_->moveDirection(0, 1);
        break;
    case Qt::Key_A:
        qDebug()<< "A pressed";
        player_->moveDirection(-1, 0);
        break;
    case Qt::Key_D:
        qDebug()<< "D pressed";
        player_->moveDirection(1, 0);
        break;
    case Qt::Key_Space:
        ballsMap_.erase(ballsMap_.begin());
        qDebug()<< "Space pressed";
        break;

    }
}

}
