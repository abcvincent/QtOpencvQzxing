#-------------------------------------------------
#
# Project created by QtCreator 2017-03-16T23:14:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtOpencvQzxing
TEMPLATE = app

INCLUDEPATH+=D:/opencv/build/include
INCLUDEPATH+=D:/opencv/build/include/opencv
INCLUDEPATH+=D:/opencv/build/include/opencv2

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../opencv/build/x64/vc14/lib/ -lopencv_world320
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../opencv/build/x64/vc14/lib/ -lopencv_world320d
else:unix: LIBS += -L$$PWD/../../opencv/build/x64/vc14/lib/ -lopencv_world320

INCLUDEPATH += $$PWD/../../opencv/build/x64/vc14
DEPENDPATH += $$PWD/../../opencv/build/x64/vc14

include(QZXing/QZXing.pri)
#添加路径为相对路径则文件要拷贝到源文件目录里

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
