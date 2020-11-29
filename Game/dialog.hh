#ifndef DIALOG_HH
#define DIALOG_HH

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
struct GameSetting
{
    int hour_;
    int min_;
    int numberOfBall_;
    int fuel_;
    int speed_;
};

class Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = nullptr);
  ~Dialog();
signals:
    void gameSettingChanged(GameSetting setting);
public slots:
  void onOpenSetting();
private:
  Ui::Dialog *ui;
  QPushButton* settingButton;
};

#endif // DIALOG_HH
