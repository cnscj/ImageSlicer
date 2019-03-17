#-------------------------------------------------
#
# Project created by QtCreator 2019-03-11T08:52:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageSlicer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    Modules/MainUI/MainWindow.cpp \
    Utils/UIDUtil.cpp \
    Config/EventType.cpp \
    Modules/MainUI/Modules/SlicePanle/SlicePanle.cpp \
    Component/UI/CPictureBox.cpp \
    Component/UI/CImageWidget.cpp \
    Modules/MainUI/Modules/SlicePanle/Component/SlicingItem.cpp \
    Modules/MainUI/Modules/SlicePanle/Models/SSliceItem.cpp

HEADERS += \
    ImageSlicer.h \
    Modules/MainUI/MainWindow.h \
    Modules/ModulesInit.h \
    Config/EventType.h \
    Utils/UtilsInit.h \
    Utils/UIDUtil.h \
    Modules/MainUI/Modules/SlicePanle/SlicePanle.h \
    Component/UI/CPictureBox.h \
    Component/UI/CImageWidget.h \
    Modules/MainUI/Modules/SlicePanle/Component/SlicingItem.h \
    Modules/MainUI/Modules/SlicePanle/Models/SSliceItem.h

FORMS += \
    Modules/MainUI/MainWindow.ui \
    Modules/MainUI/Modules/SlicePanle/SlicePanle.ui \
    Modules/MainUI/Modules/SlicePanle/Component/SlicingItem.ui
