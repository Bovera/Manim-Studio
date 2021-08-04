#include <QtWidgets>
#include <QMainWindow>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    textEdit = new QPlainTextEdit;
    setCentralWidget(textEdit);
    createActions();
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 2, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
    connect(textEdit->document(), &QTextDocument::contentsChanged,
            this, &MainWindow::documentWasModified);

#ifndef QT_NO_SESSIONMANAGER
    QGuiApplication::setFallbackSessionManagementEnabled(false);
    connect(qApp, &QGuiApplication::commitDataRequest,
            this, &MainWindow::commitData);
#endif

    setCurrentFile(QString());
    setUnifiedTitleAndToolBarOnMac(true);
    new Highlighter(textEdit->document());
}

void MainWindow::texedit(){
    TexEdit *texEdit = new TexEdit;
    texEdit->contentIn("Haven't connect it to target content!");
    texEdit->show();
    // haven't done
}

void MainWindow::createActions(){
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));

// new
    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    QAction *newAct = new QAction(newIcon, tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, [&]{
        if (maybeSave()) {
            textEdit->clear();
            setCurrentFile(QString());
        }
    });   // I used lambada expression to simplify.
    fileMenu->addAction(newAct);
    fileToolBar->addAction(newAct);

// open
    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    QAction *openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, [&]{
        if (maybeSave()) {
            QString fileName = QFileDialog::getOpenFileName(this);
            if (!fileName.isEmpty())
                loadFile(fileName);
        }
    });
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);

// save
    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
    QAction *saveAct = new QAction(saveIcon, tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, [&]{
            if (curFile.isEmpty()) saveAs();
            else save(curFile);
    });
    fileMenu->addAction(saveAct);
    fileToolBar->addAction(saveAct);

// saveas
    const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
    QAction *saveAsAct = fileMenu->addAction(saveAsIcon, tr("Save &As..."), this, &MainWindow::saveAs);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));

    fileMenu->addSeparator();

// exit
    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit Manim Studio"));

    QToolBar *manimToolBar = new QToolBar(tr("Manim"));
    addToolBar(Qt::LeftToolBarArea,manimToolBar);
    manimToolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);

// init
    const QIcon initIcon = QIcon(":/images/init.png");
    QAction *initAct = fileMenu->addAction(initIcon, tr("&Init"), this, [&]{
        textEdit->clear();
        textEdit->setPlainText("from manimlib.imports import *\n"
                               "\n"
                               "    class default(Scene):\n"
                               "        def construct(self):\n");
    });
    initAct->setStatusTip(tr("Initialize current file"));
    manimToolBar->addAction(initAct);

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    QToolBar *editToolBar = addToolBar(tr("Edit"));

#ifndef QT_NO_CLIPBOARD

// cut
    const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(":/images/cut.png"));
    QAction *cutAct = new QAction(cutIcon, tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
    connect(cutAct, &QAction::triggered, textEdit, &QPlainTextEdit::cut);
    editMenu->addAction(cutAct);
    editToolBar->addAction(cutAct);

// copy
    const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon(":/images/copy.png"));
    QAction *copyAct = new QAction(copyIcon, tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
    connect(copyAct, &QAction::triggered, textEdit, &QPlainTextEdit::copy);
    editMenu->addAction(copyAct);
    editToolBar->addAction(copyAct);

// paste
    const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon(":/images/paste.png"));
    QAction *pasteAct = new QAction(pasteIcon, tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
    connect(pasteAct, &QAction::triggered, textEdit, &QPlainTextEdit::paste);
    editMenu->addAction(pasteAct);
    editToolBar->addAction(pasteAct);

    editMenu->addSeparator();

    QToolBar *manToolBar = addToolBar(tr("Manim"));

// make
    const QIcon makeIcon = QIcon(":/images/make.png");
    QAction *makeAct = new QAction(makeIcon, tr("&Animate"), this);
    makeAct->setStatusTip(tr("Create the animation as final edition"));
    connect(makeAct, &QAction::triggered, this, [&]{
        MakePage *makepage = new MakePage;
        makepage->curFile = curFile;
        makepage->show();
    });
    editMenu->addAction(makeAct);
    manToolBar->addAction(makeAct);

// debug
    const QIcon debugIcon = QIcon(":/images/debug.png");
    QAction *debugAct = new QAction(debugIcon, tr("&Debug"), this);
    debugAct->setStatusTip(tr("Create the animation as test edition"));
    connect(debugAct, &QAction::triggered, this, [&]{
        if (maybeSave()){
            QString commandStd = configOb->value("debugcommand").toString();
            QByteArray command = ((commandStd.replace(commandStd.indexOf("%"),20,curFile)+"default").toLatin1());
            system(command.data()); // translate QString to char*
        }
    });
    editMenu->addAction(debugAct);
    manToolBar->addAction(debugAct);

    menuBar()->addSeparator();

#endif // !QT_NO_CLIPBOARD

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

// about
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, [&]{
        QMessageBox::about(this, tr("About Manim Studio"),
                 tr("<b>Manim Studio</b> is an integrated environment for creating "
                    "animation using Manim. This is the test edition."));
    });
    aboutAct->setStatusTip(tr("Show Manim Studio's About box"));

// tutorial
    QAction *tutorialAct = helpMenu->addAction(tr("&Tutorial"), this, [&]{
        QString url = QCoreApplication::applicationDirPath().left(QCoreApplication::applicationDirPath().lastIndexOf("/"));
        QDesktopServices::openUrl(QUrl(url+QString("/doc/index.html")));
    });
    tutorialAct->setStatusTip(tr("Show Manim tutorial from internet"));

// setting
    menuBar()->addAction(tr("&Settings"),this,[&]{
        SettingPage *page = new SettingPage;
        page->show();
    });

#ifndef QT_NO_CLIPBOARD
    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
    connect(textEdit, &QPlainTextEdit::copyAvailable, cutAct, &QAction::setEnabled);
    connect(textEdit, &QPlainTextEdit::copyAvailable, copyAct, &QAction::setEnabled);
#endif // !QT_NO_CLIPBOARD

    statusBar()->showMessage(tr("Ready"));
}

bool MainWindow::maybeSave(){
    if (!textEdit->document()->isModified())
        return true;
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("Manim Studio"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        if (curFile.isEmpty()) {return saveAs();} else {return save(curFile);}
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

void MainWindow::loadFile(const QString &fileName){
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Manim Studio"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::save(const QString &fileName){
    QString errorMessage;

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << textEdit->toPlainText();
        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2.")
                           .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    } else { errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                       .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }
    QGuiApplication::restoreOverrideCursor();

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr("Manim Studio"), errorMessage);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName){
    curFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.py";
    setWindowFilePath(shownName);
}

QString MainWindow::strippedName(const QString &fullFileName){
    return QFileInfo(fullFileName).fileName();
}

#ifndef QT_NO_SESSIONMANAGER
void MainWindow::commitData(QSessionManager &manager)
{
    if (manager.allowsInteraction()) {
        if (!maybeSave())
            manager.cancel();
    } else {
        // Non-interactive: save without asking
        if (textEdit->document()->isModified()){
            if (curFile.isEmpty()) saveAs();
            else save(curFile);
        }
    }
}
#endif

void MainWindow::closeEvent(QCloseEvent *event){
    if (maybeSave()) {
        QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
        settings.setValue("geometry", saveGeometry());
        event->accept();
    } else {
        event->ignore();
    }
}

bool MainWindow::saveAs(){
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    return save(dialog.selectedFiles().first());
}

void MainWindow::documentWasModified(){
    setWindowModified(textEdit->document()->isModified());
}
