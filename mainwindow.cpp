#include "mainwindow.h"
#include "intropage.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
  QWizard(parent)
{
  addPage(new IntroPage);

  setWindowTitle("Choose a file");
}


void MainWindow::accept(){

}


