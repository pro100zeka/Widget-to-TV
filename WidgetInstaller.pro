#-------------------------------------------------
#
# Project created by QtCreator 2014-03-01T22:48:59
#
#-------------------------------------------------
APP_NAME = WigdetToTV
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += core gui network

TEMPLATE = app

OBJECTS_DIR = Build/Obj

CONFIG(debug, debug|release)
{
    TARGET = Build/Bin/Dbg/WigdetToTV
    OBJECTS_DIR = Build/Obj/Dbg
    MOC_DIR = Build/Moc/Dbg
    UI_DIR = Build/Ui/Dbg
    #RCC_DIR
}

CONFIG(release, debug|release)
{
    TARGET = Build/Bin/Rel/WigdetToTV
    OBJECTS_DIR = Build/Obj/Rel
    MOC_DIR = Build/Moc/Rel
    UI_DIR = Build/Ui/Rel
}

INCLUDEPATH = \
    Sources/Inc

SOURCES += \
    Sources/Src/main.cpp \
    Sources/Src/mainwindow.cpp \
    Sources/Src/processor.cpp \
    Sources/Src/widgetdatamodel.cpp \
    Sources/Src/widgetnetwork.cpp \
    Sources/Src/xmlgen.cpp

HEADERS  += \
    Sources/Inc/mainwindow.h \
    Sources/Inc/processor.h \
    Sources/Inc/widgetdatamodel.h \
    Sources/Inc/widgetnetwork.h \
    Sources/Inc/xmlgen.h

FORMS    += \
    Sources/Ui/mainwindow.ui

RESOURCES +=
