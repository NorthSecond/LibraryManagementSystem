QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminmainwidget.cpp \
    adminwindow.cpp \
    bookinfo.cpp \
    databaseRepository.cpp \
    main.cpp \
    mainwindow.cpp \
    userinfo.cpp \
    usermainwindow.cpp \
    utils/sm3_hash.cpp \
    utils/stringutil.cpp \
    connectioninfo.cpp

HEADERS += \
    adminmainwidget.h \
    adminwindow.h \
    bookinfo.h \
    databaseRepository.h \
    mainwindow.h \
    userinfo.h \
    usermainwindow.h \
    utils/sm3_hash.h \
    utils/stringutil.h \
    connectioninfo.h

FORMS += \
    adminmainwidget.ui \
    adminwindow.ui \
    mainwindow.ui \
    usermainwindow.ui
