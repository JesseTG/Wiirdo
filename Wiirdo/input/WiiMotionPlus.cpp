#include "WiiMotionPlus.hpp"

#include <QVector3D>

namespace wii {


WiiMotionPlus::WiiMotionPlus(const CMotionPlus& mp, QObject *parent) :
    QObject(parent),
    motionPlus(mp)
{

}

void WiiMotionPlus::calibrate() {
  motionPlus.Gyroscope.Calibrate();
}

int WiiMotionPlus::getGyroscopeThreshold() {
  return motionPlus.Gyroscope.GetGyroThreshold();
}

void WiiMotionPlus::setGyroscopeThreshold(int threshold) {
  motionPlus.Gyroscope.SetGyroThreshold(threshold);

  gyroscopeThresholdChanged(threshold);
}

QVector3D WiiMotionPlus::getRates() {
  QVector3D rates;

  motionPlus.Gyroscope.GetRates(rates[0], rates[1], rates[2]);

  return rates;
}

QVector3D WiiMotionPlus::getRawRates() {
  std::array<int, 3> rawRates;

  motionPlus.Gyroscope.GetRawRates(rawRates[0], rawRates[1], rawRates[2]);

  return QVector3D(rawRates[0], rawRates[1], rawRates[2]);
}
}
