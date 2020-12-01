#include "city.h"

namespace Model
{

City::City(Utils::GameSetting gameSetting, QWidget *parent):
    map_(new QGraphicsScene(parent)),
    player_(nullptr),
    isInStop(false),
    isInBus(false),
    isLocked(false),
    player2_(nullptr),
    pause_(false),
    gameSetting_(gameSetting),
    multiplayer_(gameSetting.multiplayer_ == "Yes")
{
    pokemons_ = readPokemonData(":/pokemonImg/Pokemon/");
}

City::~City()
{

}

void City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    map_->setBackgroundBrush(basicbackground);
}

void City::setClock(QTime clock)
{
    clock_ = clock;
}

void City::startGame()
{
    QImage backgroundImage = QImage(BACKGROUND);
    setBackground(backgroundImage,backgroundImage);
    addMainActor();
    generateBalls();
    timer_.start(UPDATE_INTERVAL_MS);
    connect(&timer_, &QTimer::timeout, this, &City::onTimeIncreased);
}

QGraphicsScene* City::getMap() {
    return map_;
}

QDialog* City::getPlayerBag(QWidget* parent) const
{
    return player_->getBag(parent);
}

void City::addStop(std::shared_ptr<IStop> stop)
{
    Character* newStop = new Character(QPixmap::fromImage(QImage(BUS_STOP_ICON)), stop->getLocation());
    map_->addItem(newStop);
    newStop->setOffset(-8, -24);
    stopsMap_.insert({ stop, newStop });
}

void City::addActor(std::shared_ptr<IActor> newactor)
{
    try {
        if (actorsMap_.find(newactor) != actorsMap_.end()) {
            throw GameError("Actor is already in the city");
        }
        QString imgPath = BUS_ICON;
        auto bus = std::dynamic_pointer_cast<Nysse>(newactor);
        auto passenger = std::dynamic_pointer_cast<Passenger>(newactor);
        if (bus)
        {
            imgPath = BUS_ICON;
        }
        if (passenger)
        {
            imgPath = PASSENGER_ICON;
            std::shared_ptr<IStop> stop = passenger->getStop();
            stopsMap_.at(stop)->setTooltipText(Utils::generateTooltipTextFromPassenger(stop->getPassengers().size(), "stop"));
        }

        Character* actorGraphic = new Character(QPixmap::fromImage(QImage(imgPath)), newactor->giveLocation());
        map_->addItem(actorGraphic);
        actorGraphic->setOffset(-10, -10);
        actorsMap_.insert({ newactor, actorGraphic });
        emit actorChanged(newactor, 1);
    } catch (const GameError& e) {
        qDebug() << e.giveMessage();
    }
}

void City::addMainActor()
{
    Location mainLoc;
    mainLoc.setXY(200, 200);
    player_ = new Player(QPixmap::fromImage(QImage(STEWIE_ICON)), mainLoc, gameSetting_.fuel_, gameSetting_.speed_);
    player_->setTooltipText("Your beautiful main character :)");
    player_->setOffset(-12, -8);
    map_->addItem(player_);

    if (multiplayer_) {
        Location mainLoc2;
        mainLoc2.setXY(500, 200);
        player2_ = new Player(QPixmap::fromImage(QImage(BRIAN_ICON)), mainLoc2, gameSetting_.fuel_, gameSetting_.speed_);
        player2_->setTooltipText("Your second beautiful main character :)");
        player2_->setOffset(-12, -8);
        map_->addItem(player2_);
    }
}

void City::removeActor(std::shared_ptr<IActor> actor)
{
    try {
        map_->removeItem(actorsMap_.at(actor));
        actorsMap_.erase(actor);
        emit actorChanged(actor, -1);
    } catch (const std::out_of_range& e) {
        qDebug() << "Delete non exist actor";
    }
}

void City::addBall()
{
    // give consistency for the larger map.
    int x = Utils::generateRandom(10, WIDTH - 10) - Utils::X_OFFSET_MAP;
    int y = Utils::Y_OFFSET_MAP - Utils::generateRandom(10, HEIGHT - 10);
    Location newLoc;
    newLoc.setXY(x,y);

    Character* newBall = new Character(QPixmap::fromImage(QImage(BALL_ICON)), newLoc);
    newBall->setTooltipText("Collect this ball for pokemon and scores");
    map_->addItem(newBall);
    newBall->setOffset(-10, -10);

    ballsMap_.push_back(newBall);
}

void City::generateBalls()
{
    ballsMap_.clear();
    for (int i = 0; i < gameSetting_.numberOfBall_; i++){
        addBall();
    }
}

Pokemon City::generatePokemon()
{
    return pokemons_.at(Utils::generateRandom(0, pokemons_.size()));
}

void City::actorRemoved(std::shared_ptr<IActor> actor)
{
    actor->remove();
}

bool City::findActor(std::shared_ptr<IActor> actor) const
{
    return actorsMap_.find(actor) != actorsMap_.end();
}

void City::actorMoved(std::shared_ptr<IActor> actor)
{
    auto passenger = std::dynamic_pointer_cast<Passenger>(actor);
    if (Utils::needUpdate(actorsMap_.at(actor)->getLocation(), Utils::convertLocation(actor->giveLocation()))) {
        actorsMap_.at(actor)->setCoord(actor->giveLocation());

        // set tooltip text
        if (passenger) {
            if (passenger->isInVehicle()) {
                std::shared_ptr<IVehicle> bus = passenger->getVehicle();
                actorsMap_.at(bus)->setTooltipText(Utils::generateTooltipTextFromPassenger(bus->getPassengers().size(), "bus"));
            } else if (passenger->getStop()) {
                std::shared_ptr<IStop> stop = passenger->getStop();
                stopsMap_.at(stop)->setTooltipText(Utils::generateTooltipTextFromPassenger(stop->getPassengers().size(), "stop"));
            }
        }
    }
}

std::vector<std::shared_ptr<IActor> > City::getNearbyActors(Location loc) const
{
    std::vector< std::shared_ptr<IActor> > result;
    for (auto actor: actorsMap_) {
        if (actor.first->giveLocation().isClose(loc, 5)) {
            result.push_back(actor.first);
        }
    }

    return result;
}

void City::handleCollision()
{
    for (auto it = ballsMap_.begin(); it != ballsMap_.end(); ++it) {
        if (player_->collidesWithItem(*it)) {
            Pokemon pokemon = generatePokemon();
            player_->addPokemon(pokemon);
            map_->removeItem(*it);
            delete *it;
            ballsMap_.erase(it);
            addBall();
            emit collideBall(pokemon);
            return;
        } else if (multiplayer_ && player2_->collidesWithItem(*it)) {
            Pokemon pokemon = generatePokemon();
            player2_->addPokemon(pokemon);
            map_->removeItem(*it);
            delete *it;
            ballsMap_.erase(it);
            addBall();
            emit collideBall(pokemon);
            return;
        }
    }
}

bool City::isGameOver() const
{
    return getCurrentFuel() <= 0;
}

void City::keyPress(int command)
{
    switch (command) {
    case Qt::Key_W:
        if (isLocked)
        {
            break;
        }
        player_->moveDirection(0, -1);
        emit updateFuel(getCurrentFuel());
        handleCollision();
        break;
    case Qt::Key_S:
        if (isLocked)
        {
            break;
        }
        player_->moveDirection(0, 1);
        emit updateFuel(getCurrentFuel());
        handleCollision();
        break;
    case Qt::Key_A:
        if (isLocked)
        {
            break;
        }
        player_->moveDirection(-1, 0);
        emit updateFuel(getCurrentFuel());
        handleCollision();
        break;
    case Qt::Key_D:
        if (isLocked)
        {
            break;
        }
        player_->moveDirection(1, 0);
        emit updateFuel(getCurrentFuel());
        handleCollision();
        break;
    case Qt::Key_I:
        if (!multiplayer_) {
            break;
        }
        player2_->moveDirection(0, -1);
        emit updateFuel(getCurrentFuel());
        handleCollision();
        break;
    case Qt::Key_K:
        if (!multiplayer_) {
            break;
        }
        player2_->moveDirection(0, 1);
        emit updateFuel(getCurrentFuel());
        handleCollision();
        break;
    case Qt::Key_J:
        if (!multiplayer_) {
            break;
        }
        player2_->moveDirection(-1, 0);
        emit updateFuel(getCurrentFuel());
        handleCollision();
        break;
    case Qt::Key_L:
        if (!multiplayer_) {
            break;
        }
        player2_->moveDirection(1, 0);
        emit updateFuel(getCurrentFuel());
        handleCollision();
        break;
    case Qt::Key_Space:
        if (!isLocked)
        {
            isLocked = joinStop();
            return;
        }
        if (!isInBus){
            isLocked = false;
            isInStop = false;
            qDebug() << "player leaves bus stop";
            return;
        }
        else {
            isInBus = false;
            isLocked = false;
            qDebug() << "player leaves the bus";
        }
        break;
    }
    if (isGameOver())
    {
        emit gameOver();
    }
}

void City::onTimeIncreased()
{
    for (auto iter = ballsMap_.begin(); iter < ballsMap_.end(); iter +=2)
    {
        if (Utils::generateRandom(0,2) == 0)
        {
            (*iter)->move(Utils::generateRandom(0,3)-1, Utils::generateRandom(0,3)-1);
        }
    }
    if (isInStop)
    {
        for (auto& bus : actorsMap_)
        {
            if (typeid(*(bus.first)).name() == Utils::NYSSE_TYPE)
            {
                if (bus.second->getLocation().isClose(player_->getLocation()))
                {
                    isInStop = false;
                    isInBus = true;
                    onBus_ = bus.second;
                    return;
                }
            }
        }
    }
    if (isInBus)
    {
        auto busLocation = onBus_->getLocation();
        auto x = busLocation.giveX();
        auto y = busLocation.giveY();
        if (x >= 0 && y >= 0 && x <= WIDTH && y <= HEIGHT)
        {
            player_->setTrueCoord(busLocation);
        }
        else {
            onBus_ = nullptr;
            isInBus = false;
            isLocked = false;
        }
    }
}


bool City::joinStop()
{
    auto playerLoc = player_->getLocation();
    for (auto& stop: stopsMap_){
        if (playerLoc.isClose(stop.second->getLocation(),25))
        {
            isInStop = true;
            player_->setTrueCoord(stop.second->getLocation());
            qDebug() << "player joins stop" << stop.first->getName();
            return true;
        }
    }
    return false;
}

int City::getCurrentFuel() const
{
    if (!multiplayer_) {
        return player_->getFuel();
    }
    return player_->getFuel() + player2_->getFuel();
}

}
