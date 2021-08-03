#include <QtGlobal>

#include "settingpage.h"
#include "ui_settingpage.h"

SettingPage::SettingPage(QWidget *parent) :
    QDialog(parent), ui(new Ui::SettingPage){
    configFile.setFileName("config.json");
    configFile.open(QIODevice::ReadOnly);
    configOb = QJsonDocument::fromJson(configFile.readAll()).object();
    configFile.close();

    ui->setupUi(this);

    manimConfig.setFileName(configOb.value("manimlibpath").toString()+"/imports.py");
    if (!manimConfig.open(QIODevice::ReadOnly)){
        ui->tabManim->hide();
        ui->tabWidget->setCurrentIndex(0);
    }

    ui->langChose->setCurrentIndex(configOb.value("language").toInt());
    ui->pathCmd->setText(configOb.value("manimlibpath").toString());
    ui->debugCmd->setText(configOb.value("debugcommand").toString());

    connect(ui->checkEnv,&QAbstractButton::pressed,this,&SettingPage::checkEnv);
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&SettingPage::saveSetting);
    connect(ui->pathChose,&QAbstractButton::pressed,this,[&]{
        ui->pathCmd->setText(QFileDialog::getOpenFileName(this));
    });
}

void SettingPage::checkEnv(){
#ifdef Q_OS_WIN
    system("start cmd /c checkenv.bat");
#endif
#ifdef Q_OS_LINUX
    system("gnome-terminal -- bash checkenv.sh");
#endif
}

void SettingPage::saveSetting(){
    QJsonObject config;
    int lang = ui->langChose->currentIndex();
    if (configOb.value("language").toInt()!=lang){
        QMessageBox::warning(this,tr("Manim Studio Settings"),
                             tr("Language settings changed successfully!\n"
                                "The new settings will take effect after restart."));
    }
    switch (lang){
        case 0: config.insert("language", 0);
                config.insert("languagefile", "none");
        break;
        case 1: config.insert("language", 1);
                config.insert("languagefile", "lang_zhcn.qm");
    }
    config.insert("manimlibpath",ui->pathCmd->text());
    config.insert("debugcommand",ui->debugCmd->text());
    configFile.open(QIODevice::WriteOnly);
    configFile.write(QJsonDocument(config).toJson());
    configFile.close();
}

SettingPage::~SettingPage(){
    delete ui;
}
