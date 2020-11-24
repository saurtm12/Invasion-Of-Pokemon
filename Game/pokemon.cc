#include "pokemon.h"
namespace Model {

Pokemon::Pokemon(int id, QString category, QString name, QString description,
                 QString path, int score, int hp,
                 int attack, int defense, int speed, int total):
  id_(id),
  category_(category),
  name_(name),
  description_(description),
  score_(score),
  hp_(hp),
  attack_(attack),
  defense_(defense),
  speed_(speed),
  total_(total)
{
  img_ = QImage(path);
}

QDialog *Pokemon::dialogInfo(QWidget *parent) const
{
  if (parent == 0){
    return nullptr;
  }
  QDialog* nDialog = new QDialog(parent);
  return nDialog;
}

std::vector<Pokemon> readPokemonData(std::string resource)
{
  QString path = QString::fromStdString(resource);

  QString filecontent;
  QString pokemonFile = path + QString("pokemons.json");

  QFile file;
  file.setFileName(pokemonFile);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  filecontent = file.readAll();
  file.close();

  qDebug() << pokemonFile;
  QJsonParseError parse_error;
  QJsonDocument document = QJsonDocument::fromJson( filecontent.toUtf8()  , &parse_error);
  if (parse_error.error != QJsonParseError::NoError) {
      qDebug() << "Error parsing pokemon JSON: " << parse_error.errorString() << " at: " << filecontent.mid(parse_error.offset-3, parse_error.offset+3);
      return {};
  }
  QJsonObject jsonObject = document.object();
  QJsonArray jsonArray = document.array();

  qDebug() << pokemonFile;
  std::vector <Pokemon> pokemons;
  pokemons.reserve(jsonArray.size());

  for (int i = 0; i < jsonArray.size(); i++) {

      QJsonObject o = jsonArray.at(i).toObject();
      int id = o.value("id").toString().toInt();
      QString category = o.value("category").toString();
      QString name = o.value("name").toString();
      QString description = o.value("description").toString();
      QString img = path + o.value("img").toString();
      int score = o.value("score").toString().toInt();
      int hp = o.value("hp").toString().toInt();
      int attack = o.value("attack").toString().toInt();
      int defense = o.value("defense").toString().toInt();
      int speed = o.value("speed").toString().toInt();
      int total = o.value("total").toString().toInt();
      Pokemon newPokemon = Pokemon(id, category, name, description, img, score, hp, attack, defense, speed, total);
      pokemons.push_back(newPokemon);
    }
  return pokemons;
}


}
