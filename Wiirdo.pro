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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-Wiirdo-Desktop_Qt_5_8_0_MSVC2015_64bit-Release/Keysender/release/ -lKeysender
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-Wiirdo-Desktop_Qt_5_8_0_MSVC2015_64bit-Release/Keysender/debug/ -lKeysender
else:unix: LIBS += -L$$PWD/../build-Wiirdo-Desktop_Qt_5_8_0_MSVC2015_64bit-Release/Keysender/ -lKeysender

INCLUDEPATH += $$PWD/../build-Wiirdo-Desktop_Qt_5_8_0_MSVC2015_64bit-Release/Keysender/release
DEPENDPATH += $$PWD/../build-Wiirdo-Desktop_Qt_5_8_0_MSVC2015_64bit-Release/Keysender/release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Keysender/ -lKeysender
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Keysender/ -lKeysenderd
else:unix: LIBS += -L$$PWD/Keysender/ -lKeysender

INCLUDEPATH += $$PWD/Keysender
DEPENDPATH += $$PWD/Keysender

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Keysender/ -lKeysender
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Keysender/ -lKeysenderd
else:unix: LIBS += -L$$PWD/Keysender/ -lKeysender

INCLUDEPATH += $$PWD/Keysender
DEPENDPATH += $$PWD/Keysender

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -lKeysender
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -lKeysenderd
else:unix: LIBS += -L$$PWD/./ -lKeysender

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/./libKeysender.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/./libKeysenderd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/./Keysender.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/./Keysenderd.lib
else:unix: PRE_TARGETDEPS += $$PWD/./libKeysender.a

unix|win32: LIBS += -lKeysender
