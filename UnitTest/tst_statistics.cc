#include <QtTest>
#include "statistics.hh"

// add necessary includes here

class StatisticsTest : public QObject
{
    Q_OBJECT

public:
    StatisticsTest();
    ~StatisticsTest();

private Q_SLOTS:
    void testInit();
    void testInit_data();

    void testAddNysse();
    void testAddNysse_data();

    void testAddPassenger();
    void testAddPassenger_data();

    void testAddScore();
    void testAddScore_data();
};

StatisticsTest::StatisticsTest()
{

}

StatisticsTest::~StatisticsTest()
{

}

void StatisticsTest::testInit()
{
    QFETCH(int, passenger);
    QFETCH(int, bus);
    QFETCH(int, expectPassenger);
    QFETCH(int, expectBus);

    Stats::Statistics stats(passenger, bus);
    QVERIFY2(stats.getNumberOfPassengers() == expectPassenger, "Wrong passengers");
    QVERIFY2(stats.getNumberOfBuses() == expectBus, "Wrong buses");
}

void StatisticsTest::testInit_data()
{
    QTest::addColumn<int>("passenger");
    QTest::addColumn<int>("bus");
    QTest::addColumn<int>("expectPassenger");
    QTest::addColumn<int>("expectBus");

    QTest::addRow("Negative passenger")         << -2 << 2 << 0 << 2;
    QTest::addRow("Negative bus")               << 2  << -2 << 2 << 0;
    QTest::addRow("Both valid")                 << 10 << 20 << 10 << 20;
}

void StatisticsTest::testAddNysse()
{
    QFETCH(int, busNum);

    Stats::Statistics stats(0, busNum);
    QVERIFY2(stats.getNumberOfBuses() == busNum, "Not init bus with correct give number");

    stats.newNysse();
    QVERIFY2(stats.getNumberOfBuses() == busNum + 1, "Not increase bus count by one!");

    stats.newNysse();
    QVERIFY2(stats.getNumberOfBuses() == busNum + 2, "Not increase bus count by two!");

    stats.nysseRemoved();
    stats.nysseLeft();
    QVERIFY2(stats.getNumberOfBuses() == busNum, "Not decrease bus count correspondingly!");
}

void StatisticsTest::testAddNysse_data()
{
    QTest::addColumn<int>("busNum");

    QTest::addRow("Five buses")                 << 5;
    QTest::addRow("No bus initially")           << 0;
    QTest::addRow("A very big one")             << 200000;
}

void StatisticsTest::testAddPassenger()
{
    QFETCH(int, init);
    QFETCH(int, num);
    QFETCH(int, expect);

    Stats::Statistics stats(init, 0);
    stats.morePassengers(num);
    QVERIFY2(stats.getNumberOfPassengers() == expect, "Wrong number of passengers after modify");
}

void StatisticsTest::testAddPassenger_data()
{
    QTest::addColumn<int>("init");
    QTest::addColumn<int>("num");
    QTest::addColumn<int>("expect");

    QTest::addRow("Normal new passengers")      << 0 << 16 << 16;
    QTest::addRow("Initial negative")           << -2 << 10 << 10;
    QTest::addRow("Remove passengers")          << 10 << -2 << 8;
    QTest::addRow("Remove more than exist")     << 10 << -12 << 10;
}

void StatisticsTest::testAddScore()
{
    QFETCH(int, score);
    QFETCH(int, expect);

    Stats::Statistics stats;
    stats.addScores(score);
    QVERIFY2(stats.getScores() == expect, "Wrong scores");
}

void StatisticsTest::testAddScore_data()
{
    QTest::addColumn<int>("score");
    QTest::addColumn<int>("expect");

    QTest::addRow("Add 20 scores")              << 20 << 20;
    QTest::addRow("Minus 2 scores")             << -2 << -2;
    QTest::addRow("Do not add anything")        << 0 << 0;
}

QTEST_APPLESS_MAIN(StatisticsTest)

#include "tst_statistics.moc"
