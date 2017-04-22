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

#define CHECK_WIIMOTE_BUTTONS(lowername, uppername) \
  do { \
    if (IS_JUST_PRESSED(wiimote, Button::uppername)) { \
      emit lowername##HeldChanged(); \
      emit buttonPressed(Button::uppername); \
      emit lowername##Pressed(); \
    } \
    else if (IS_RELEASED(wiimote, Button::uppername)) { \
      emit lowername##HeldChanged(); \
      emit buttonReleased(Button::uppername); \
      emit lowername##Released(); \
    } \
  } while (false) \

void WiiRemote::update() {
  emit batteryChanged();

  Accelerometer* accelerometer = this->getAccelerometer();

  emit accelerometer->gravityChanged();
  emit accelerometer->orientationChanged();
  emit accelerometer->gravityRawChanged();
  accelerometer->updateFilters();

  CHECK_WIIMOTE_BUTTONS(two, Two);
  CHECK_WIIMOTE_BUTTONS(one, One);
  CHECK_WIIMOTE_BUTTONS(b, B);
  CHECK_WIIMOTE_BUTTONS(a, A);
  CHECK_WIIMOTE_BUTTONS(minus, Minus);
  CHECK_WIIMOTE_BUTTONS(home, Home);
  CHECK_WIIMOTE_BUTTONS(left, Left);
  CHECK_WIIMOTE_BUTTONS(right, Right);
  CHECK_WIIMOTE_BUTTONS(up, Up);
  CHECK_WIIMOTE_BUTTONS(down, Down);
  CHECK_WIIMOTE_BUTTONS(plus, Plus);
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

bool WiiRemote::isButtonHeld(Button button) const {
  return IS_HELD(wiimote, button);
}

bool WiiRemote::isTwoHeld() const {
  return isButtonHeld(Button::Two);
}

bool WiiRemote::isOneHeld() const {
  return isButtonHeld(Button::One);
}

bool WiiRemote::isBHeld() const {
  return isButtonHeld(Button::B);
}

bool WiiRemote::isAHeld() const {
  return isButtonHeld(Button::A);
}

bool WiiRemote::isMinusHeld() const {
  return isButtonHeld(Button::Minus);
}

bool WiiRemote::isHomeHeld() const {
  return isButtonHeld(Button::Home);
}

bool WiiRemote::isLeftHeld() const {
  return isButtonHeld(Button::Left);
}

bool WiiRemote::isRightHeld() const {
  return isButtonHeld(Button::Right);
}

bool WiiRemote::isUpHeld() const {
  return isButtonHeld(Button::Up);
}

bool WiiRemote::isDownHeld() const {
  return isButtonHeld(Button::Down);
}

bool WiiRemote::isPlusHeld() const {
  return isButtonHeld(Button::Plus);
}

}
