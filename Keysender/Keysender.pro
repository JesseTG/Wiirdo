TARGET = Keysender
TEMPLATE = lib
CONFIG += staticlib c++11
QT += core gui gui-private

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Keysender-common.cpp \

HEADERS += \
    Keysender.hpp \

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32 {
  SOURCES += Keysender-windows.cpp
}

macx {
  SOURCES += Keysender-macos.cpp
}

linux {
  QT += x11extras
  SOURCES += Keysender-linux.cpp
  LIBS += \
      -L/usr/local/lib \
      -lX11 \
      -lXtst \
}
