#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "../Course/CourseLib/core/location.hh"
#include "../Course/CourseLib/core/logic.hh"
#include "city.h"
#include "statistics.hh"
#include "Utils/helpers.hh"
#include "dialog.hh"

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
#include <algorithm>

using namespace CourseSide;
using namespace Interface;
using namespace Model;

/**
 * @file mainwindow.h : define game mainwindow.
 */

namespace Ui {
  class MainWindow;
}

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
    /**
   * @brief MainWindow constructor
   * @param parent
   * @post : Mainwindow is not in removed state by default.
   */
  explicit MainWindow(QWidget *parent = 0);

  ~MainWindow();
    /**
   * @brief startGame
   * @post : game is running. Exception guarantee: basics
   * @exception: game is once start if the memory is available, or throw std::bad_alloc.
   */
  void startGame();
signals:
  /**
   * @brief SIGNAL keyPressed - emit key has been pressed by user
   * @param key
   * @pre : if a key is pressed.
   */
  void keyPressed(int key);
private slots:
  /**
   * @brief SLOT onBallCollided - display the pokemon has been catched.
   * @param pokemon
   * @pre : the player is move to the pokemon ball position.
   * @post exception guarantee: basics
   * @exception: if there is no memory available, this might throw exception std::bad_alloc.
   */
  void onBallCollided(Pokemon pokemon);

  /**
   * @brief openBag to display pokemon
   * @pre -
   * @post exception guarantee: basics
   * @exception: if there is no memory available, this might throw exception std::bad_alloc.
   */
  void openBag();

  /**
   * @brief SLOT updateFuelBar in mainwindow
   * @param fuel
   * @pre - the fuel changed, fuel >= 0
   * @post exception guarantee: no throw
   */
  void updateFuelBar(int fuel);

  /**
   * @brief SLOT actorCountChanged - number of actors changed
   * @param actor
   * @param delta - number of actor has changed.
   * @post exception guarantee: no throw
   */
  void actorCountChanged(std::shared_ptr<IActor> actor, int delta);

  /**
   * @brief SLOT onGameOver - display final score.
   * @pre : game is over
   * @post exception guarantee : basics
   * @exception: if there is no memory available, this might throw exception std::bad_alloc.
   */
  void onGameOver();

  /**
   * @brief SLOT openLeaderBoard - open top 10 leaderboard.
   * @pre -
   * @post exception guarantee : basics
   * @exception: if there is no memory available, this might throw exception std::bad_alloc.
   */
  void openLeaderboard();
private:
  // keyPressEvent override
  void keyPressEvent(QKeyEvent *event) override;

  Ui::MainWindow *ui;
  Logic* logic_;
  std::shared_ptr<City> city_;
  QProgressBar* fuelBar_;
  Stats::Statistics stats_;
  int width_ = 1095;
  int height_ = 592;
  int tick_ = 500;
  const int LEADER_BOARD_SIZE = 10;
  Utils::GameSetting gameSetting_;
  bool isStarted;
};

#endif // MAINWINDOW_HH
