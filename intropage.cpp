#include "intropage.h"
#include "ui_IntroPage.h"
#include "DES.h"
#include <QFileDialog>
#include <QMessageBox>

IntroPage::IntroPage(QWidget *parent)
  : QWizardPage(parent), ui(new Ui::IntroPage)
{
  ui -> setupUi(this);

  //setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark1.png"));

  ui -> title -> setText("<h1>1. Intro</h1>");
  ui -> description -> setText("Follow steps to pick cipher components "
                               "and generate a corresponding ciphertext. "
                               "First, choose a file to encrypt ");
  ui -> description -> setWordWrap(true);

  connect(ui ->choose_cipher, SIGNAL(clicked()), this, SLOT(save_cipher_file()));
  connect(ui ->choose_decrypt, SIGNAL(clicked()), this, SLOT(save_decrypt_file()));
  connect(ui ->decrypt_button, SIGNAL(clicked()), this, SLOT(decrypt()));

  registerField("input_file_path*", ui -> file_path);

}

IntroPage::~IntroPage(){
  delete ui;
}



void IntroPage::on_file_button_clicked()
{
  QString file_path = QFileDialog::getOpenFileName(this,"select a file");

  if(!file_path.isEmpty()){
      ui -> file_path -> setText(file_path);
    }
}

void IntroPage::save_decrypt_file(){
  QString file_path = QFileDialog::getSaveFileName(this, "save");

  if(!file_path.isEmpty()){
      ui -> decrypt_file_path -> setText(file_path);
    }
}

void IntroPage::save_cipher_file(){
  QString file_path = QFileDialog::getOpenFileName(this, "select a file");

  if(!file_path.isEmpty()){
      ui -> cipher_file_path -> setText(file_path);
    }
}

void IntroPage::decrypt(){
  component_selection user_choice;

  QString input_file = ui ->cipher_file_path->text();
  QString output_file = ui ->decrypt_file_path ->text();
  QString password = field("password").toString();
  std::string input_file_str = input_file.toStdString();
  std::string output_file_str = output_file.toStdString();
  std::string password_str = password.toStdString();

  int ret = DES_Decrypt(input_file_str.c_str(), password_str.c_str(),
                        output_file_str.c_str(), &user_choice);

  if(ret == 1){//OK
    QMessageBox::information(this, "info", "file decrypted!");
    }
  else if(ret == -3){//cipher file error
      QMessageBox::critical(this, "error", "cannot read cipher file!");
    }
  else if(ret == -1){//plain file error
      QMessageBox::critical(this, "error", "cannot write to plain file!");
    }
}
