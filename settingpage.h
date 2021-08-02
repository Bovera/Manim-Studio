#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include <QDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <cstdlib>
#include <QFileDialog>

namespace Ui {
class SettingPage;
}

class SettingPage : public QDialog
{
    Q_OBJECT

public:
    explicit SettingPage(QWidget *parent = nullptr);
    ~SettingPage();

public slots:
    void checkEnv();
    void saveSetting();
    void pathChose();

private:
    void readSetting();
    Ui::SettingPage *ui;
    QJsonObject configOb;
    QFile configFile;
};

#endif // SETTINGPAGE_H
