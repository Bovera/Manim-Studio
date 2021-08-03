#include "tutorialpage.h"

TutorialPage::TutorialPage(){
    layout = new QGridLayout(this);

    QLabel *list1 = new QLabel;
    list1->setText("<p style=\"font-size:20px\"><b>Mirrors</b></p>");
    layout->addWidget(list1);
    
    QLabel *therebItem = new QLabel;
    therebItem->setText(tr("1. <a href=\"https://github.com/3b1b/manim\">Original Manim version (on Github)</a>"));
    layout->addWidget(therebItem);
    connect(therebItem,SIGNAL(linkActivated(QString)),this,SLOT(openUrl(QString)));
    
    QLabel *communityItem = new QLabel;
    communityItem->setText(tr("2. <a href=\"https://github.com/ManimCommunity/manim\">Manim community edition(on Github)</a>"));
    layout->addWidget(communityItem);
    connect(communityItem,SIGNAL(linkActivated(QString)),this,SLOT(openUrl(QString)));
    
    QLabel *chinaItem = new QLabel;
    chinaItem->setText(tr("3. <a href=\"https://gitee.com/m1rr0rs/manim\">Manim mirror for Chinese users(on Gitee)</a>"));
    layout->addWidget(chinaItem);
    connect(chinaItem,SIGNAL(linkActivated(QString)),this,SLOT(openUrl(QString)));

    QLabel *list2 = new QLabel;
    list2->setText("<p style=\"font-size:20px\"><b>Chinese tutorial</b></p>");
    layout->addWidget(list2);

    QLabel *chinaItem1 = new QLabel;
    chinaItem1->setText(tr("1. <a href=\"https://github.com/cai-hust/manim-tutorial-CN\">Manim tutorial in Chinese(Github edition)</a>"));
    layout->addWidget(chinaItem1);
    connect(chinaItem1,SIGNAL(linkActivated(QString)),this,SLOT(openUrl(QString)));

    QLabel *chinaItem2 = new QLabel;
    chinaItem2->setText(tr("2. <a href=\"https://www.bilibili.com/read/readlist/rl82339\">Manim tutorial in Chinese(bilibili edition)</a>"));
    layout->addWidget(chinaItem2);
    connect(chinaItem2,SIGNAL(linkActivated(QString)),this,SLOT(openUrl(QString)));

    QLabel *chinaItem3 = new QLabel;
    chinaItem3->setText(tr("3. <a href=\"https://www.bilibili.com/video/av64023740\">English video (Reprinted from youtobe)</a>"));
    layout->addWidget(chinaItem3);
    connect(chinaItem3,SIGNAL(linkActivated(QString)),this,SLOT(openUrl(QString)));
}

void TutorialPage::openUrl(QString url){
    QDesktopServices::openUrl(url);
}
