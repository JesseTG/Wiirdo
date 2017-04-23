#include "Keysender.hpp"

#include <QEvent>
#include <QInputEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QShortcutEvent>

// Implement any Keysender methods that are platform-agnostic here

namespace wiirdo {

bool Keysender::send(const QEvent& event) {
  switch (event.type()) {
  case QEvent::KeyPress:
    return keyPress(static_cast<Qt::Key>(static_cast<const QKeyEvent&>(event).key()));
  case QEvent::KeyRelease:
    return keyRelease(static_cast<Qt::Key>(static_cast<const QKeyEvent&>(event).key()));
  case QEvent::ShortcutOverride:
    return keyShortcutOverride(static_cast<const QKeyEvent&>(event));

  case QEvent::MouseButtonDblClick:
  case QEvent::MouseButtonPress:
  case QEvent::MouseButtonRelease:
  case QEvent::MouseMove:
    return mouseEvent(static_cast<const QMouseEvent&>(event));
  case QEvent::Wheel:
    return wheelEvent(static_cast<const QWheelEvent&>(event));
  case QEvent::Shortcut:
    return shortcutEvent(static_cast<const QShortcutEvent&>(event));
  default:
    return false;
  }
}

}
