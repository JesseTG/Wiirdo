#include "Accelerometer.hpp"

namespace wii {

Accelerometer::Accelerometer(const CAccelerometer& _accelerometer, QObject *parent) :
  QObject(parent),
  accelerometer(_accelerometer)
{

}

float Accelerometer::getOrientationThreshold() {
  return accelerometer.GetOrientThreshold();
}

void Accelerometer::setOrientationThreshold(float threshold) {
  accelerometer.SetOrientThreshold(threshold);

  orientationThresholdChanged(threshold);
}

int Accelerometer::getAccelerationThreshold() {
  return accelerometer.GetAccelThreshold();
}

void Accelerometer::setAccelerationThreshold(int threshold) {
  accelerometer.SetAccelThreshold(threshold);

  accelerationThresholdChanged(threshold);
}

QVector3D Accelerometer::getGravityCalibration() {
  QVector3D gravityCalibrated;

  accelerometer.GetGravityCalVector(gravityCalibrated[0], gravityCalibrated[1], gravityCalibrated[2]);

  return gravityCalibrated;
}

void Accelerometer::setGravityCalibration(const QVector3D& calibration) {
  accelerometer.SetGravityCalVector(calibration.x(), calibration.y(), calibration.z());

  gravityCalibrationChanged(calibration);
}

QVector3D Accelerometer::getOrientation() {
  QVector3D orientation;
  accelerometer.GetOrientation(orientation[0], orientation[1], orientation[2]);
  return orientation;
}

QVector3D Accelerometer::getGravity() {
  QVector3D gravity;

  accelerometer.GetGravityVector(gravity[0], gravity[1], gravity[2]);
  return gravity;
}

QVector3D Accelerometer::getGravityRaw() {
  QVector3D gravityRaw;

  accelerometer.GetRawGravityVector(gravityRaw[0], gravityRaw[1], gravityRaw[2]);
  return gravityRaw;
}
}
