QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

RC_ICONS = Resource/icon.ico

TARGET = Doki-Doki-Just-Monika
TEMPLATE = app
VERSION = 0.1.3
DEFINES += APP_NAME=\\\"$$TARGET\\\"
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += APP_EDITION=\\\"251U\\\"

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DDLCWordDic.cpp \
    DDWordDialog.cpp \
    M2GoForm.cpp \
    MASSForm.cpp \
    OSOperationWin.cpp \
    main.cpp \
    mainwindow.cpp \
    mw_buttonOperation.cpp \
    mw_quickSearch.cpp \
    mw_showMASSupport.cpp

HEADERS += \
    DDLCWordDic.h \
    DDWordDialog.h \
    M2GoForm.h \
    MASSForm.h \
    OSOperationWin.h \
    mainwindow.h

FORMS += \
    DDWordDialog.ui \
    M2GoForm.ui \
    MASSForm.ui \
    mainwindow.ui

RESOURCES += \
    rs_ddjm.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

CONFIG(debug, debug|release){
    DESTDIR =$$PWD/debug
}else{
    DESTDIR =$$PWD/release/bin
}

DISTFILES += \
    update-details.txt
