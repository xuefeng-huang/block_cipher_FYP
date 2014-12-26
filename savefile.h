#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QWizardPage>
#include "DES.h"

namespace Ui {
  class SaveFile;
}

class SaveFile : public QWizardPage
{
  Q_OBJECT

public:
  explicit SaveFile(QWidget *parent = 0);
  ~SaveFile();

private slots:
  void save_file();
  void save_decrypt_file();
  void decrypt();

private:
  Ui::SaveFile *ui;
  void get_selection(component_selection* user_choice);
};

#endif // SAVEFILE_H
