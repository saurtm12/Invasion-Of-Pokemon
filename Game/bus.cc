#include "bus.hh"

namespace Model
{

Bus::Bus(std::shared_ptr<CourseSide::BusData> busData) :
    CourseSide::Nysse(busData->routeNumber)
{
    setRoute(busData->timeRoute2, busData->schedule.front());
    calcStartingPos(busData->schedule.front());
    setCoord(Utils::convertLocation(giveLocation()));
}

}
