#-------------------------------------------------
#
# Project created by QtCreator 2017-04-10T19:31:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = air_condition
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog1.cpp \
    dialog2.cpp \
    dialog3.cpp \
    dialog5.cpp \
    dialog7.cpp \
    dialog8.cpp \
    host.cpp \
    customer.cpp \
    server.cpp \
    socket.cpp \
    dialog9.cpp

HEADERS  += mainwindow.h \
    dialog1.h \
    dialog2.h \
    dialog3.h \
    dialog5.h \
    dialog7.h \
    dialog8.h \
    host.h \
    customer.h \
    server.h \
    socket.h \
    dialog9.h

FORMS    += mainwindow.ui \
    dialog1.ui \
    dialog2.ui \
    dialog3.ui \
    dialog5.ui \
    dialog7.ui \
    dialog8.ui \
    dialog9.ui

RESOURCES += \
    resource.qrc
QT += network
