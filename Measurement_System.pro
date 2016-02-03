#-------------------------------------------------
#
# Project created by QtCreator 2015-02-22T14:28:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Continental_Measurement_System
TEMPLATE = app

FORMS += \
    colorchangedialog.ui \
    mdffileinfodialog.ui \
    measuringwindow.ui \
    signalselect.ui \
    widgetb.ui \
    widgeta.ui

HEADERS += \
    colorchangedialog.h \
    mdffileinfodialog.h \
    measuringwindow.h \
    mysignal.h \
    signalselect.h \
    MDF/MDFBaseData.h \
    MDF/MDFCC.h \
    MDF/MDFCCLinear.h \
    MDF/MDFCCTextTable.h \
    MDF/MDFCG.h \
    MDF/MDFChannel.h \
    MDF/MDFConversion.h \
    MDF/MDFData.h \
    MDF/MDFDG.h \
    MDF/MDFHeader.h \
    MDF/MDFID.h \
    MDF/MDFLib.h \
    MDF/MDFPR.h \
    MDF/MDFTX.h \
    qcustomplot/qcustomplot.h \
    widgetb.h \
    widgeta.h \
    modelmanager.h

SOURCES += \
    colorchangedialog.cpp \
    main.cpp \
    mdffileinfodialog.cpp \
    measuringwindow.cpp \
    mysignal.cpp \
    signalselect.cpp \
    MDF/MDFBaseData.cpp \
    MDF/MDFCC.cpp \
    MDF/MDFCCLinear.cpp \
    MDF/MDFCCTextTable.cpp \
    MDF/MDFCG.cpp \
    MDF/MDFChannel.cpp \
    MDF/MDFConversion.cpp \
    MDF/MDFDG.cpp \
    MDF/MDFHeader.cpp \
    MDF/MDFID.cpp \
    MDF/MDFLib.cpp \
    MDF/MDFPR.cpp \
    MDF/MDFTX.cpp \
    qcustomplot/qcustomplot.cpp \
    widgetb.cpp \
    widgeta.cpp \
    modelmanager.cpp

RESOURCES += \
    resources/MyResources.qrc

DISTFILES += \
    resources/icons/Line Chart.png \
    resources/icons/Window Left Panel.png \
    resources/icons/Window Performance.png

