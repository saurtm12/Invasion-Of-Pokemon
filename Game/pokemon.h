#ifndef PIKACHU_H
#define PIKACHU_H

#include <QString>
#include <QImage>
namespace Model {

class Pokemon
{
public:
  Pokemon(int id, QString category, QString name, QString description,
          QString path, int score, int attack, int defense, int speed, int total);
private:
  int id_;
  QString category_;
  QString name_;
  QString description_;
  QImage img_;
  int score_;
  int hp_;
  int attack_;
  int defense_;
  int speed_;
  int total_;
};

}


#endif // PIKACHU_H
