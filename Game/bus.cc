#include "bus.hh"

namespace Model
{

Bus::Bus(std::shared_ptr<CourseSide::BusData> busData) :
    CourseSide::Nysse(busData->routeNumber), schedule_(busData->schedule), timeIter_(schedule_.begin()), time_(*timeIter_)
{
    setRoute(busData->timeRoute2, busData->schedule.front());
    calcStartingPos(busData->schedule.front());
    setCoord(giveLocation());
}

QTime Bus::getNextSchedule()
{
    if (++timeIter_ == schedule_.end()) {
        timeIter_ = schedule_.begin();
        time_ = *timeIter_;
        return *timeIter_;
    }

    time_ = *(++timeIter_);
    return *timeIter_;
}

QTime Bus::advanceTime()
{
    return time_.addSecs(15);
}

void Bus::setCoord(Interface::Location loc)
{
    Nysse::move(loc);
    Character::move(loc);
}

}
