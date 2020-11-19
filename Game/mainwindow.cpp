#include "mainwindow.hh"
#include "ui_mainwindow.h"

const qreal PADDING = 10;
const qreal MAPWIDTH = 1095;
const qreal MAPHEIGHT = 592;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  Dialog *dialog = new Dialog(this);
  dialog->exec();


  ui->setupUi(this);
  ui->gameView->setFixedSize(width_, height_);
  ui->centralwidget->setFixedSize(width_ + ui->startButton->width() + PADDING, height_ + PADDING);

  ui->startButton->move(width_+ PADDING, PADDING);

  map = new QGraphicsScene(this);
  QImage background = QImage(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
  this->setPicture(background);
  ui->gameView->setScene(map);
  map->setSceneRect(0, 0, width_, height_);


  resize(minimumSizeHint());
//  ui->gameView->fitInView(0, 0, MAPWIDTH, MAPHEIGHT, Qt::KeepAspectRatio);
  Location loc(6825813, 3328734);
  this->addActor(loc.giveX(), loc.giveY(), 0);
  qDebug() << loc.giveX() << loc.giveY();

  connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);

  timer = new QTimer(this);
}

MainWindow::~MainWindow()
{
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

void MainWindow::addActor(int locX, int locY, int type)
{
    SimpleActorItem* nActor = new SimpleActorItem(locX, locY, type);
    actors_.push_back(nActor);
    map->addItem(nActor);
    last_ = nActor;
}

void MainWindow::updateCoords(int nX, int nY)
{
    last_->setCoord(nX, nY);
}

void MainWindow::setPicture(QImage &img)
{
  map->setBackgroundBrush(img);
}

void MainWindow::onStartButtonClicked()
{
    this->updateCoords(566, 200);
}
