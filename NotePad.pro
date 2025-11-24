QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Res.qrc

DISTFILES += \
    Res/circle-info-solid-full.svg \
    Res/circle-xmark-regular-full.svg \
    Res/clipboard-regular-full.svg \
    Res/copy-solid-full.svg \
    Res/file-export-solid-full.svg \
    Res/file-solid-full.svg \
    Res/floppy-disk-solid-full.svg \
    Res/folder-open-solid-full.svg \
    Res/font-solid-full.svg \
    Res/paint-roller-solid-full.svg \
    Res/palette-solid-full.svg \
    Res/print-solid-full.svg \
    Res/rotate-left-solid-full.svg \
    Res/rotate-right-solid-full.svg \
    Res/scissors-solid-full.svg
