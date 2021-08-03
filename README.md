# Manim Studio Project

## Introduction

### Manim
Manim is an animation engine for explanatory math videos. It's used to create precise animations programmatically, as seen in the videos at 3Blue1Brown. Here are its main mirrors.  

1. [original edition, by Grant Sanderson](https://github.com/manimcommunity/manim/)  
2. [community edition](https://github.com/manimcommunity/manim/)  
3. [edition for Chinese users (on Gitee)](https://gitee.com/m1rr0rs/manim)  

If you want to learn more about Manim, go [YouTube](https://www.youtube.com/watch?v=ENMyFGmq5OA). If you are in China, you may find these tutorial useful.  

1. [Manim tutorial in Chinese (Github edition)](https://github.com/cai-hust/manim-tutorial-CN)  
2. [English video (Reprinted from YouTobe)](https://www.bilibili.com/video/av64023740)  
3. [Manim tutorial in Chinese (bilibili edition)](https://www.bilibili.com/read/readlist/rl82339)  

If you just want to watch videos made by Manim, I thought you are on the wrong way. You may need to go to YouTube or bilibili to find 3Bule1Brown.  

### Manim Studio
Manim Studio is an integrated environment for creating animation using Manim. The application haven't released yet. So you need to complile it by yourself (you need to install Manim and Qt first).  

Qt(c++) is used as main programming language. This is the test edition and many parts heaven't finished yet. Everyone is welcome to join us. You can find prompts of them in the source files.  

We will use jsp to create web edition if possible. You won't need to install it yourself then.  

## Files
Files included are as follows.  
1. manim_studio.pro / main.cpp  
2. mainwindow.cpp / mainwindow.h  
3. highlighter.cpp / highlighter.h  
4. settingpage.cpp / settingpage.h / settingpage.ui  
5. checkenv.sh / checkenv.bat  
6. lang_zhcn.ts  
7. images(9 pictures included) / image.qrc  

### manim_studio.pro / main.cpp
"manim_studio.pro" tells qmake how to create the application. "main.cpp" is the entry point of the application. "config.json" tells the application its settings. It can be created when you use settingpage to change settings.  

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
