#ifndef GETPASSWORD_H
#define GETPASSWORD_H
#include <QWizard>

namespace Ui {
  class GetPassword;
}

class GetPassword : public QWizardPage
{
  Q_OBJECT
public:
  explicit GetPassword(QWidget* parent = 0);
  ~GetPassword();
  bool isComplete() const;

private slots:
  void check_length();

private:
  Ui::GetPassword* ui;
  bool is_length_enough;
};

#endif // GETPASSWORD_H
