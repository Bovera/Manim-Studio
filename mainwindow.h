#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include <QUrl>

#include "highlighter.h"
#include "settingpage.h"
#include "texedit.h"
#include "makepage.h"

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
    QJsonObject* configOb;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    bool saveAs();
    void documentWasModified();
#ifndef QT_NO_SESSIONMANAGER
    void commitData(QSessionManager &);
#endif
    // for manim
    void texedit();

private:
    void createActions();
    bool maybeSave();
    bool save(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    QString lang;
    QString curFile;
    QPlainTextEdit *textEdit;
};

#endif // MAINWINDOW_H
