#include "intropage.h"
#include "ui_IntroPage.h"
#include <QFileDialog>

IntroPage::IntroPage(QWidget *parent)
  : QWizardPage(parent), ui(new Ui::IntroPage)
{
  ui -> setupUi(this);

  //setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark1.png"));

  ui -> title -> setText("<h1>1. Intro</h1>");
  ui -> description -> setText("Follow steps to customize DES parametres "
                               "and generate a corresponding ciphertext. "
                               "First, choose a file to encrypt ");
  ui -> description -> setWordWrap(true);

  registerField("file_path*", ui -> file_path);

}

IntroPage::~IntroPage(){
  delete ui;
}



void IntroPage::on_file_button_clicked()
{
  QString file_path = QFileDialog::getOpenFileName(this,"select a file");

  if(!file_path.isEmpty()){
      ui -> file_path -> setText(file_path);
    }
}
