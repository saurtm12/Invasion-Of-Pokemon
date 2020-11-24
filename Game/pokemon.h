#ifndef PIKACHU_H
#define PIKACHU_H

#include <QString>
#include <QImage>
#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <vector>
#include <string>
#include <iostream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QString>
#include <QLabel>
#include <QTextBrowser>
#include <QProgressBar>
#include <QPalette>
#include <QColor>

namespace Model {

class Pokemon
{
public:
  Pokemon(int id, QString category, QString name, QString description,
          QString path, int score, int hp, int attack, int defense, int speed, int total);

  QDialog* dialogInfo(QWidget* parent=0) const;
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

std::vector<Pokemon> readPokemonData(std::string resource);
auto getIntensity(const int& value,const int& maxvalue);

}


#endif // PIKACHU_H
