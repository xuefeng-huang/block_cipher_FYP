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
  IntroPage(QWidget *parent = 0);
  ~IntroPage();

private slots:
  void on_file_button_clicked();

private:
  Ui::IntroPage* ui;

};

#endif // INTROPAGE_H
