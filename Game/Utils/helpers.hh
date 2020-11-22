#ifndef HELPERS_HH
#define HELPERS_HH

#include "../Course/CourseLib/core/location.hh"
#include <QObject>

using namespace Interface;

namespace Utils {

const int X_OFFSET_MAP = 352;
const int Y_OFFSET_MAP = 558;

Location convertLocation(Location loc);

}

#endif // HELPERS_HH
