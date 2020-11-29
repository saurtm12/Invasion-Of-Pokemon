#ifndef DIALOG_HH
#define DIALOG_HH

#include "Utils/helpers.hh"
#include <QDialog>
#include <QString>
#include <QFile>
#include <QTextBlock>
#include <QPushButton>
#include <QLabel>
#include <QTimeEdit>
#include <QSpinBox>
#include <qdebug.h>
namespace Ui {
  class Dialog;
}

class Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = nullptr);
  ~Dialog();
signals:
    void gameSettingChanged(Utils::GameSetting setting);
public slots:
  void onOpenSetting();
private:
  Ui::Dialog *ui;
  QPushButton* settingButton;
};

#endif // DIALOG_HH
