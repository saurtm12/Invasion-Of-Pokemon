#include "mainwindow.hh"
#include "ui_mainwindow.h"

const int PADDING = 10;

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

  map =new QGraphicsScene(this);
  ui->gameView->setScene(map);
  map->setSceneRect(0,0,width_, height_);
  resize(minimumSizeHint());

  QImage background = QImage(":/offlinedata/offlinedata/kartta_pieni_500x500.png");
  this->setPicture(background);

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

}

void MainWindow::updateCoords(int nX, int nY)
{

}

void MainWindow::setPicture(QImage &img)
{
  map->setBackgroundBrush(img);
}


void MainWindow::onStartButtonClicked()
{

}
