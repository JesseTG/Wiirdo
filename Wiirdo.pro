TEMPLATE = subdirs

QT += qml quick 3dcore 3drender 3dinput 3dlogic 3dextras 3dquick 3dquickextras concurrent
CONFIG += c++11

OTHER_FILES += \
  .gitignore

SUBDIRS += \
    Wiirdo-Example \
    Wiirdo

Wiirdo-Example.depends = Wiirdo
