#include "Wii.hpp"

#include <QtConcurrent>


namespace wii {

Wii::Wii(QObject *parent) : QObject(parent), _wiimoteProperty(nullptr, this->_wiimotes)
{
  QObject::connect(&_futureWatcher, &decltype(_futureWatcher)::finished, [this]() {
    auto wiimotes = _futureWatcher.result();

    if (wiimotes.empty()) {
      // If we couldn't find any Wii Remotes...
      this->connectionFailed();
    }
    else {
      QList<WiiRemote*> wm;
      for (const CWiimote& w : wiimotes) {
        wm.push_back(new WiiRemote(w, this));
      }

      this->_wiimotes = wm;

      this->wiimotesChanged();
      this->connectionSucceeded();
    }

    this->connectionDone();
  });
}


void Wii::findAndConnect(int timeout, bool rumbleAck, bool autoreconnect) {

  if (_futureWatcher.isFinished()) {
    // If we're not already looking for Wiimotes...

    QFuture<std::vector<CWiimote>> future = QtConcurrent::run([this, timeout, rumbleAck, autoreconnect]() {
      return wii.FindAndConnect(timeout, rumbleAck, autoreconnect);
    });

    this->_futureWatcher.setFuture(future);
  }
}

void Wii::poll()  {
  wii.Poll();

  for (WiiRemote* wiimote : this->_wiimotes) {
    wiimote->batteryChanged();

    Accelerometer* accelerometer = wiimote->getAccelerometer();

    accelerometer->gravityChanged();
    accelerometer->orientationChanged();
    accelerometer->gravityRawChanged();
  }
}

}
