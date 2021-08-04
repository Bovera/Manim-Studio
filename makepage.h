#ifndef MAKEPAGE_H
#define MAKEPAGE_H

#include <QDialog>

namespace Ui {
class MakePage;
}

class MakePage : public QDialog
{
    Q_OBJECT

public:
    explicit MakePage(QWidget *parent = nullptr);
    ~MakePage();
    QString curFile;

private:
    Ui::MakePage *ui;
};

#endif // MAKEPAGE_H
