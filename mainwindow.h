#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "highlighter.h"
#include "settingpage.h"
#include "texedit.h"
#include "tutorialpage.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QPlainTextEdit;
class QSessionManager;
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void loadFile(const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void newFile();
    void open();
    bool saveAs();
    void documentWasModified();
#ifndef QT_NO_SESSIONMANAGER
    void commitData(QSessionManager &);
#endif
    // for manim
    void make();
    void debug();
    void initialize();
    void texedit();

private:
    void createActions();
    bool maybeSave();
    bool save(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    QString lang;
    QString curFile;

    // assembly of mainwindow
    QPlainTextEdit *textEdit;
    TexEdit *texEdit;
    TutorialPage *tutorialpage;
    Highlighter *highmy;
    SettingPage *page;
};

#endif // MAINWINDOW_H
