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
    file.open(SCORE_FILE);
    if (!file)
    {
        qDebug() <<"File empty";
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

void writeScore(std::vector<int> highScores)
{
    std::ofstream file;
    file.open(SCORE_FILE, std::ofstream::out | std::ofstream::trunc );
    for (auto& score: highScores)
    {
        qDebug() <<score;
        file << score << "\n";
    }
    file.close();
}

}
