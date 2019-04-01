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


# 版本信息资源文件
RC_FILE += ./version.rc

# 源文件
SOURCES += \
        main.cpp \
    Modules/MainUI/MainWindow.cpp \
    Utils/UIDUtil.cpp \
    Config/EventType.cpp \
    Component/UI/CPictureBox.cpp \
    Modules/SliceEdit/SliceEdit.cpp \
    Config/GlobalVar.cpp \
    Config/EnumType.cpp \
    Config/GlobalStruct.cpp \
    Modules/AboutWnd/AboutWnd.cpp \
    Utils/FileUtil.cpp \
    Services/Dispatcher.cpp \
    Modules/Export/ExportWnd.cpp \
    Modules/Import/ImportWnd.cpp \
    Modules/SlicePanel/SlicePanel.cpp \
    Modules/SlicePanel/Models/CSliceGridData.cpp \
    Modules/SlicePanel/Models/CSlicePanelData.cpp \
    Component/UI/CGridArea.cpp \
    Utils/StringUtil.cpp \
    Modules/SlicePanel/Component/CScrollArea.cpp \
    Modules/SlicePanel/Component/CSliceItem.cpp \
    Modules/SlicePanel/Component/ImgAttrListItem.cpp \
    Utils/MathUtil.cpp \
    Utils/WidgetUtil.cpp \
    Utils/DebugUtil.cpp

HEADERS += \
    ImageSlicer.h \
    Modules/MainUI/MainWindow.h \
    Config/EventType.h \
    Utils/UtilsInit.h \
    Utils/UIDUtil.h \
    Component/UI/CPictureBox.h \
    Modules/SliceEdit/SliceEdit.h \
    Config/GlobalVar.h \
    Config/EnumType.h \
    Config/GlobalStruct.h \
    Modules/AboutWnd/AboutWnd.h \
    Utils/FileUtil.h \
    Config/ConfigInit.h \
    Services/Dispatcher.h \
    Services/ServicesInit.h \
    Modules/Export/ExportWnd.h \
    Modules/Import/ImportWnd.h \
    Modules/SlicePanel/SlicePanel.h \
    Modules/SlicePanel/Models/CSliceGridData.h \
    Modules/SlicePanel/Models/CSlicePanelData.h \
    Component/UI/CGridArea.h \
    Utils/StringUtil.h \
    Modules/SlicePanel/Component/CScrollArea.h \
    Modules/SlicePanel/Component/CSliceItem.h \
    Modules/SlicePanel/Component/ImgAttrListItem.h \
    Utils/MathUtil.h \
    Utils/WidgetUtil.h \
    Utils/DebugUtil.h

FORMS += \
    Modules/MainUI/MainWindow.ui \
    Modules/SliceEdit/SliceEdit.ui \
    Modules/AboutWnd/AboutWnd.ui \
    Modules/Export/ExportWnd.ui \
    Modules/Import/ImportWnd.ui \
    Modules/SlicePanel/SlicePanel.ui \
    Modules/SlicePanel/Component/ImgAttrListItem.ui

# 第三方工程
include("../qtpropertybrowser/src/qtpropertybrowser.pri")
