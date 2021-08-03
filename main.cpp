#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QTranslator>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "mainwindow.h"

int main(int argc, char *argv[]){
    Q_INIT_RESOURCE(image);

    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("Manim Studio Group");
    QCoreApplication::setApplicationName("Manim Studio");
    QCoreApplication::setApplicationVersion("0.1.0");
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(app);

    QFile configFile("config.json");
    configFile.open(QIODevice::ReadOnly);
    QJsonObject configOb = QJsonDocument::fromJson(configFile.readAll()).object();
    configFile.close();
    QString langCon = configOb.value("languagefile").toString();
    QTranslator trans;
    if(trans.load(langCon))
        QCoreApplication::installTranslator(&trans);

    MainWindow mainWin;
    mainWin.configOb = &configOb;
    if (!parser.positionalArguments().isEmpty())
        mainWin.loadFile(parser.positionalArguments().first());
    mainWin.show();
    return QCoreApplication::exec();
}
