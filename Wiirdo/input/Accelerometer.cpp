#include "Accelerometer.hpp"

namespace wii {

Accelerometer::Accelerometer(
    const accel_t* accel_calib,
    const orient_t* orient,
    const gforce_t* gforce,
    const float* ot,
    const int* at,
    const vec3b_t* accel,
    QObject *parent) :
  QObject(parent),
  _accel_calib(accel_calib),
  _orient(orient),
  _gforce(gforce),
  _orientThreshold(ot),
  _accelThreshold(at),
  _accel(accel)
{
}

void Accelerometer::updateFilters() {
}

float Accelerometer::getOrientationThreshold() const {
  return *_orientThreshold;
}

void Accelerometer::setOrientationThreshold(float threshold) {
  float current = getOrientationThreshold();

  if (qAbs(threshold - current) < 0.0001f) {
    *const_cast<float*>(_orientThreshold) = threshold;

    orientationThresholdChanged(threshold);
  }
}

int Accelerometer::getAccelerationThreshold() const {
  return *_accelThreshold;
}

void Accelerometer::setAccelerationThreshold(int threshold) {
  int current = getAccelerationThreshold();

  if (threshold != current) {
    *const_cast<int*>(_accelThreshold) = threshold;

    accelerationThresholdChanged(threshold);
  }
}

QVector3D Accelerometer::getGravityCalibration() const {
  return QVector3D(_accel_calib->cal_zero.x, _accel_calib->cal_zero.y, _accel_calib->cal_zero.z);
}

void Accelerometer::setGravityCalibration(const QVector3D& calibration) {
  QVector3D current = getGravityCalibration();

  if (calibration != current) {
    const_cast<accel_t*>(_accel_calib)->cal_zero.x = static_cast<byte>(calibration.x());
    const_cast<accel_t*>(_accel_calib)->cal_zero.y = static_cast<byte>(calibration.y());
    const_cast<accel_t*>(_accel_calib)->cal_zero.z = static_cast<byte>(calibration.z());

    gravityCalibrationChanged(calibration);
  }
}

QVector3D Accelerometer::getOrientation() const {
  return QVector3D(_orient->pitch, _orient->roll, _orient->yaw);
  // TODO: There are raw variants, too
}

QVector3D Accelerometer::getGravity() const {
  return QVector3D(_gforce->x, _gforce->y, _gforce->z);
}

QVector3D Accelerometer::getGravityRaw() const {
  return QVector3D(_accel->x, _accel->y, _accel->z);
}
}
