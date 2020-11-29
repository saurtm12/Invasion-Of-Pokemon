#ifndef STATISTICS_HH
#define STATISTICS_HH

#include "../Course/CourseLib/interfaces/istatistics.hh"

namespace Stats
{

class Statistics : Interface::IStatistics
{
public:
    Statistics();

    void morePassengers(int num);
    void nysseRemoved();
    void newNysse();
    void nysseLeft();
    int addScores(int score = 20);

    int getNumberOfBuses() const;
    int getNumberOfPassengers() const;
    int getScores() const;

private:
    int passengers_;
    int buses_;
    int scores_;
};

}

#endif // STATISTICS_HH
