#ifndef HELPERS_HH
#define HELPERS_HH

#include "../Course/CourseLib/core/location.hh"
#include "../city.h"
#include <QObject>
using namespace Interface;

namespace Utils {

const int X_OFFSET_MAP = 350;
const int Y_OFFSET_MAP = 558;

Location convertLocation(Location loc);

}

namespace Model {

const std::vector< int >  KEY_FUNC =
{
  Qt::Key_W,
  Qt::Key_S,
  Qt::Key_A,
  Qt::Key_D,
  Qt::Key_Space
};

}
#endif // HELPERS_HH
