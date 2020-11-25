#ifndef HELPERS_HH
#define HELPERS_HH

#include "../Course/CourseLib/core/location.hh"
#include "../Course/CourseLib/actors/nysse.hh"
#include "../Course/CourseLib/actors/passenger.hh"
#include "../Course/CourseLib/actors/stop.hh"
#include <QObject>

using namespace Interface;

namespace Utils {

const int X_OFFSET_MAP = 352;
const int Y_OFFSET_MAP = 558;

const std::string NYSSE_TYPE = typeid(CourseSide::Nysse).name();
const std::string PASSENGER_TYPE = typeid(CourseSide::Passenger).name();
const std::string STOP_TYPE = typeid(CourseSide::Stop).name();

Location convertLocation(Location loc);

}

#endif // HELPERS_HH
