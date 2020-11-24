#include "bus.hh"

namespace Model
{

Bus::Bus(std::shared_ptr<CourseSide::BusData> busData, QTime time) :
    CourseSide::Nysse(busData->routeNumber), schedule_(busData->schedule), timeIter_(schedule_.begin())
{
    setRoute(busData->timeRoute2, busData->schedule.front());
    calcStartingPos(time);
}

QTime Bus::getNextSchedule()
{
    if (++timeIter_ == schedule_.end()) {
        timeIter_ = schedule_.begin();
        return *timeIter_;
    }

    return *(++timeIter_);
}

void Bus::moveToLocation(Interface::Location loc)
{
    Nysse::move(loc);
    Character::setCoord(loc);
}

}
