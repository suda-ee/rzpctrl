# -------------------------------------------------
# Project created by QtCreator 2009-03-22T20:09:25
# -------------------------------------------------
QT += network \
    xml
TARGET = rzpctrl
TEMPLATE = app
CONFIG += windows

# CONFIG += embed_manifest_exe
SOURCES += main.cpp \
    mainwindow.cpp \
    tabhost.cpp \
    ctlitems.cpp \
    ratestatepage.cpp \
    rtstatepage.cpp \
    rtsetpage.cpp \
    quickconn.cpp \
    dlgaddrbk.cpp \
    addrmodel.cpp \
    statemodel.cpp \
    statedelegate.cpp \
    rtsetmodel.cpp \
    rtsetdelegate.cpp
HEADERS += mainwindow.h \
    tabhost.h \
    ctlitems.h \
    ratestatepage.h \
    rtstatepage.h \
    rtsetpage.h \
    quickconn.h \
    dlgaddrbk.h \
    addrmodel.h \
    statemodel.h \
    statedelegate.h \
    rtsetmodel.h \
    rtsetdelegate.h
FORMS += mainwindow.ui \
    tabhost.ui \
    ratestatepage.ui \
    rtsetpage.ui \
    rtstatepage.ui \
    quickconn.ui \
    dlgaddrbk.ui
RESOURCES += zpmain.qrc
win32:RC_FILE = rzpctrl.rc
