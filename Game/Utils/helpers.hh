#ifndef HELPERS_HH
#define HELPERS_HH

#include "../Course/CourseLib/core/location.hh"
#include "../Course/CourseLib/actors/nysse.hh"
#include "../Course/CourseLib/actors/passenger.hh"
#include "../Course/CourseLib/actors/stop.hh"
#include "../Course/CourseLib/errors/initerror.hh"
#include <random>
#include <fstream>
#include <string>
#include <vector>
#include <qdebug.h>
using namespace Interface;

namespace Utils {

const std::string SCORE_FILE = "../../doesnt-matter/Game/Text/score.txt";

/**
 * @brief The GameSetting struct
 */
struct GameSetting
{
    int hour_;
    int min_;
    int numberOfBall_;
    int fuel_;
    int speed_;
};

const int X_OFFSET_MAP = 352;
const int Y_OFFSET_MAP = 558;

const std::string NYSSE_TYPE = typeid(CourseSide::Nysse).name();
const std::string PASSENGER_TYPE = typeid(CourseSide::Passenger).name();
const std::string STOP_TYPE = typeid(CourseSide::Stop).name();

Location convertLocation(Location loc);
int generateRandom(int lo, int hi);
QString generateTooltipTextFromPassenger(int num, std::string actor);
void writeScore(std::vector<int> highScores);
std::vector<int> getHighScores();
}

#endif // HELPERS_HH
