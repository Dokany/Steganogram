#-------------------------------------------------
#
# Project created by QtCreator 2017-11-26T11:01:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Steganogram
TEMPLATE = app


SOURCES += main.cpp\
    ViewsRequestData.cpp \
    ViewsReplyData.cpp \
    userwindow.cpp \
    UDPSocket.cpp \
    StatusData.cpp \
    Service.cpp \
    Server.cpp \
    PingData.cpp \
    Peer.cpp \
    PackGen.cpp \
    Message.cpp \
    main_service.cpp \
    loginwindow.cpp \
    imageviewer.cpp \
    ImageRequestData.cpp \
    ImageListData.cpp \
    imagelist.cpp \
    ImageData.cpp \
    Data.cpp \
    Client.cpp \
    AuthData.cpp \
    AckData.cpp

HEADERS  += ViewsRequestData.h \
    ViewsReplyData.h \
    userwindow.h \
    UDPSocket.h \
    StatusData.h \
    Service.h \
    Server.h \
    PingData.h \
    Peer.h \
    PackGen.h \
    Message.h \
    loginwindow.h \
    imageviewer.h \
    ImageRequestData.h \
    ImageListData.h \
    imagelist.h \
    ImageData.h \
    Data.h \
    Client.h \
    AuthData.h \
    AckData.h

FORMS    += userwindow.ui \
    loginwindow.ui \
    imageviewer.ui \
    imagelist.ui

DISTFILES += \
    ImageRequestData.h.gch \
    ImageListData.h.gch \
    Data.h.gch \
    AuthData.h.gch \
    Steganogram.pro.user \
    name \
    compilation \
    auth.txt
