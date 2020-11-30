#include "../Utils/helpers.hh"

namespace Utils {

Location convertLocation(Location loc) {
    loc.setXY(loc.giveX() + X_OFFSET_MAP, Y_OFFSET_MAP - loc.giveY());
    return loc;
}

int generateRandom(int lo, int hi)
{
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distr(lo, hi - 1);
    return distr(generator);
}

QString generateTooltipTextFromPassenger(int num, std::string actor)
{
    return QString::fromStdString(std::to_string(num) + " passengers in the " + actor);
}

}
