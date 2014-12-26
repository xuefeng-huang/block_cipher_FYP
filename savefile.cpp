#include "savefile.h"
#include "ui_savefile.h"
#include "DES.h"
#include <QFileDialog>
#include <QMessageBox>

SaveFile::SaveFile(QWidget *parent) :
  QWizardPage(parent),
  ui(new Ui::SaveFile)
{
  ui->setupUi(this);

  ui -> title -> setText("<h1>4. Encrypt and decrypt file</h1>");
  ui -> description -> setText("Choose a location to save your file:"
                               "<p>Note: A setting file will be saved with the cipher "
                               "text, it is recommended to save them into "
                               "a <b>new folder</b></p>");
  ui -> description -> setWordWrap(true);

  connect(ui -> choose_button, SIGNAL(clicked()), this, SLOT(save_file()));
  connect(ui ->choose_decrypt, SIGNAL(clicked()), this, SLOT(save_decrypt_file()));
  connect(ui ->decrypt_button, SIGNAL(clicked()), this, SLOT(decrypt()));

  registerField("save_file_path*", ui -> save_file_path);
  registerField("plain_file_path", ui ->decrypt_file_path);
}

SaveFile::~SaveFile()
{
  delete ui;
}

void SaveFile::save_file(){
  QString file_path = QFileDialog::getSaveFileName(this, "save");

  if(!file_path.isEmpty()){
      ui -> save_file_path -> setText(file_path);
    }
}

void SaveFile::save_decrypt_file(){
  QString file_path = QFileDialog::getSaveFileName(this, "save");

  if(!file_path.isEmpty()){
      ui -> decrypt_file_path -> setText(file_path);
    }
}

void SaveFile::get_selection(component_selection *user_choice){
  if(field("check_IP").toBool()){
      user_choice ->IP = true;
    }
  else{
      user_choice ->IP = false;
    }

  if(field("check_swap").toBool()){
      user_choice ->feistel_swap = true;
    }
  else {
      user_choice ->feistel_swap = false;
    }

  if(field("check_permutation").toBool()){
      user_choice ->permutation_internal = true;
    }
  else {
      user_choice ->permutation_internal = false;
    }

  if(field("check_inverse_IP").toBool()){
      user_choice ->inverse_permutation = true;
    }
  else {
      user_choice ->inverse_permutation = false;
    }

  //set number of rounds
  user_choice ->num_of_rounds = field("num_rounds").toInt();

  //set sbox array
  QString s;
  for(int i = 0; i < 8; i++){
      s = "S" + QString::number(i + 1);
      user_choice ->sbox[i] = field(s).toInt();
    }
}

void SaveFile::decrypt(){
  component_selection user_choice;
  get_selection(&user_choice);

  QString input_file = field("save_file_path").toString();
  QString output_file = field("plain_file_path").toString();
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
