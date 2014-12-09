#include "mainwindow.h"
#include "intropage.h"
#include "getpassword.h"
#include "ffunction.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
  QWizard(parent)
{
  addPage(new IntroPage);
  addPage(new GetPassword);
  addPage(new FFunction);

  setWindowTitle("Blockcipher playground");
}


void MainWindow::accept(){

}


