#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QPlainTextEdit;
QT_END_NAMESPACE

class TexEdit : public QDialog{
    Q_OBJECT

public:
    TexEdit(QWidget *parent = nullptr);
    void contentIn(const QString &);
    QString contentOut();
private:
    QPlainTextEdit *TexEdits;
};

#endif // ADDDIALOG_H
