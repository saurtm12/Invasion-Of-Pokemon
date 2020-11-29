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
}

Dialog::~Dialog()
{
  delete ui;
}
