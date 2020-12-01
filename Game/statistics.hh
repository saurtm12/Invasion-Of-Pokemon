#ifndef STATISTICS_HH
#define STATISTICS_HH

#include "../Course/CourseLib/interfaces/istatistics.hh"
#include <QDebug>

/**
 * @file statistics.hh
 * @brief Define Statistic class which is a storage for statistics of current game state.
 */
namespace Stats
{

/**
 * @brief The Statistics class
 * @inherits iStatistic.
 */
class Statistics : Interface::IStatistics
{
public:
    /**
     * @brief Statistics constructor
     * @param passengers number of passenger initially
     * @param buses number of buses initially
     * @post exception guarantee: strong
     * @exception InitError - initial passengers or buses is negative
     */
    Statistics(int passengers = 0, int buses = 0);

    /**
     * @brief some amount of passengers is added/removed
     * @param num number of passengers to be added or removed
     * @post exception guarantee: strong
     * @exception GameError - Remove amount more than currently exist
     */
    void morePassengers(int num);

    /**
     * @brief a Bus is removed forcefully (by external reasons)
     * @pre There must be buses running in traffic
     * @post exception guarantee: no throw
     */
    void nysseRemoved();

    /**
     * @brief a Bus is introduced
     * @post exception guarantee: no throw
     */
    void newNysse();

    /**
     * @brief a Bus is removed by wrong addition (by internal reasons)
     * @post exception guarantee: no throw
     */
    void nysseLeft();

    /**
     * @brief scores is added to player
     * @post exception guarantee: no throw
     */
    int addScores(int score = 20);

    /**
     * @brief get total number of buses
     * @post exception guarantee: no throw
     */
    int getNumberOfBuses() const;

    /**
     * @brief get total number of passengers
     * @post exception guarantee: no throw
     */
    int getNumberOfPassengers() const;

    /**
     * @brief get total number of scores
     * @post exception guarantee: no throw
     */
    int getScores() const;

private:
    int passengers_;
    int buses_;
    int scores_;
};

}

#endif // STATISTICS_HH
