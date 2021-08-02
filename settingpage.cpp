#include <QtGlobal>

#include "settingpage.h"
#include "ui_settingpage.h"

SettingPage::SettingPage(QWidget *parent) :
    QDialog(parent), ui(new Ui::SettingPage){
    ui->setupUi(this);
    readSetting();
    connect(ui->checkEnv,&QAbstractButton::pressed,this,&SettingPage::checkEnv);
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&SettingPage::saveSetting);
    connect(ui->pathChose,&QAbstractButton::pressed,this,&SettingPage::pathChose);
}

void SettingPage::pathChose(){
    ui->pathCmd->setText(QFileDialog::getOpenFileName(this));
}

void SettingPage::checkEnv(){
#ifdef Q_OS_WIN
    system("start cmd /c checkenv.bat");
#endif
#ifdef Q_OS_LINUX
    system("gnome-terminal -- bash checkenv.sh");
#endif
}

void SettingPage::readSetting(){
    configFile.setFileName("config.json");
    configFile.open(QIODevice::ReadOnly);
    configOb = QJsonDocument::fromJson(configFile.readAll()).object();
    configFile.close();
}

void SettingPage::saveSetting(){
    QJsonObject config;
    int lang = ui->langChose->currentIndex();
    if (configOb["language"]==lang){

    } else {

        switch (lang){
            case 1: ;
            case 2: configOb["language"] = "lang_zhcn.qm";
        }
    }
    configFile.open(QIODevice::WriteOnly);
    configFile.write(QJsonDocument(configOb).toJson());
    configFile.close();
}

SettingPage::~SettingPage(){
    delete ui;
}
