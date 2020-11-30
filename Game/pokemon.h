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
#include <QPushButton>

/**
 * @file pokemon.hh
 * @brief Pokemon class as an actor, and function read pokemons from resource.
 */
namespace Model {

/**
 * @brief The Pokemon class
 */
class Pokemon
{
public:
    /**
   * @brief Pokemon constructor
   * @param id
   * @param category
   * @param name
   * @param description
   * @param path
   * @param score
   * @param hp
   * @param attack
   * @param defense
   * @param speed
   * @param total
   * @post pokemon is not in removed state by default.
   */
  Pokemon(int id, QString category, QString name, QString description,
          QString path, int score, int hp, int attack, int defense, int speed, int total);

  /**
   * @brief Pokemon destructor - do nothing.
   * @post the pokemon is successfully destructed.
   */
  ~Pokemon();

  /**
   * @brief dialogInfo
   * @param parent
   * @return an info graphical dialog which contains all the information about this pokemon.
   * @post Exception guarantee: no throw
   * @exception the program might throw std::bad_alloc when out of memory.
   */
  QDialog* dialogInfo(QWidget* parent=0) const;

  /**
   * @brief getImage
   * @return image of this pokemon.
   * @post exception guarantee: no throw
   */
  QImage getImage() const;

  /**
   * @brief score
   * @return the score for this pokemon
   * @post exception guarantee: no throw
   */
  int score() const;
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

// Base score for each score_ pokemon has.
const int BASE = 100;

/**
 * @brief readPokemonData
 * @param resource : Path of resource file
 * @return vector of available pokemons
 */
std::vector<Pokemon> readPokemonData(std::string resource);

/**
 * @brief getIntensity
 * @param value
 * @param maxvalue
 * @return The color respects to the power of pokemons.
 */
auto getIntensity(const int& value,const int& maxvalue);

}


#endif // PIKACHU_H
