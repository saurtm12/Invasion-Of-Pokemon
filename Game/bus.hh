#ifndef BUS_HH
#define BUS_HH

#include "../Course/CourseLib/actors/nysse.hh"
#include "character.hh"


class Bus : public CourseSide::Nysse, public Model::Character
{
public:
    Bus();
};

#endif // BUS_HH
