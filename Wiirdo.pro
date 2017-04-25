TEMPLATE = subdirs

QT += qml quick 3dcore 3drender 3dinput 3dlogic 3dextras 3dquick 3dquickextras concurrent
CONFIG += c++11

OTHER_FILES += \
  .gitignore

SUBDIRS += \
    Wiirdo-Example \
    Wiirdo \
    Wiirdo-Record \
    Wiirdo-Train \
    Keysender \
    Keysender-Test \

Keysender-Test.depends = Keysender
Wiirdo-Config.depends = Wiirdo
Wiirdo-Example.depends = Wiirdo
Wiirdo-Record.depends = Wiirdo
Wiirdo-Train.depends = Wiirdo-Record

message(top_srcdir: $$top_srcdir)
message(top_builddir: $$top_builddir)

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -lWS2_32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -lWS2_32d
else:unix: LIBS += -L$$PWD/./ -lWS2_32

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
