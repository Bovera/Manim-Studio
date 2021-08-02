# Manim Studio Project
----------------------
## Introduction
### Manim
Manim is an animation engine for explanatory math videos. It's used to create precise animations programmatically, as seen in the videos at 3Blue1Brown.  
[original edition, by Grant Sanderson](https://github.com/manimcommunity/manim/)  
[community edition](https://github.com/manimcommunity/manim/)  
[edition for Chinese users](https://gitee.com/m1rr0rs/manim)  
### Manim Studio
Manim Studio is an integrated environment for creating animation using Manim. Qt(c++) is used as main programming language. This is the test edition and many parts heaven't finished yet. You can find prompts of them in the source files.  
-----------------------
## Files
Files included are as follows.  
1. manim_studio.pro / main.cpp / config.json
2. mainwindow.cpp / mainwindow.h  
3. highlighter.cpp / highlighter.h  
4. settingpage.cpp / settingpage.h / settingpage.ui  
5. checkenv.sh / checkenv.bat  
6. lang_zhcn.ts  
7. images(9 pictures included) / image.qrc  
### manim_studio.pro / main.cpp / config.json
**You should move config.json to target folder.**  
"manim_studio.pro" tells qmake how to create the application. "main.cpp" is the entry point of the application. "config.json" tells the application its settings.  
### mainwindow.cpp / mainwindow.h
Most of them inherits from Qt Application Example.  
### highlighter.cpp / highlighter.h
They describe the highlighting rules.  
### settingpage.cpp / settingpage.h / settingpage.ui
They are designed with Qt User Interface. They are used to set the application.  
### checkenv.sh / checkenv.bat
**You should move one of them to target folder. "checkenv.sh" is for Linux, while "checkenv.bat" is for Windows.**  
They are used to check whether the Manim environment has been set up completely or not and help users set up environment.  
### lang_zhcn.ts
**This file is created by Lupdte and translated by myself. You should use Irelease to create ".qm" files and move ".qm" files to target folder.**  
### images(9 pictures included) / image.qrc
6 of them come from Qt Application Example and won't be used when included in your system theme. "image.qrc" acts as a link between qmake and images.  
