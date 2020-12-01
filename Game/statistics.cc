#include "statistics.hh"
#include "../Course/CourseLib/errors/initerror.hh"
#include "../Course/CourseLib/errors/gameerror.hh"

namespace Stats
{

Statistics::Statistics(int passenger, int buses):
    passengers_(passenger), buses_(buses), scores_(0)
{
    try {
        if (passengers_ < 0) {
            throw Interface::InitError("Passengers count cannot be negative.");
        }
    } catch (const Interface::InitError& e) {
        qDebug() << e.what();
        passengers_ = 0;
    }

    try {
        if (buses_ < 0) {
            throw Interface::InitError("Buses count cannot be negative.");
        }
    } catch (const Interface::InitError& e) {
        qDebug() << e.what();
        buses_ = 0;
    }
}

void Statistics::morePassengers(int num)
{
    try {
        if (passengers_ + num < 0) {
            throw Interface::GameError("Passengers count reached negative after removed");
        }
        passengers_ += num;
    }  catch (const Interface::GameError& e) {
        qDebug() << e.what();
    }
}

void Statistics::nysseRemoved()
{
    --buses_;
}

void Statistics::newNysse()
{
    ++buses_;
}

void Statistics::nysseLeft()
{
    --buses_;
}

int Statistics::addScores(int score)
{
    scores_ += score;
    return scores_;
}

int Statistics::getNumberOfBuses() const
{
    return buses_;
}

int Statistics::getNumberOfPassengers() const
{
    return passengers_;
}

int Statistics::getScores() const
{
    return scores_;
}

}
