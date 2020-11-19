#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH
#include <dialog.hh>

#include "../Course/CourseLib/graphics/simpleactoritem.hh"
#include "../Course/CourseLib/core/location.hh"
#include "character.hh"
#include "city.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include <iostream>
#include <memory>
#include <QVector>
#include <map>
#include <QString>

using namespace CourseSide;
using namespace Interface;
using namespace Model;
namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void setSize(int w, int h);
  void setTick(int t);

//  void addCharacter(Model::Character& character);
  void addActor(int locX, int locY, int type=0);
  void updateCoords(int nX, int nY);
  void readFiles();
signals:
  void gameStarted();

private slots:
  void onStartButtonClicked();

private:
  Ui::MainWindow *ui;
  City *city;
  QTimer *timer;
  QVector<QGraphicsItem*> actors_;
  SimpleActorItem* last_;

  //QVector<QGraphicsItem*> characters_;



  int width_ = 950;
  int height_ = 500;
  int tick_ = 500;

};

#endif // MAINWINDOW_HH
