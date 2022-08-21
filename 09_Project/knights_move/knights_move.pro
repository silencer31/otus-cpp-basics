QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cell_info_keeper.cpp \
    delegate/game_delegate.cpp \
    delegate/line_delegate.cpp \
    extra_functions.cpp \
    gameprepare.cpp \
    knights_move.cpp \
    main.cpp \
    gamewindow.cpp \
    usermessage.cpp

HEADERS += \
    cell_info_keeper.h \
    delegate/game_delegate.h \
    delegate/line_delegate.h \
    extra_functions.h \
    gamewindow.h \
    knights_move.h \
    usermessage.h

FORMS += \
    gamewindow.ui \
    usermessage.ui

TRANSLATIONS += \
    knights_move_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
