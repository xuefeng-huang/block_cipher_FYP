#include "mainwindow.h"
#include "intropage.h"
#include "getpassword.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
  QWizard(parent)
{
  addPage(new IntroPage);
  addPage(new GetPassword);

  setWindowTitle("Blockcipher playground");
}


void MainWindow::accept(){

}


