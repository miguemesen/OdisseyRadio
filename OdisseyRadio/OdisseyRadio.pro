QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    artist.cpp \
    csvparse.cpp \
    fetchartists.cpp \
    getallsongs.cpp \
    loadtrack.cpp \
    main.cpp \
    mainwindow.cpp \
    page.cpp \
    reader.cpp \
    readerchecksums.cpp \
    song.cpp

HEADERS += \
    LinkedList.h \
    artist.h \
    csvparse.h \
    fetchartists.h \
    getallsongs.h \
    loadtrack.h \
    mainwindow.h \
    memoryusage.h \
    page.h \
    reader.h \
    readerchecksums.h \
    song.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_CXXFLAGS += -std=gnu++11
