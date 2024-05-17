QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    function.cpp \
    graph.cpp \
    graphvertex.cpp \
    information.cpp \
    main.cpp \
    matrica.cpp \
    node.cpp \
    weight.cpp

HEADERS += \
    function.h \
    graph.h \
    graphvertex.h \
    information.h \
    matrica.h \
    node.h \
    weight.h

FORMS += \
    function.ui \
    information.ui \
    matrica.ui \
    weight.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
