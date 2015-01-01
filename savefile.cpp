#include "savefile.h"
#include "ui_savefile.h"
#include <QFileDialog>
#include <QMessageBox>

SaveFile::SaveFile(QWidget *parent) :
  QWizardPage(parent),
  ui(new Ui::SaveFile)
{
  ui->setupUi(this);

  ui -> title -> setText("<h1>4. Encrypt and decrypt file</h1>");
  ui -> description -> setText("Choose a location to save your file:<br />"
                               "Note: A setting file will be saved with the cipher "
                               "text, it is recommended to save them into "
                               "a <b>new folder</b><br><br>");
  ui -> description -> setWordWrap(true);

  connect(ui -> choose_button, SIGNAL(clicked()), this, SLOT(save_file()));

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
