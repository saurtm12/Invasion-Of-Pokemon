#ifndef PIKACHU_H
#define PIKACHU_H

#include <QString>
#include <QImage>
namespace Model {

class Pokemon
{
public:
  Pokemon();
private:
  int id;
  QString element_;
  QString name;
  QString description;
  QImage img_;
  int hp_;
  int attack_;
  int defense_;
  int speed_;
  int total_;

};

}


#endif // PIKACHU_H
