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

void Wii::click(){
    Win_Mail();
    }

void Wii::Win_Mail(){
    BYTE keyState[256];
    GetKeyboardState((LPBYTE)&keyState);

          // Simulate a key press
             keybd_event( VK_LCONTROL,
                          0xA2,
                          KEYEVENTF_EXTENDEDKEY | 0,
                          0 );
             keybd_event( VK_ESCAPE,
                          0x1B,
                          KEYEVENTF_EXTENDEDKEY | 0,
                          0 );

         // Simulate a key release
             keybd_event( VK_LCONTROL,
                          0xA2,
                          KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                          0);
             keybd_event( VK_ESCAPE,
                          0x1B,
                          KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                          0);
}


void Wii::Music_Play(){
    BYTE keyState[256];
    GetKeyboardState((LPBYTE)&keyState);

          // Simulate a key press
             keybd_event( VK_MEDIA_PLAY_PAUSE,
                          0xB3,
                          KEYEVENTF_EXTENDEDKEY | 0,
                          0 );

         // Simulate a key release
             keybd_event( VK_MEDIA_PLAY_PAUSE,
                          0xB3,
                          KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                          0);
}

void Wii::Music_Pause(){
    BYTE keyState[256];
    GetKeyboardState((LPBYTE)&keyState);

          // Simulate a key press
             keybd_event( VK_MEDIA_PLAY_PAUSE,
                          0xB3,
                          KEYEVENTF_EXTENDEDKEY | 0,
                          0 );

         // Simulate a key release
             keybd_event( VK_MEDIA_PLAY_PAUSE,
                          0xB3,
                          KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                          0);
}

void Wii::Music_Next(){
    BYTE keyState[256];
    GetKeyboardState((LPBYTE)&keyState);

          // Simulate a key press
             keybd_event( VK_MEDIA_NEXT_TRACK,
                          0xB0,
                          KEYEVENTF_EXTENDEDKEY | 0,
                          0 );

         // Simulate a key release
             keybd_event( VK_MEDIA_NEXT_TRACK,
                          0xB0,
                          KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                          0);
}

void Wii::Music_Previous(){
    BYTE keyState[256];
    GetKeyboardState((LPBYTE)&keyState);

          // Simulate a key press
             keybd_event( VK_MEDIA_PREV_TRACK,
                          0xB1,
                          KEYEVENTF_EXTENDEDKEY | 0,
                          0 );

         // Simulate a key release
             keybd_event( VK_MEDIA_PREV_TRACK,
                          0xB1,
                          KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                          0);
}

}
