TEMPLATE = subdirs

QT += qml quick 3dcore 3drender 3dinput 3dlogic 3dextras 3dquick 3dquickextras concurrent
CONFIG += c++11

OTHER_FILES += \
  .gitignore

SUBDIRS += \
    Wiirdo-Example \
    Wiirdo \
    Keysender \
    Wiirdo-Record \
    Wiirdo-Train \

Wiirdo-Example.depends = Wiirdo
Wiirdo-Record.depends = Wiirdo
Wiirdo-Train.depends = Wiirdo-Record

message(top_srcdir: $$top_srcdir)
message(top_builddir: $$top_builddir)
