#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWizard>



class MainWindow : public QWizard
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  void accept();

};



#endif // MAINWINDOW_H
