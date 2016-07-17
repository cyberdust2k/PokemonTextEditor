QT += core gui widgets


FORMS += \
    windows/mainwindow.ui \
    windows/searchwindow.ui

HEADERS += \
    include/string.hpp \
    include/mainwindow.h \
    include/searchwindow.h

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/string.cpp \
    src/searchwindow.cpp

INCLUDEPATH += include
