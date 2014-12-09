#include "ffunction.h"
#include "ui_F_Function.h"
#include <QtWebKitWidgets/QWebView>
#include <QUrl>

FFunction::FFunction(QWidget *parent)
  :QWizardPage(parent), ui(new Ui::F_Function)
{
  ui -> setupUi(this);
  ui -> webView -> load(QUrl("http://en.wikipedia.org/wiki/Data_Encryption_Standard"));

  ui -> title -> setText("<h1>3. F function</h1>");
  ui -> description -> setText("F function is the most important part in "
                               "DES, SBox provides confusion and Permutation "
                               "box provides diffusion, choose the one you "
                               "want to enable:");
  ui -> description -> setWordWrap(true);

  registerField("check_sbox", ui -> check_sbox);
  registerField("check_permutation", ui -> check_permutarion);
}

FFunction::~FFunction(){
  delete ui;
}
