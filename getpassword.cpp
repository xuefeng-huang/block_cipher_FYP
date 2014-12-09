#include "getpassword.h"
#include "ui_Password.h"

GetPassword::GetPassword(QWidget *parent)
  :QWizardPage(parent), ui(new Ui::GetPassword), is_length_enough(false)
{
  ui -> setupUi(this);

  ui -> title -> setText("<h1>2. Encryption key</h1>");
  ui -> description -> setText("Type your password blow, it is used to "
                                 "encrypt the file you have chosen, it should "
                                 "be at least 8 characters:");
  ui -> description -> setWordWrap(true);

  connect(ui -> password, SIGNAL(textChanged(QString)),
            this, SLOT(check_length()));
}

GetPassword::~GetPassword(){
  delete ui;
}

void GetPassword::check_length(){
  QString password =  ui -> password ->text();
  //check minimal 8 char
  if(password.length() >= 8){
      is_length_enough = true;
      emit completeChanged();
    }
  else{
      is_length_enough = false;
      emit completeChanged();
    }
}

bool GetPassword::isComplete() const{
  return is_length_enough;
}
