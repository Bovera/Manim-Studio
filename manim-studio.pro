QT += widgets
requires(qtConfig(filedialog))

HEADERS       = mainwindow.h \
                highlighter.h \
                settingpage.h \
                texedit.h \
                tutorialpage.h
                
SOURCES       = main.cpp \
                mainwindow.cpp \
                highlighter.cpp \
                settingpage.cpp  \
                texedit.cpp \
                tutorialpage.cpp

RESOURCES     = image.qrc \
                checkenv.sh \
                checkenv.bat \
                README.md

TRANSLATIONS  = lang_zhcn.ts

FORMS += \
    settingpage.ui
