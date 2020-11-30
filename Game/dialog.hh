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
#include <QComboBox>
#include <qdebug.h>
namespace Ui {
  class Dialog;
}
/**
 * @brief The Dialog class - greeting dialog
 */
class Dialog : public QDialog
{
  Q_OBJECT

public:
    /**
   * @brief Dialog constructor
   * @param parent
   * @post the dialog is not in removed state.
   */
  explicit Dialog(QWidget *parent = nullptr);
  ~Dialog();
signals:
    /**
     * @brief SIGNAL gameSettingChanged
     * @param setting
     */
    void gameSettingChanged(Utils::GameSetting setting);
public slots:
    /**
   * @brief onOpenSetting
   * @pre -
   * @post no throw
   * @exception if memory is not available, the function might leak out std::bad_alloc
   */
  void onOpenSetting();
private:
  Ui::Dialog *ui;
  QPushButton* settingButton;
};

#endif // DIALOG_HH
