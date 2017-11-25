#-------------------------------------------------
#
# Project created by QtCreator 2017-11-12T01:25:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Steganogram
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
        loginwindow.cpp \
    userwindow.cpp \
    AckData.cpp \
    AuthData.cpp \
    Client.cpp \
    Data.cpp \
    ImageData.cpp \
    ImageListData.cpp \
    ImageRequestData.cpp \
    Message.cpp \
    PackGen.cpp \
    Peer.cpp \
    PingData.cpp \
    Server.cpp \
    Service.cpp \
    StatusData.cpp \
    UDPSocket.cpp \
    imageviewer.cpp \
    accessjpeg.cpp \
    aesencrypt.cpp \
    encryptjpeg.cpp \
    ViewsRequestData.cpp \
    ViewsReplyData.cpp

HEADERS += \
        loginwindow.h \
    userwindow.h \
    AckData.h \
    AuthData.h \
    Client.h \
    Data.h \
    ImageData.h \
    ImageListData.h \
    ImageRequestData.h \
    Message.h \
    PackGen.h \
    Peer.h \
    PingData.h \
    Server.h \
    Service.h \
    StatusData.h \
    UDPSocket.h \
    imageviewer.h \
    accessjpeg.h \
    aesencrypt.h \
    encryptjpeg.h \
    ViewsRequestData.h \
    ViewsReplyData.h

FORMS += \
        loginwindow.ui \
    imageviewer.ui \
    userwindow.ui

DISTFILES += \
    cat.jpg \
    dog_b.jpg \
    dog_s.jpg \
    dogg.jpg \
    auth.txt \
    dog_b.txt \
    dog.txt
