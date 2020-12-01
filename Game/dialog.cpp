#include "dialog.hh"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  ui->setupUi(this);
  this->setFixedSize(500,500);

  QString filecontent;
  QString path = ":/intro/Text/intro.txt";
  QFile file;
  file.setFileName(path);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  filecontent = file.readAll();
  file.close();
  ui->textBrowser->setText(filecontent);
  settingButton = new QPushButton("Game setting",this);
  settingButton->move(10,450);
  connect(settingButton, &QPushButton::clicked, this, &Dialog::onOpenSetting);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onOpenSetting()
{
    QDialog* settingDialog = new QDialog(this);
    settingDialog->setFixedSize(500,500);
    settingDialog->setWindowTitle("Setting");
    QLabel* startTime = new QLabel("Start time:", settingDialog);
    startTime->move(10,10);
    auto font = startTime->font();
    font.setPointSize(14);
    startTime->setFont(font);
    QTimeEdit* timeEdit = new QTimeEdit(settingDialog);
    timeEdit->move(300,10);
    timeEdit->setTime(QTime(9,0,0,0));

    QLabel* numerOfBall = new QLabel("Number of Pokemon Ball:", settingDialog);
    numerOfBall->move(10,50);
    font = numerOfBall->font();
    font.setPointSize(14);
    numerOfBall->setFont(font);
    QSpinBox* noBallSpin = new QSpinBox(settingDialog);
    noBallSpin->move(300,50);
    noBallSpin->setValue(5);
    noBallSpin->setMaximum(100);

    QLabel* fuel = new QLabel("Fuel:", settingDialog);
    fuel->move(10,90);
    font = fuel->font();
    font.setPointSize(14);
    fuel->setFont(font);
    QSpinBox* fuelSpin = new QSpinBox(settingDialog);
    fuelSpin->move(300,90);
    fuelSpin->setMaximum(10000);
    fuelSpin->setValue(3000);

    QLabel* playerSpeed = new QLabel("Speed:", settingDialog);
    playerSpeed->move(10,130);
    font = fuel->font();
    font.setPointSize(14);
    playerSpeed->setFont(font);
    QSpinBox* speedSpin = new QSpinBox(settingDialog);
    speedSpin->move(300,130);
    speedSpin->setMaximum(10);
    speedSpin->setValue(1);

    QLabel* multiplayer = new QLabel("Mutliplayer:", settingDialog);
    multiplayer->move(10,170);
    font = fuel->font();
    font.setPointSize(14);
    multiplayer->setFont(font);
    QComboBox* multiplayerDropdown = new QComboBox(settingDialog);
    multiplayerDropdown->move(300,170);
    multiplayerDropdown->addItem("Yes");
    multiplayerDropdown->addItem("No");

    QPushButton* confirm = new QPushButton("OK", settingDialog);
    confirm->move(10,220);
    connect(confirm, &QPushButton::clicked, [=, &settingDialog](){
        emit gameSettingChanged({  timeEdit->time().hour(),
                                   timeEdit->time().minute(),
                                   noBallSpin->value(),
                                   fuelSpin->value(),
                                   speedSpin->value(),
                                   multiplayerDropdown->currentText()
                                });
    });
    connect(confirm, &QPushButton::clicked, settingDialog, &QDialog::accept);
    settingDialog->show();
}
