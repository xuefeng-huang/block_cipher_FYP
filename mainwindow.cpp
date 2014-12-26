#include "mainwindow.h"
#include "intropage.h"
#include "getpassword.h"
#include "ffunction.h"
#include "savefile.h"
#include "DES.h"
#include <QtGui>
#include <QMessageBox>
//#include <QString>

MainWindow::MainWindow(QWidget *parent) :
  QWizard(parent)
{
  addPage(new IntroPage);
  addPage(new GetPassword);
  addPage(new FFunction);
  addPage(new SaveFile);

  setButtonText(QWizard::CancelButton, "Close");
  setButtonText(QWizard::FinishButton, "Encrypt");
  setWindowTitle("Blockcipher playground");
}

void MainWindow::get_selection(component_selection* user_choice){

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

void MainWindow::accept(){
  component_selection user_choice;

  QString input_file = field("input_file_path").toString();
  QString output_file = field("save_file_path").toString();
  QString password = field("password").toString();
  std::string input_file_str = input_file.toStdString();
  std::string output_file_str = output_file.toStdString();
  std::string password_str = password.toStdString();

  get_selection(&user_choice);

  int ret = DES_Encrypt(input_file_str.c_str(), password_str.c_str(),
              output_file_str.c_str(), &user_choice);

  if(ret == 1){//OK
    QMessageBox::information(this, "info", "file encrypted!");
    }
  else if(ret == -1){//input file error
      QMessageBox::critical(this, "error", "cannot read input file!");
    }
  else if(ret == -3){//output file error
      QMessageBox::critical(this, "error", "cannot write to output file!");
    }

  //save setting file
  QFile setting_file(output_file + "_setting.txt");

  if (!setting_file.open(QIODevice::WriteOnly | QIODevice::Text)){
    QMessageBox::critical(this, "error", "cannot write to setting file!");
    return;
    }

  QTextStream out(&setting_file);
  if(user_choice.IP)
    out << "Initial permutation: true\n";
  else
    out << "Initial permutation: false\n";

  if(user_choice.feistel_swap)
    out << "Feistel swap: true\n";
  else
    out << "Feistel swap: false\n";

  if(user_choice.permutation_internal)
    out << "Permutation after substitution: true\n";
  else
    out << "Permutation after substitution: false\n";

  if(user_choice.inverse_permutation)
    out << "Inverse permutation: true\n";
  else
    out << "Inverse permutation: false\n";

  out << "rounds of operation: " << user_choice.num_of_rounds << "\n";
  out << "selection of 8 Sboxes:\n";

  for(int i = 0; i < 8; i++){
      out << (i + 1) << " ";
      switch (user_choice.sbox[i]) {
        case 0:
          out << "S1\n";
          break;
        case 1:
          out << "S2\n";
          break;
        case 2:
          out << "S3\n";
          break;
        case 3:
          out << "S4\n";
          break;
        case 4:
          out << "S5\n";
          break;
        case 5:
          out << "S6\n";
          break;
        case 6:
          out << "S7\n";
          break;
        case 7:
          out << "S8\n";
          break;

        }
    }

  setting_file.close();
}


