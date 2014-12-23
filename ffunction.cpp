#include "ffunction.h"
#include "ui_F_Function.h"
//#include <QtWebKitWidgets/QWebView>
//#include <QUrl>

FFunction::FFunction(QWidget *parent)
  :QWizardPage(parent), ui(new Ui::F_Function)
{
  ui -> setupUi(this);
//  ui -> webView -> load(QUrl("http://en.wikipedia.org/wiki/Data_Encryption_Standard"));

  ui -> title -> setText("<h1>3. Select cipher component</h1>");
  ui -> description -> setText("Select components used in cipher:");
  ui -> description -> setWordWrap(true);
  //set number of rounds
  for(int i = 0; i <= 16; i++){
      ui -> num_rounds -> addItem(QString::number(i));
    }
  ui -> num_rounds -> setCurrentIndex(0);

  //set sbox value
  for(int i = 1; i <= 8; i++){
      ui -> S1 -> addItem("S" + QString::number(i));
      ui -> S2 -> addItem("S" + QString::number(i));
      ui -> S3 -> addItem("S" + QString::number(i));
      ui -> S4 -> addItem("S" + QString::number(i));
      ui -> S5 -> addItem("S" + QString::number(i));
      ui -> S6 -> addItem("S" + QString::number(i));
      ui -> S7 -> addItem("S" + QString::number(i));
      ui -> S8 -> addItem("S" + QString::number(i));
    }

  registerField("check_swap", ui -> check_swap);
  registerField("check_IP", ui -> check_IP);
  registerField("check_inverse_IP", ui -> check_inverse_IP);
  registerField("check_permutation", ui -> check_permutarion);
  registerField("num_rounds", ui -> num_rounds);
  registerField("S1", ui -> S1);
  registerField("S2", ui -> S2);
  registerField("S3", ui -> S3);
  registerField("S4", ui -> S4);
  registerField("S5", ui -> S5);
  registerField("S6", ui -> S6);
  registerField("S7", ui -> S7);
  registerField("S8", ui -> S8);
}

FFunction::~FFunction(){
  delete ui;
}
