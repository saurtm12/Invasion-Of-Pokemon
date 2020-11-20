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

    // GAME START FROM HERE --- NEED NEW FUNCTION gameStart
    city = new City(this);

    // setScene for Graphic view
    city->getMap()->setSceneRect(0, 0, width_, height_);
    ui->gameView->setSceneRect(0, 0, 1092, 590);
    ui->gameView->setScene(city->getMap());
    city->startGame();
    qDebug() << city->getMap()->sceneRect();
//    resize(minimumSizeHint());
//    ui->gameView->fitInView(city->getMap()->sceneRect(), Qt::KeepAspectRatio);

    // connect events
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);

    timer = new QTimer(this);
}

MainWindow::~MainWindow()
{
  for (auto item: actors_) {
      delete item;
  }

//  for (auto item: characters_) {
//      delete item;
//  }
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
    city->addItem(nActor);
    last_ = nActor;
}

void MainWindow::updateCoords(int nX, int nY)
{
    last_->setCoord(nX, nY);
}

void MainWindow::onStartButtonClicked()
{
    if (!last_) {
        return;
    }
    this->updateCoords(566, 200);
}
