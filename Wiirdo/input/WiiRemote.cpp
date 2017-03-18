#include "WiiRemote.hpp"

namespace wii {

WiiRemote::WiiRemote(const CWiimote& _wiimote, QObject *parent) :
  QObject(parent),
  wiimote(_wiimote),
  accelerometer(_wiimote.Accelerometer),
  motionPlus(nullptr) {
}

bool WiiRemote::isAccelerometerEnabled() {
  return wiimote.isUsingACC();
}

void WiiRemote::setAccelerometerEnabled(bool isUsing) {

  wiimote.SetMotionSensingMode(isUsing ? CWiimote::ON : CWiimote::OFF);

  accelerometerEnabledChanged(isUsing);
}

bool WiiRemote::isRumbleEnabled() {
  return wiimote.isRumbleEnabled();
}

void WiiRemote::setRumbleEnabled(bool isUsing) {
  wiimote.SetRumbleMode(isUsing ? CWiimote::ON : CWiimote::OFF);

  rumbleEnabledChanged(isUsing);
}

bool WiiRemote::isMotionPlusEnabled() {
  return wiimote.isUsingMotionPlus();
}

void WiiRemote::setMotionPlusEnabled(bool isUsing) {
  wiimote.EnableMotionPlus(isUsing ? CWiimote::ON : CWiimote::OFF);

  motionPlusEnabledChanged(isUsing);
}

bool WiiRemote::isSmoothingEnabled() {
  return wiimote.GetFlags() & WIIC_SMOOTHING;
}

void WiiRemote::setSmoothingEnabled(bool isUsing) {
  wiimote.SetSmoothing(isUsing);

  smoothingEnabledChanged(isUsing);
}

int WiiRemote::getId() {
  return wiimote.GetID();
}

QString WiiRemote::getAddress() {
  return QString(wiimote.GetAddress());
}

float WiiRemote::getBattery() {
  // TODO: Detect whether or not this has *really* changed
  return wiimote.GetBatteryLevel();
}
}
