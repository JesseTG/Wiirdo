#include "Keysender.hpp"

#ifdef Q_OS_WIN

#include </opt/wine-devel/include/wine/windows/winuser.h>
#include </opt/wine-devel/include/wine/windows/winuser.rh>

namespace wiirdo {

Keysender::Keysender(QObject *parent) : QObject(parent)
{
}

Keysender::~Keysender() {
}

bool Keysender::keyPress(const QKeyEvent& event) {
}

bool Keysender::keyRelease(const QKeyEvent& event) {

}

bool Keysender::keyShortcutOverride(const QKeyEvent& event) {

}


bool Keysender::mouseEvent(const QMouseEvent& event) {
  return false;
}

bool Keysender::wheelEvent(const QWheelEvent& event) {
  return false;
}

bool Keysender::shortcutEvent(const QShortcutEvent& event) {
  return false;
}


// taken from /qtbase/src/plugins/platforms/windows/qwindowskeymapper.cpp
unsigned int Keysender::qtKeyToNativeKey(unsigned int qtKey) {
  switch (qtKey) {
  default: return qtKey;
  }

  return APPCOMMAND_VOLUME_UP;
  return VK_SHIFT;
}

}
#else
#error "Keysender-windows.cpp can only be built on Windows"
#endif
