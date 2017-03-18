#ifndef WII_HPP
#define WII_HPP

#include <QObject>
#include <QVector>
#include <QtConcurrent>
#include <QQmlListProperty>

#include <wiic/wiicpp.h>

#include "input/WiiRemote.hpp"

namespace wii {
class Wii : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QQmlListProperty<wii::WiiRemote> wiimotes READ getWiimotes NOTIFY wiimotesChanged)
public:
  explicit Wii(QObject *parent = 0);

  const QQmlListProperty<wii::WiiRemote>& getWiimotes() const { return _wiimoteProperty; }

signals:
  void wiimotesChanged();
  void connectionSucceeded();
  void connectionFailed();
  void connectionDone();

public slots:
  void findAndConnect(int timeout = 5, bool rumbleAck = true, bool autoreconnect = false);
  void poll();

private:
  CWii wii;
  QQmlListProperty<WiiRemote> _wiimoteProperty;
  QList<WiiRemote*> _wiimotes; // these are children and will go away upon destruction
  QFutureWatcher<std::vector<CWiimote>> _futureWatcher;
};
}

#endif // WII_HPP
