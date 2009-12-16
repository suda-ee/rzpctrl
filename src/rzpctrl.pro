########################################################################
# Copyright (c) 2009 Soochow University
# $Id: $
# Purpose: 
########################################################################
TEMPLATE = app
TARGET = rzpctrl
QT += network \
    xml
PRODUCT_VERSION=0,1,1,0
DEFINES += PRODUCT_VERSION=$${PRODUCT_VERSION}
DEFINES += PRODUCT_VERSION_STR=\\\"$$PRODUCT_VERSION\\\"
FILE_VERSION=0,1,1,0
DEFINES += FILE_VERSION=$${FILE_VERSION}
DEFINES += FILE_VERSION_STR=\\\"$$FILE_VERSION\\\"
win32 {
    CONFIG += embed_manifest_exe windows 
    #CONFIG += embed_manifest_exe console
}
CODECFORTR = GBK
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
