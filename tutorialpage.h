#ifndef TUTORIALPAGE_H
#define TUTORIALPAGE_H
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QDesktopServices>
#include <QUrl>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class TutorialPage : public QDialog{
    Q_OBJECT

public:
    TutorialPage();

public slots:
    void openUrl(QString);

private:
    QGridLayout *layout;
};

#endif // TUTORIALPAGE_H
