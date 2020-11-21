#include "bus.hh"

Bus::Bus(std::shared_ptr<CourseSide::BusData> busData) :
    CourseSide::Nysse(busData->routeNumber)
{

}
