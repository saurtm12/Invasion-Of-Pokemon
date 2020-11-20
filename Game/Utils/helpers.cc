#include "../Utils/helpers.hh"

namespace Utils {

Location convertLocation(Location loc) {
    loc.setXY(loc.giveX() + X_OFFSET_MAP, Y_OFFSET_MAP - loc.giveY());
    return loc;
}

}
