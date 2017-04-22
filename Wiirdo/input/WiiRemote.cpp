#include "WiiRemote.hpp"

namespace wii {

WiiRemote::WiiRemote(wiimote_t* _wiimote, QObject *parent) :
  QObject(parent),
  wiimote(_wiimote),
  accelerometer(
    &_wiimote->accel_calib,
    &_wiimote->orient,
    &_wiimote->gforce,
    &_wiimote->orient_threshold,
    &_wiimote->accel_threshold,
    &_wiimote->accel),
  motionPlus(nullptr) {
}

WiiRemote::~WiiRemote() {

}

void WiiRemote::update() {
  emit batteryChanged();

  Accelerometer* accelerometer = this->getAccelerometer();

  emit accelerometer->gravityChanged();
  emit accelerometer->orientationChanged();
  emit accelerometer->gravityRawChanged();
  accelerometer->updateFilters();
}

bool WiiRemote::isAccelerometerEnabled() const {
  return WIIUSE_USING_ACC(wiimote);
}

void WiiRemote::setAccelerometerEnabled(bool isUsing) {
  bool current = isAccelerometerEnabled();

  if (isUsing != current) {

    wiiuse_motion_sensing(wiimote, isUsing);

    emit accelerometerEnabledChanged(isUsing);
  }
}

bool WiiRemote::isRumbleEnabled() const {
  return false; // TODO: Fix
}

void WiiRemote::setRumbleEnabled(bool isUsing) {
//  bool current = isRumbleEnabled();

//  if (isUsing != current) {
//    wiimote->to(isUsing ? CWiimote::ON : CWiimote::OFF);

//    rumbleEnabledChanged(isUsing);
//  }
  // TODO
}

bool WiiRemote::isMotionPlusEnabled() const {
  return WIIUSE_USING_EXP(wiimote) && (wiimote->exp.type == EXP_MOTION_PLUS);
}

void WiiRemote::setMotionPlusEnabled(bool isUsing) {
  bool current = isMotionPlusEnabled();

  if (isUsing != current) {
    wiiuse_set_motion_plus(wiimote, isUsing); // TODO: isUsing should really be an int, because of nunchuck passthrough

    emit motionPlusEnabledChanged(isUsing);
  }
}

bool WiiRemote::isSmoothingEnabled() const {
  //return wiimote.GetFlags() & WIIC_SMOOTHING;
  return false; // TODO
}

void WiiRemote::setSmoothingEnabled(bool isUsing) {
//  bool current = isSmoothingEnabled();

//  if (isUsing != current) {
//    wiimote.SetSmoothing(isUsing);

//    smoothingEnabledChanged(isUsing);
//  }
 // TODO
}

int WiiRemote::getId() const {
  return WIIMOTE_ID(this->wiimote);
}

QString WiiRemote::getAddress() const {
//  return QString(wiimote.GetAddress());
  return ""; // TODO
}

float WiiRemote::getBattery() const {
  // TODO: Detect whether or not this has *really* changed
  return wiimote->battery_level;
}
}
