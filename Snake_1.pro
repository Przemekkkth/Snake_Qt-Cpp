QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    game.cpp \
    gamescene.cpp \
    main.cpp \
    view.cpp


RESOURCES += \
    resource.qrc \
    resource.qrc

HEADERS += \
    game.h \
    gamescene.h \
    view.h
