#include "Keysender.hpp"

#ifdef Q_OS_MACOS
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

}
#else
#error "Keysender-macos.cpp can only be built on macOS"
#endif
