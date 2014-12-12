#include "savefile.h"
#include "ui_savefile.h"
#include <QFileDialog>

SaveFile::SaveFile(QWidget *parent) :
  QWizardPage(parent),
  ui(new Ui::SaveFile)
{
  ui->setupUi(this);

  ui -> title -> setText("<h1>4. Save file");
  ui -> description -> setText("Choose a location to save your file:");
  ui -> description -> setWordWrap(true);

  connect(ui -> choose_button, SIGNAL(clicked()), this, SLOT(save_file()));

  registerField("save_file_path*", ui -> save_file_path);
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
