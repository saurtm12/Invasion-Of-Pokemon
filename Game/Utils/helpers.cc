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

std::vector<int> getHighScores()
{
    std::ifstream file;
    file.open(SCORE_FILE, std::ios::in);
    try {
        if (!file.is_open())
        {
            throw InitError("File not found");
        }
    }  catch (const InitError& e) {
        qDebug() << e.what();
        return {};
    }

    int temp = 0;
    std::vector<int> highScores;
    while (file >> temp) {
        highScores.push_back(temp);
    }
    file.close();
    return highScores;
}

void writeScore(const std::vector<int>& highScores)
{
    std::ofstream file;
    file.open(SCORE_FILE, std::ofstream::out | std::ofstream::trunc);

    try {
        if (!file.is_open())
        {
            throw InitError("File not found");
        }
    }  catch (const InitError& e) {
        qDebug() << e.what();
        return;
    }

    for (auto& score: highScores)
    {
        file << score << "\n";
    }

    file.close();
}

bool needUpdate(const Location& prev, const Location& cur)
{
    int prevX = prev.giveX();
    int prevY = prev.giveY();
    int curX = cur.giveX();
    int curY = cur.giveY();
    return !(
        (prevX < -10 || prevX >= WIDTH_WITH_OFFSET || prevY < -10 || prevY >= HEIGHT_WITH_OFFSET) &&
        (curX < -10 || curX >= WIDTH_WITH_OFFSET || curY < -10 || curY >= HEIGHT_WITH_OFFSET)
    );
}

}
