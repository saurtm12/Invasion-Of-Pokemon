#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH
#include <dialog.hh>

#include <QMainWindow>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>
#include <memory>
#include <QVector>
#include <map>

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
  // ActorItem last_;

  int width_ = 500;
  int height_ = 500;
  int tick_ = 500;
};

#endif // MAINWINDOW_HH
