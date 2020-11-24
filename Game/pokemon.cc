#include "pokemon.h"
namespace Model {

Pokemon::Pokemon(int id, QString category, QString name, QString description, QString path, int score, int attack, int defense, int speed, int total):
  id_(id),
  category_(category),
  name_(name),
  description_(description),
  score_(score),
  attack_(attack),
  defense_(defense),
  speed_(speed),
  total_(total_)
{
  img_ = QImage(path);
}

}
