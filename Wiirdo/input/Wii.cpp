#include "Wii.hpp"

#include <QtConcurrent>


namespace wii {

Wii::Wii(QObject *parent) : QObject(parent), wiimotes(nullptr), _wiimoteProperty(nullptr, this->_qwiimotes)
{
  wiimotes = wiiuse_init(MAX_WIIMOTES);

  QObject::connect(&_futureWatcher, &decltype(_futureWatcher)::finished, [this]() {
    int connected = _futureWatcher.result();

    if (connected == 0) {
      // If we couldn't find any Wii Remotes...
      this->connectionFailed();
    }
    else {
      QList<WiiRemote*> wm;
      for (int i = 0; i < connected; ++i) {
        wm.push_back(new WiiRemote(wiimotes[i], this));
      }

      this->_qwiimotes = wm;

      this->wiimotesChanged();
      this->connectionSucceeded();
    }

    this->connectionDone();
  });
}

Wii::~Wii() {

  if (wiimotes != nullptr) {
    wiiuse_cleanup(wiimotes, MAX_WIIMOTES);
  }
}

void Wii::findAndConnect(int timeout, bool rumbleAck, bool autoreconnect) {

  if (_futureWatcher.isFinished()) {
    // If we're not already looking for Wiimotes...

    QFuture<int> future = QtConcurrent::run([this, timeout, rumbleAck, autoreconnect]() {
      int found = wiiuse_find(wiimotes, MAX_WIIMOTES, timeout);

      if (found == 0) {
        return 0;
      }
      else {
        return wiiuse_connect(wiimotes, MAX_WIIMOTES);
      }
    });

    this->_futureWatcher.setFuture(future);
  }
}

void Wii::poll()  {
  int events = wiiuse_poll(wiimotes, MAX_WIIMOTES);

  for (WiiRemote* wiimote : this->_qwiimotes) {
    wiimote->update();
  }
}

}
