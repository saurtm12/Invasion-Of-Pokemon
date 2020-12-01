#include "mainwindow.hh"
#include "ui_mainwindow.h"

const qreal PADDING = 85;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  isStarted(false)
{
    //default game setting.
    gameSetting_ = {9, 0, 5, 3000, 1, "No"};
    // add first dialog
    Dialog *dialog = new Dialog(this);
    connect(dialog, &Dialog::gameSettingChanged, [&](Utils::GameSetting gameSetting){
        this->gameSetting_ = gameSetting;
    });
    connect(dialog, &Dialog::rejected, [&](){ close();});
    dialog->move(300,20);
    dialog->show();

    // setup window
    ui->setupUi(this);
    this->setWindowTitle("NYSEE");
    this->setFixedSize(1368, 700);
    ui->gameView->setFixedSize(width_, height_);
    ui->centralwidget->setFixedSize(1368, 700);

    ui->startButton->move(width_+ PADDING, PADDING);
    ui->bagBtn->move(width_+ PADDING, 300);
    ui->boardBtn->move(width_ + PADDING, 400);

    ui->busLabel->move(width_ + 30, 152);
    ui->passengerLabel->move(width_ + 30, 192);
    ui->scoreLabel->move(width_ + 30, 232);
    ui->busText->move(width_ + 175, 150);
    ui->busText->setReadOnly(true);
    ui->passengerText->move(width_ + 175, 190);
    ui->passengerText->setReadOnly(true);
    ui->scoreText->move(width_ + 175, 230);
    ui->scoreText->setReadOnly(true);

    // connect start game
    connect(ui->startButton, &QPushButton::clicked, [&](){startGame();});
    connect(ui->boardBtn, &QPushButton::clicked, this, &MainWindow::openLeaderboard);
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
    logic_->setTime(gameSetting_.hour_, gameSetting_.min_);
    logic_->fileConfig();

    // setScene for Graphic view
    city_->getMap()->setSceneRect(0, 0, width_, height_);
    ui->gameView->setSceneRect(0, 0, 1092, 590);
    ui->gameView->setScene(city_->getMap());

    fuelBar_ = new QProgressBar(this);
    fuelBar_->move(PADDING,600);
    fuelBar_->setFixedHeight(20);
    fuelBar_->setFixedWidth(width_-PADDING);
    fuelBar_->setFormat("Fuel: %p%");
    if (gameSetting_.multiplayer_ == "Yes") {
        fuelBar_->setMaximum(2 * gameSetting_.fuel_);
        fuelBar_->setValue(2 * gameSetting_.fuel_);
    } else {
        fuelBar_->setMaximum(gameSetting_.fuel_);
        fuelBar_->setValue(gameSetting_.fuel_);
    }
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


void MainWindow::onBallCollided(Pokemon pokemon)
{
    int newScores = stats_.addScores(pokemon.score());
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
    auto highScores = Utils::getHighScores();
    highScores.push_back(stats_.getScores());
    std::sort(highScores.rbegin(), highScores.rend());
    while (highScores.size() > 10)
    {
        highScores.pop_back();
    }
    Utils::writeScore(highScores);

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

    openLeaderboard();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (isStarted) {
        emit keyPressed( static_cast<int>(event->key()) );
    }
}

void MainWindow::openLeaderboard()
{
    auto highScores = Utils::getHighScores();
    QDialog* displayResult = new QDialog(this);
    if (!isStarted) {
        displayResult->setWindowTitle("Gameover!");
    } else {
        displayResult->setWindowTitle("Leaderboard");
    }
    QLabel* text = new QLabel(displayResult);
    QString content = QString("Your Score is: ") + QString::number(stats_.getScores());
    text->setText(content);
    text->move(10,10);

    QLabel* highScoreText = new QLabel(displayResult);
    highScoreText->setText("High Scores:");
    highScoreText->move(10,30);
    int space = 30;
    int currentLine = 60;
    for (unsigned int i = 0; i < highScores.size(); ++i)
    {
        QLabel* scoreLabel = new QLabel(displayResult);
        scoreLabel->setText(QString::number(i + 1) + ". " + QString::number(highScores[i]));
        if (!isStarted && highScores[i] == stats_.getScores()) {
            scoreLabel->setStyleSheet("font-weight: bold;");
        }
        scoreLabel->move(10, currentLine);
        currentLine += space;
    }

    if (!isStarted) {
        QLabel* instruction = new QLabel(displayResult);
        instruction->setText("Press start to restart");
        instruction->move(10, currentLine);
    }
    QPushButton* confirm = new QPushButton("OK", displayResult);
    confirm->move(80, currentLine + space);
    connect(confirm, &QPushButton::clicked, displayResult, &QDialog::accept);

    displayResult->setFixedSize(250, currentLine + 2*space);
    displayResult->exec();
}
