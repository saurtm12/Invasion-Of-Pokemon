#include "bus.hh"

namespace Model
{

Bus::Bus(unsigned int line) : CourseSide::Nysse(line)
{

}

void Bus::moveToLocation(Interface::Location loc)
{
    Nysse::move(loc);
    Character::setCoord(loc);
}

}
