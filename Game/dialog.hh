#ifndef DIALOG_HH
#define DIALOG_HH

#include <QDialog>
#include <QString>
#include <QFile>
#include <QTextBlock>
namespace Ui {
  class Dialog;
}

class Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = nullptr);
  ~Dialog();

private:
  Ui::Dialog *ui;
};

#endif // DIALOG_HH
