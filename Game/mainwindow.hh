#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH
#include <dialog.hh>

#include "../Course/CourseLib/graphics/simpleactoritem.hh"
#include "../Course/CourseLib/core/location.hh"
#include "character.hh"
#include <QMainWindow>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include <iostream>
#include <memory>
#include <QVector>
#include <map>

using namespace CourseSide;
using namespace Interface;

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

  void addCharacter(Model::Character& character);
  void addActor(int locX, int locY, int type=0);
  void updateCoords(int nX, int nY);
  void setPicture(QImage &img);

signals:
  void gameStarted();

private slots:
  void onStartButtonClicked();

private:
  Ui::MainWindow *ui;
  QGraphicsScene *map;
  QTimer *timer;
  QVector<QGraphicsItem*> actors_;
  SimpleActorItem* last_;

  QVector<QGraphicsItem*> characters_;

  int width_ = 950;
  int height_ = 500;
  int tick_ = 500;
};

#endif // MAINWINDOW_HH
