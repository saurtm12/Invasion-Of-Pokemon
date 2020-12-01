#include "pokemon.h"
namespace Model {

auto getIntensity(const int &value, const int &maxvalue)
{
    double rate = value * 1.0 / maxvalue;
    if (rate <= 0.21)
    {
    return Qt::cyan;
    }
    if (rate <= 0.41)
    {
    return Qt::blue;
    }
    if (rate <= 0.61)
    {
    return Qt::darkYellow;
    }
    if (rate <= 0.81)
    {
    return Qt::red;
    }
    return Qt::darkRed;
}

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

Pokemon::~Pokemon()
{

}

QDialog *Pokemon::dialogInfo(QWidget *parent) const
{
    if (parent == 0){
    return nullptr;
    }
    QDialog* nDialog = new QDialog(parent);
    nDialog->setWindowTitle("YOU HAVE CAUGHT THIS POKEMON!");
    nDialog->setFixedSize(750, 530);

    QGraphicsView* view = new QGraphicsView(nDialog);
    QGraphicsScene* scene = new QGraphicsScene(view);
    QGraphicsPixmapItem* imgItem = new QGraphicsPixmapItem(QPixmap::fromImage(img_));
    view->setSceneRect(10, 10, 485, 485);
    view->setScene(scene);
    view->show();
    scene->addItem(imgItem);

    QLabel* name = new QLabel(QString("Name: ")+name_, nDialog);
    name->move(510,10);

    QLabel* category = new QLabel(QString("Category: ") + category_, nDialog);
    category->move(510, 50);

    QLabel* description = new QLabel("Description: ", nDialog);
    description->move(510, 90);

    QTextBrowser* descriptionValue = new QTextBrowser(nDialog);
    descriptionValue->setText(description_);
    descriptionValue->move(510, 110);
    descriptionValue->setFixedSize(230, 120);

    QLabel* score = new QLabel("Score: ", nDialog);
    score->move(510, 240);
    QProgressBar* scoreValue = new QProgressBar(nDialog);
    scoreValue->setFormat(QString("%v"));
    scoreValue->move(510, 260);
    scoreValue->setFixedWidth(200);
    scoreValue->setMaximum(5);
    scoreValue->setValue(score_);
    QPalette p = scoreValue->palette();
    p.setColor(QPalette::Highlight, getIntensity(score_,5));
    scoreValue->setPalette(p);

    QLabel* hp = new QLabel("HP: ", nDialog);
    hp->move(510, 290);
    QProgressBar* hpValue = new QProgressBar(nDialog);
    hpValue->setFormat(QString("%v"));
    hpValue->move(510, 310);
    hpValue->setFixedWidth(200);
    hpValue->setMaximum(10);
    hpValue->setValue(hp_);
    p = hpValue->palette();
    p.setColor(QPalette::Highlight, getIntensity(hp_, 10));
    hpValue->setPalette(p);

    QLabel* attack = new QLabel("Attack: ", nDialog);
    attack->move(510, 340);
    QProgressBar* attackValue = new QProgressBar(nDialog);
    attackValue->setFormat(QString("%v"));
    attackValue->move(510, 360);
    attackValue->setFixedWidth(200);
    attackValue->setMaximum(10);
    attackValue->setValue(attack_);
    p = attackValue->palette();
    p.setColor(QPalette::Highlight, getIntensity(attack_, 10));
    attackValue->setPalette(p);

    QLabel* defense = new QLabel("Defense: ", nDialog);
    defense->move(510, 390);
    QProgressBar* defenseValue = new QProgressBar(nDialog);
    defenseValue->setFormat(QString("%v"));
    defenseValue->move(510, 410);
    defenseValue->setFixedWidth(200);
    defenseValue->setMaximum(10);
    defenseValue->setValue(defense_);
    p = defenseValue->palette();
    p.setColor(QPalette::Highlight, getIntensity(defense_, 10));
    defenseValue->setPalette(p);

    QLabel* speed = new QLabel("Speed: ", nDialog);
    speed->move(510, 440);
    QProgressBar* speedValue = new QProgressBar(nDialog);
    speedValue->setFormat(QString("%v"));
    speedValue->move(510, 460);
    speedValue->setFixedWidth(200);
    speedValue->setMaximum(10);
    speedValue->setValue(speed_);
    p = speedValue->palette();
    p.setColor(QPalette::Highlight, getIntensity(speed_, 10));
    speedValue->setPalette(p);

    QPushButton* confirm = new QPushButton(nDialog);
    confirm->move(630, 490);
    confirm->setText("OK");
    QObject::connect(confirm, &QPushButton::clicked,
                   nDialog, &QDialog::accept);
    return nDialog;
}

QImage Pokemon::getImage() const
{
    return img_;
}

int Pokemon::score() const
{
    return score_*BASE;
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

    QJsonParseError parse_error;
    QJsonDocument document = QJsonDocument::fromJson(filecontent.toUtf8()  , &parse_error);

    if (parse_error.error != QJsonParseError::NoError) {
      qDebug() << "Error parsing pokemon JSON: " << parse_error.errorString() << " at: " << filecontent.mid(parse_error.offset-3, parse_error.offset+3);
      return {};
    }

    QJsonObject jsonObject = document.object();
    QJsonArray jsonArray = document.array();

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
