QT += core gui

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
VERSION = 0.2.5
DEFINES += APP_NAME=\\\"$$TARGET\\\"
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += APP_EDITION=\\\"252P\\\"

DEFINES += TEAM_WEB=\\\"https://github.com/ltofuy/DDJM/releases/download/latest\\\"

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TRANSLATIONS += \
    Doki-Doki-Just-Monika_en.ts\
    Doki-Doki-Just-Monika_zh_CN.ts

INCLUDEPATH += ./MASSForm
INCLUDEPATH += ./DDLCWordDic
INCLUDEPATH += ./DDWordDialog
INCLUDEPATH += ./kits
INCLUDEPATH += ./mainwindow
INCLUDEPATH += ./M2GoForm

SOURCES += \
    DDLCWordDic/DDLCWordDic.cpp \
    DDWordDialog/DDWordDialog.cpp \
    DDWordDialog/DDWordDialog_slots_check.cpp \
    DDWordDialog/DDWordDialog_slots_getTranslation.cpp \
    DDWordDialog/DDWordDialog_slots_reset.cpp \
    DDWordDialog/DDWordDialog_slots_setWord.cpp \
    DDWordDialog/DDWordDialog_slots_toEnableMatch.cpp \
    DDWordDialog/DDWordDialog_slots_translateOL.cpp \
    M2GoForm/M2GoForm.cpp \
    MASSForm/MASSForm.cpp \
    MASSForm/MASS_QFileInfoList_getGiftFiles.cpp \
    MASSForm/MASS_QJsonObject_loadJson.cpp \
    MASSForm/MASS_QStringList_getCurrentProcesses.cpp \
    MASSForm/MASS_bool_check.cpp \
    MASSForm/MASS_bool_isMatched.cpp \
    MASSForm/MASS_bool_isThumb.cpp \
    MASSForm/MASS_int_appearanceType.cpp \
    MASSForm/MASS_slot_buttonOperation.cpp \
    MASSForm/MASS_slot_makeBackup.cpp \
    MASSForm/MASS_slot_openDDLCFolder.cpp \
    MASSForm/MASS_slot_refreshGiftStatus.cpp \
    MASSForm/MASS_slot_reload.cpp \
    MASSForm/MASS_slot_visitMonika.cpp \
    MASSForm/MASS_toSendGift.cpp \
    kits/OSOperationWin.cpp \
    kits/UpdateJsonForm.cpp \
    kits/ez_write_log.cpp \
    main.cpp \
    mainwindow/mainwindow.cpp \
    mainwindow/mw_autoCheckUpdate.cpp \
    mainwindow/mw_buttonOperation.cpp \
    mainwindow/mw_checkFileLoopTask.cpp \
    mainwindow/mw_checkLanguage.cpp \
    mainwindow/mw_clearDir.cpp \
    mainwindow/mw_createDir.cpp \
    mainwindow/mw_download.cpp \
    mainwindow/mw_quickSearch.cpp \
    mainwindow/mw_showMASSupport.cpp \
    mainwindow/mw_slots_enableAutoUpdate.cpp

HEADERS += \
    DDLCWordDic/DDLCWordDic.h \
    DDWordDialog/DDWordDialog.h \
    M2GoForm/M2GoForm.h \
    MASSForm/MASSForm.h \
    kits/OSOperationWin.h \
    kits/UpdateJsonForm.h \
    kits/ez_write_log.h \
    mainwindow/mainwindow.h

FORMS += \
    DDWordDialog/DDWordDialog.ui \
    M2GoForm/M2GoForm.ui \
    MASSForm/MASSForm.ui \
    kits/UpdateJsonForm.ui \
    mainwindow/mainwindow.ui

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
