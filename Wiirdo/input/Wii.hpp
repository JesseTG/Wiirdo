#ifndef WII_HPP
#define WII_HPP

#include <QObject>
#include <QVector>
#include <QtConcurrent>
#include <QQmlListProperty>

#include <wiiuse.h>

#include "input/WiiRemote.hpp"

namespace wii {

const int MAX_WIIMOTES = 4;

class Wii : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QQmlListProperty<wii::WiiRemote> wiimotes READ getWiimotes NOTIFY wiimotesChanged)
public:
  explicit Wii(QObject *parent);
  Wii() : Wii(nullptr) { }

  Wii(const Wii& other) = delete;
  Wii& operator=(const Wii& other) = delete;
  virtual ~Wii();
  const QQmlListProperty<wii::WiiRemote>& getWiimotes() const { return _wiimoteProperty; }
  const QList<WiiRemote*>& getWiimotesCpp() const { return _qwiimotes; }

signals:
  void wiimotesChanged();
  void connectionSucceeded();
  void connectionFailed();
  void connectionDone();

public slots:
  void findAndConnect(int timeout = 5, bool rumbleAck = true, bool autoreconnect = false);
  void poll();
  void click();
  void Win_Menu();
  void Win_TaskManager();
  void Win_Apps();
  void Win_Mute();
  void Music_Play();
  void Music_Pause();
  void Music_Next();
  void Music_Previous();

private:
  wiimote_t** wiimotes;
  int _connected;
  QQmlListProperty<WiiRemote> _wiimoteProperty;
  QList<WiiRemote*> _qwiimotes; // these are children and will go away upon destruction
  QFutureWatcher<int> _futureWatcher;
};
}

#endif // WII_HPP
