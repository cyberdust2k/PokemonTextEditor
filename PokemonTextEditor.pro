QT += core gui widgets


FORMS += \
    windows/mainwindow.ui \
    windows/searchwindow.ui \
    windows/insertwindow.ui

HEADERS += \
    include/string.hpp \
    include/mainwindow.h \
    include/searchwindow.h \
    include/insertwindow.h

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/string.cpp \
    src/searchwindow.cpp \
    src/insertwindow.cpp

INCLUDEPATH += include
