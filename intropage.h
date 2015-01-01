#ifndef INTROPAGE_H
#define INTROPAGE_H
#include <QWizard>


namespace Ui {
  class IntroPage;
}

class IntroPage : public QWizardPage
{
  Q_OBJECT

public:
  explicit IntroPage(QWidget *parent = 0);
  ~IntroPage();

private slots:
  void on_file_button_clicked();
  void save_cipher_file();
  void save_decrypt_file();
  void decrypt();

private:
  Ui::IntroPage* ui;

};

#endif // INTROPAGE_H
