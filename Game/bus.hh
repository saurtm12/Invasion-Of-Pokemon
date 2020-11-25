#ifndef BUS_HH
#define BUS_HH

#include "../Course/CourseLib/actors/nysse.hh"
#include "../Course/CourseLib/offlinereader.hh"
#include "character.hh"
#include "Utils/helpers.hh"

namespace Model
{

class Bus : public CourseSide::Nysse, public Model::Character
{
public:
    Bus(unsigned int line);

    void moveToLocation(Interface::Location loc);

private:

};

}

#endif // BUS_HH
