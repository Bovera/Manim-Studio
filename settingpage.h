#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include <QDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <cstdlib>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class SettingPage;
}

class SettingPage : public QDialog
{
    Q_OBJECT

public:
    explicit SettingPage(QWidget *parent = nullptr);
    ~SettingPage();

private slots:
    void checkEnv();
    void saveSetting();

private:
    Ui::SettingPage *ui;
    QJsonObject configOb;
    QFile configFile;
    QFile manimConfig;
};

#endif // SETTINGPAGE_H
