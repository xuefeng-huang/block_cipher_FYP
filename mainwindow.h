#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWizard>
#include "DES.h"



class MainWindow : public QWizard
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  void accept();

private:
  void get_selection(component_selection* user_choice);
  void save_binary(component_selection& user_choice);

};



#endif // MAINWINDOW_H
