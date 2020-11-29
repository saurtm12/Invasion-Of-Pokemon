#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH
#include <dialog.hh>

#include "../Course/CourseLib/core/location.hh"
#include "../Course/CourseLib/core/logic.hh"
#include "city.h"
#include "statistics.hh"
#include "Utils/helpers.hh"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include <iostream>
#include <memory>
#include <QVector>
#include <map>
#include <QString>
#include <QProgressBar>

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
  void startGame();

signals:
  void gameStarted();
  void keyPressed(int key);
private slots:
  void onStartButtonClicked();
  void onBallCollided(Pokemon pokemon);
  void openBag();
  void updateFuelBar(int fuel);
  void actorCountChanged(std::shared_ptr<IActor> actor, int delta);
  void onGameOver();
private:
  void keyPressEvent(QKeyEvent *event) override;

  Ui::MainWindow *ui;
  Logic* logic_;
  std::shared_ptr<City> city_;
  QProgressBar* fuelBar_;
  Stats::Statistics stats_;
  int width_ = 1095;
  int height_ = 592;
  int tick_ = 500;
  Utils::GameSetting gameSetting_;
  bool isStarted;
};

#endif // MAINWINDOW_HH
