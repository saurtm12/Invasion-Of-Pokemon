#include "mainwindow.hh"
#include "ui_mainwindow.h"

const qreal PADDING = 85;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  isStarted(false)
{
    // add first dialog
    Dialog *dialog = new Dialog(this);
    connect(dialog, &Dialog::gameSettingChanged, [&](Utils::GameSetting gameSetting){
        this->gameSetting_ = gameSetting;
    });
    dialog->exec();

    // setup window
    ui->setupUi(this);
    this->setWindowTitle("NYSEE");
    this->setFixedSize(1368, 700);
    ui->gameView->setFixedSize(width_, height_);
    ui->centralwidget->setFixedSize(1368, 700);

    ui->startButton->move(width_+ PADDING, PADDING);
    ui->bagBtn->move(width_+ PADDING, 300);

    ui->busLabel->move(width_ + 30, 152);
    ui->passengerLabel->move(width_ + 30, 192);
    ui->scoreLabel->move(width_ + 30, 232);
    ui->busText->move(width_ + 175, 150);
    ui->busText->setReadOnly(true);
    ui->passengerText->move(width_ + 175, 190);
    ui->passengerText->setReadOnly(true);
    ui->scoreText->move(width_ + 175, 230);
    ui->scoreText->setReadOnly(true);

//    resize(minimumSizeHint());
//    ui->gameView->fitInView(city->getMap()->sceneRect(), Qt::KeepAspectRatio);

    // connect events
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);
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
    logic_ = new Logic(this);

    // GAME START FROM HERE --- NEED NEW FUNCTION gameStart
    city_ = std::make_shared<City>(gameSetting_, this);
    logic_->takeCity(city_);
    logic_->setTime(9, 20);
    logic_->fileConfig();

    // setScene for Graphic view
    city_->getMap()->setSceneRect(0, 0, width_, height_);
    ui->gameView->setSceneRect(0, 0, 1092, 590);
    ui->gameView->setScene(city_->getMap());

    fuelBar_ = new QProgressBar(this);
    fuelBar_->move(PADDING,600);
    fuelBar_->setMaximum(gameSetting_.fuel_);
    fuelBar_->setFixedHeight(20);
    fuelBar_->setFixedWidth(width_-PADDING);
    fuelBar_->setFormat("Fuel: %p%");
    fuelBar_->setValue(gameSetting_.fuel_);
    QPalette p = fuelBar_->palette();
    p.setColor(QPalette::Highlight, QColor(0,128,0));
    fuelBar_->setPalette(p);
    fuelBar_->show();

    //connect keys
    connect(this, &MainWindow::keyPressed, city_.get(), Model::HANDLEFUNCT);
    connect(city_.get(), &City::collideBall, this, &MainWindow::onBallCollided);
    connect(ui->bagBtn, &QPushButton::clicked, this, &MainWindow::openBag);
    connect(city_.get(), &City::updateFuel, this, &MainWindow::updateFuelBar);
    connect(city_.get(), &City::actorChanged, this, &MainWindow::actorCountChanged);
    connect(city_.get(), &City::gameOver, this, &MainWindow::onGameOver);
    logic_->finalizeGameStart();

    int newBusCount = stats_.getNumberOfBuses();
    ui->busText->setText(QString::number(newBusCount));
    int newPassengerCount = stats_.getNumberOfPassengers();
    ui->passengerText->setText(QString::number(newPassengerCount));

    isStarted = true;
}

void MainWindow::onStartButtonClicked()
{
    startGame();
}

void MainWindow::onBallCollided(Pokemon pokemon)
{
    int newScores = stats_.addScores();
    ui->scoreText->setText(QString::number(newScores));
    QDialog* dialog = pokemon.dialogInfo(this);
    dialog->exec();
}

void MainWindow::openBag()
{
    QDialog* bagDialog = city_->getPlayerBag(this);
    bagDialog->exec();
}

void MainWindow::updateFuelBar(int fuel)
{
    fuelBar_->setValue(fuel);
}

void MainWindow::actorCountChanged(std::shared_ptr<IActor> actor, int delta)
{
    if (typeid(*actor).name() == Utils::NYSSE_TYPE) {
        if (delta == 1) {
            stats_.newNysse();
        } else {
            stats_.nysseRemoved();
        }
        if (!isStarted) return;
        int newBusCount = stats_.getNumberOfBuses();
        ui->busText->setText(QString::number(newBusCount));
    } else if (typeid(*actor).name() == Utils::PASSENGER_TYPE) {
        stats_.morePassengers(delta);
        if (!isStarted) return;
        int newPassengerCount = stats_.getNumberOfPassengers();
        ui->passengerText->setText(QString::number(newPassengerCount));
    }
}

void MainWindow::onGameOver()
{
    delete logic_;
    ui->gameView->setScene(nullptr);
    disconnect(this, &MainWindow::keyPressed, city_.get(), Model::HANDLEFUNCT);
    disconnect(city_.get(), &City::collideBall, this, &MainWindow::onBallCollided);
    disconnect(ui->bagBtn, &QPushButton::clicked, this, &MainWindow::openBag);
    disconnect(city_.get(), &City::updateFuel, this, &MainWindow::updateFuelBar);
    disconnect(city_.get(), &City::gameOver, this, &MainWindow::onGameOver);
    city_ = nullptr;
    delete fuelBar_;
    isStarted = false;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
  // LOOK BACK IF THE GAME NEED TO BE STARTED OR NOT.
  emit keyPressed( static_cast<int>(event->key()));
}
