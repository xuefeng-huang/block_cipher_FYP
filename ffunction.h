#ifndef FFUNCTION_H
#define FFUNCTION_H
#include <QWizard>

namespace Ui {
  class F_Function;
}

class FFunction : public QWizardPage
{
  Q_OBJECT
public:
  explicit FFunction(QWidget* parent = 0);
  ~FFunction();

private:
  Ui::F_Function* ui;
};

#endif // FFUNCTION_H
