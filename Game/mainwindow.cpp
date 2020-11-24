#include "mainwindow.hh"
#include "ui_mainwindow.h"

const qreal PADDING = 10;
const qreal MAPWIDTH = 1095;
const qreal MAPHEIGHT = 592;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
    // add first dialog
    Dialog *dialog = new Dialog(this);
    dialog->exec();



    // setup window
    ui->setupUi(this);
    ui->gameView->setFixedSize(width_, height_);
    ui->centralwidget->setFixedSize(width_ + ui->startButton->width() + PADDING, height_ + PADDING);

    ui->startButton->move(width_+ PADDING, PADDING);
    ui->resumeBtn->move(width_+ PADDING, 300);
    ui->pauseBtn->move(width_+ PADDING, 380);

//    resize(minimumSizeHint());
//    ui->gameView->fitInView(city->getMap()->sceneRect(), Qt::KeepAspectRatio);

    // connect events
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);
    connect(ui->resumeBtn, &QPushButton::clicked, this, &MainWindow::resumeGame);
    connect(ui->pauseBtn, &QPushButton::clicked, this, &MainWindow::pauseGame);

    startGame();
    //test
    qDebug()<< pokemons_.size();
    QDialog* dia = pokemons_.at(0).dialogInfo(this);
    dia->exec();
}

MainWindow::~MainWindow()
{
  for (auto item: actors_) {
      delete item;
  }

//  for (auto item: characters_) {
//      delete item;
//  }
  delete timer;
  delete city;
  delete ui;
}

void MainWindow::setSize(int w, int h)
{
    width_ = w;
    height_ = h;
}

void MainWindow::setTick(int t)
{

}

//void MainWindow::addCharacter(Model::Character& character) {
//    QGraphicsPixmapItem* pm = character.setImage(city);
//    characters_.append(pm);
//}

void MainWindow::addActor(int locX, int locY, int type)
{
    SimpleActorItem* nActor = new SimpleActorItem(locX, locY, type);
    actors_.push_back(nActor);
    city->getMap()->addItem(nActor);
    last_ = nActor;
}

void MainWindow::updateCoords(int nX, int nY)
{
  last_->setCoord(nX, nY);
}

void MainWindow::startGame()
{
  // GAME START FROM HERE --- NEED NEW FUNCTION gameStart
    timer = new QTimer(this);
    timer->setInterval(1000);
    city = new City(this);

  // setScene for Graphic view
    city->getMap()->setSceneRect(0, 0, width_, height_);
    ui->gameView->setSceneRect(0, 0, 1092, 590);
    ui->gameView->setScene(city->getMap());

    pokemons_ = readPokemonData(":/pokemonImg/Pokemon/");
    city->startGame();

    //connect keys
    connect(this, &MainWindow::keyPressed, city, Model::HANDLEFUNCT);
    connect(timer, &QTimer::timeout, city, &City::changeTime);
}

void MainWindow::onStartButtonClicked()
{
    timer->start();
    if (!last_) {
        return;
    }
}

void MainWindow::pauseGame()
{
    timer->stop();
}

void MainWindow::resumeGame()
{
    timer->start();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
  // LOOK BACK IF THE GAME NEED TO BE STARTED OR NOT.
  emit keyPressed( static_cast<int>(event->key()));
}
