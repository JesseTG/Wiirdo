#include "Wii.hpp"
#include <QtConcurrent>
#include <iostream>
#include <stdio.h>
#include <QKeyEvent>
#include <QCoreApplication>
#include <QQuickItem>
#include <QGuiApplication>
#include <Windows.h>

#pragma comment(lib, "user32.lib")

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

/*void Wii::click(){

    QQuickItem *receiver = qobject_cast<QQuickItem*>(QGuiApplication::focusObject());
    QKeyEvent *pressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_CapsLock, Qt::NoModifier, "", false, 0);
    QKeyEvent *releaseEvent = new QKeyEvent(QEvent::KeyRelease, Qt::Key_CapsLock, Qt::NoModifier, "", false, 0);
    QGuiApplication::sendEvent(receiver, pressEvent);
    //QGuiApplication::sendEvent(receiver, releaseEvent);
    std::cout<<"Clicked"<<endl;
    //QKeyEvent key(QKeyEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier, "Tab", false, 0 );


    }*/

void Wii::click(){

    BYTE keyState[256];
    GetKeyboardState((LPBYTE)&keyState);

          // Simulate a key press
             keybd_event( VK_MENU,
                          0xB8,
                          KEYEVENTF_EXTENDEDKEY | 0,
                          0 );
             keybd_event( VK_TAB,
                          0x8F,
                          KEYEVENTF_EXTENDEDKEY | 0,
                          0 );
         // Simulate a key release

             keybd_event( VK_TAB,
                          0x8F,
                          KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                          0);
             keybd_event( VK_MENU,
                          0xB8,
                          KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                          0);
    }
}
