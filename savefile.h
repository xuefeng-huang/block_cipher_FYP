#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QWizardPage>

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

private:
  Ui::SaveFile *ui;
};

#endif // SAVEFILE_H
