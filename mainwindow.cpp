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


void MainWindow::accept(){
  QString input_file = field("input_file_path").toString();
  QString output_file = field("save_file_path").toString();
  QString password = field("password").toString();
  std::string input_file_str = input_file.toStdString();
  std::string output_file_str = output_file.toStdString();
  std::string password_str = password.toStdString();

  int ret = DES_Encrypt(input_file_str.c_str(), password_str.c_str(),
              output_file_str.c_str());

  if(ret == 1){//OK
    QMessageBox::information(this, "info", "file encrypted!");
    }
  else if(ret == -1){//input file error
      QMessageBox::critical(this, "error", "cannot read input file!");
    }
  else if(ret == -3){//output file error
      QMessageBox::critical(this, "error", "cannot write to output file!");
    }
}


