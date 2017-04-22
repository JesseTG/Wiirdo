#ifndef KEYSENDER_HPP
#define KEYSENDER_HPP

#include <QObject>
#include <QInputEvent>
#include <QKeyEvent>
#include <QMouseEvent>

#ifdef Q_OS_LINUX
typedef struct _XDisplay Display;
#endif

namespace wiirdo {
class Keysender : public QObject
{
  Q_OBJECT

public:
  explicit Keysender(QObject *parent = nullptr);

  Keysender(const Keysender& other) = delete;
  Keysender& operator=(const Keysender& other) = delete;
  virtual ~Keysender();

public slots:
  bool send(const QEvent& event);
  bool keyPress(uint64_t key, int modifiers);
  bool keyRelease(const QKeyEvent& event);
  bool keyShortcutOverride(const QKeyEvent& event);

  bool shortcutEvent(const QShortcutEvent& event);
  bool mouseEvent(const QMouseEvent& event);
  bool wheelEvent(const QWheelEvent& event);
private:
#ifdef Q_OS_LINUX
  Display* x11;
#endif
};
}
#endif // KEYSENDER_HPP
