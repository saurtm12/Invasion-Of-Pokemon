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
  nDialog->setFixedSize(750,500);

  QGraphicsView* view = new QGraphicsView(nDialog);
  QGraphicsScene* scene = new QGraphicsScene(view);
  QGraphicsPixmapItem* imgItem = new QGraphicsPixmapItem(QPixmap::fromImage(img_));
  view->setSceneRect(10,10,485,485);
  view->setScene(scene);
  view->show();
  scene->addItem(imgItem);

  QLabel* name = new QLabel(QString("Name: ")+name_,nDialog);
  name->move(510,10);

  QLabel* category = new QLabel(QString("Category: ") + category_,nDialog);
  category->move(510,50);

  QLabel* description = new QLabel("Description: ", nDialog);
  description->move(510, 90);

  QTextBrowser* descriptionValue = new QTextBrowser(nDialog);
  descriptionValue->setText(description_);
  descriptionValue->move(510,110);
  descriptionValue->setFixedSize(230,120);

  QLabel* score = new QLabel("Score: ", nDialog);
  score->move(510, 240);
  QProgressBar* scoreValue = new QProgressBar(nDialog);
  scoreValue->setFormat(QString("%v"));
  scoreValue->move(510,260);
  scoreValue->setMaximum(5);
  scoreValue->setValue(score_);

//  QLabel* score = new QLabel("Score: ", nDialog);
//  score->move(510, 240);
//  QProgressBar* scoreValue = new QProgressBar(nDialog);
//  scoreValue->setFormat(QString("%v"));
//  scoreValue->move(510,260);
//  scoreValue->setMaximum(5);
//  scoreValue->setValue(score_);

  qDebug() << Qt::darkRed;
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
