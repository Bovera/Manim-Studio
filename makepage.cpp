#include "makepage.h"
#include "ui_makepage.h"

MakePage::MakePage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MakePage)
{
    ui->setupUi(this);
}

MakePage::~MakePage()
{
    delete ui;
}
