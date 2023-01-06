QT       += core gui
QT += sql
QT += svg
QT += svgwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminmainwidget.cpp \
    adminwindow.cpp \
    bookinfo.cpp \
    bookmanagementdialog.cpp \
    bookrtndialog.cpp \
    changeadmininfodialog.cpp \
    databaseRepository.cpp \
    main.cpp \
    mainwindow.cpp \
    punishinfo.cpp \
    punishmentdialog.cpp \
    readeraccountdialog.cpp \
    userinfo.cpp \
    usermainwindow.cpp \
    utils/sm3_hash.cpp \
    utils/stringutil.cpp \
    connectioninfo.cpp

HEADERS += \
    adminmainwidget.h \
    adminwindow.h \
    bookinfo.h \
    bookmanagementdialog.h \
    bookrtndialog.h \
    changeadmininfodialog.h \
    databaseRepository.h \
    mainwindow.h \
    punishinfo.h \
    punishmentdialog.h \
    readeraccountdialog.h \
    userinfo.h \
    usermainwindow.h \
    utils/sm3_hash.h \
    utils/stringutil.h \
    connectioninfo.h

FORMS += \
    adminmainwidget.ui \
    adminwindow.ui \
    bookmanagementdialog.ui \
    bookrtndialog.ui \
    changeadmininfodialog.ui \
    mainwindow.ui \
    punishmentdialog.ui \
    readeraccountdialog.ui \
    usermainwindow.ui

RESOURCES += \
    icons.qrc
