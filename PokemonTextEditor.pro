QT += core gui widgets


FORMS += \
    windows/mainwindow.ui \
    windows/searchwindow.ui \
    windows/insertwindow.ui \
    windows/aboutwindow.ui \
    windows/fswindow.ui

HEADERS += \
    include/string.hpp \
    include/mainwindow.h \
    include/searchwindow.h \
    include/insertwindow.h \
    include/aboutwindow.h \
    include/fswindow.h

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/string.cpp \
    src/searchwindow.cpp \
    src/insertwindow.cpp \
    src/aboutwindow.cpp \
    src/fswindow.cpp

INCLUDEPATH += include

RESOURCES += \
    images.qrc
