#include "mainwindow.hh"
#include "ui_mainwindow.h"

const qreal PADDING = 10;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  logic_(new Logic(this))
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
//    connect(ui->resumeBtn, &QPushButton::clicked, logic_, &AdvancedLogic::resumeGame);
//    connect(ui->pauseBtn, &QPushButton::clicked, logic_, &AdvancedLogic::pauseGame);

    startGame();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::startGame()
{
  // GAME START FROM HERE --- NEED NEW FUNCTION gameStart
    city_ = std::make_shared<City>(this);
    logic_->takeCity(city_);
    logic_->setTime(9, 20);
    logic_->fileConfig();

    // setScene for Graphic view
    city_->getMap()->setSceneRect(0, 0, width_, height_);
    ui->gameView->setSceneRect(0, 0, 1092, 590);
    ui->gameView->setScene(city_->getMap());

    //connect keys
    connect(this, &MainWindow::keyPressed, city_.get(), Model::HANDLEFUNCT);

    logic_->finalizeGameStart();
}

void MainWindow::onStartButtonClicked()
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
  // LOOK BACK IF THE GAME NEED TO BE STARTED OR NOT.
  emit keyPressed( static_cast<int>(event->key()));
}
