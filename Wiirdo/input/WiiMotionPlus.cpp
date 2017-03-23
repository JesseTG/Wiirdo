#include "WiiMotionPlus.hpp"

#include <QVector3D>

namespace wii {


WiiMotionPlus::WiiMotionPlus(motion_plus_t* mp, QObject *parent) :
    QObject(parent),
    _mp(mp)
{

}

void WiiMotionPlus::calibrate() {
  // TODO
}

int WiiMotionPlus::getGyroscopeThreshold() {
  return _mp->raw_gyro_threshold;
}

void WiiMotionPlus::setGyroscopeThreshold(int threshold) {
  _mp->raw_gyro_threshold = threshold;

  gyroscopeThresholdChanged(threshold);
}

QVector3D WiiMotionPlus::getRates() {
  return QVector3D(_mp->angle_rate_gyro.pitch, _mp->angle_rate_gyro.roll, _mp->angle_rate_gyro.yaw);
}

QVector3D WiiMotionPlus::getRawRates() {
  return QVector3D(_mp->raw_gyro.pitch, _mp->raw_gyro.roll, _mp->raw_gyro.yaw);
}
}
