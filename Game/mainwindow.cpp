#include "mainwindow.hh"
#include "ui_mainwindow.h"

const qreal PADDING = 10;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  logic_(new Logic(this)),
  isStarted(false)
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


}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::startGame()
{
    if (isStarted)
    {
        return;
    }
    isStarted = true;
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
    fuelBar_ = new QProgressBar(this);
    fuelBar_->move(PADDING,600);
    fuelBar_->setMaximum(MAXIMUM_FUEL);
    fuelBar_->setFixedHeight(20);
    fuelBar_->setFixedWidth(width_-PADDING);
    fuelBar_->setFormat("Fuel: %p%");
    fuelBar_->setValue(MAXIMUM_FUEL);
    QPalette p = fuelBar_->palette();
    p.setColor(QPalette::Highlight, QColor(0,128,0));
    fuelBar_->setPalette(p);
    fuelBar_->show();

    logic_->finalizeGameStart();
}

void MainWindow::onStartButtonClicked()
{
    startGame();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
  // LOOK BACK IF THE GAME NEED TO BE STARTED OR NOT.
  emit keyPressed( static_cast<int>(event->key()));
}
