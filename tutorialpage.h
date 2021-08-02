#ifndef TUTORIALPAGE_H
#define TUTORIALPAGE_H
#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class TutorialPage : public QDialog{
    Q_OBJECT

public:
    TutorialPage();
};

#endif // TUTORIALPAGE_H
