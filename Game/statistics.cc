#include "statistics.hh"

namespace Stats
{

Statistics::Statistics(): passengers_(0), buses_(0), scores_(0)
{

}

void Statistics::morePassengers(int num)
{
    passengers_ += num;
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
