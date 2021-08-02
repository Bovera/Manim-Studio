#include "texedit.h"

#include <QtWidgets>

TexEdit::TexEdit(QWidget *parent)
    : QDialog(parent), TexEdits(new QPlainTextEdit){
    auto okButton = new QPushButton(tr("OK"));
    auto cancelButton = new QPushButton(tr("Cancel"));

    auto gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 2);

    gLayout->addWidget(TexEdits, 1, 1, Qt::AlignLeft);

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Edit the Tex content"));
}

QString TexEdit::contentOut(){
    return TexEdits->toPlainText();
}

void TexEdit::contentIn(const QString &content){
    TexEdits->insertPlainText(content);
}
