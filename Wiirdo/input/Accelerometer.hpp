#ifndef ACCELEROMETER_HPP
#define ACCELEROMETER_HPP

#include <QObject>
#include <QVector3D>

#include <wiiuse.h>
#include <QDebug>

namespace wii {

class Accelerometer : public QObject
{
  Q_OBJECT

  Q_PROPERTY(float orientationThreshold READ getOrientationThreshold WRITE setOrientationThreshold NOTIFY orientationThresholdChanged)
  Q_PROPERTY(int accelerationThreshold READ getAccelerationThreshold WRITE setAccelerationThreshold NOTIFY accelerationThresholdChanged)
  Q_PROPERTY(QVector3D gravityCalibration READ getGravityCalibration WRITE setGravityCalibration NOTIFY gravityCalibrationChanged)
  Q_PROPERTY(QVector3D orientation READ getOrientation NOTIFY orientationChanged)
  Q_PROPERTY(QVector3D gravity READ getGravity NOTIFY gravityChanged)
  Q_PROPERTY(QVector3D gravityRaw READ getGravityRaw NOTIFY gravityRawChanged)

public:
  explicit Accelerometer(const accel_t*, const orient_t*, const gforce_t*, const float*, const int*, const vec3b_t*, QObject *parent = nullptr);
  Accelerometer(const Accelerometer& other) = delete;
  Accelerometer& operator=(const Accelerometer& other) = delete;
  Accelerometer() = delete;

  void updateFilters();
  float getOrientationThreshold() const;
  void setOrientationThreshold(float threshold);

  int getAccelerationThreshold() const;
  void setAccelerationThreshold(int threshold);

  QVector3D getGravityCalibration() const;
  void setGravityCalibration(const QVector3D& calibration);

  QVector3D getOrientation() const;
  QVector3D getGravity() const;
  QVector3D getGravityRaw() const;

signals:
  void orientationThresholdChanged(float threshold);
  void accelerationThresholdChanged(int threshold);
  void gravityCalibrationChanged(const QVector3D& calibration);
  void orientationChanged();
  void gravityChanged();
  void gravityRawChanged();

public slots:
private:
  const accel_t* _accel_calib;
  const orient_t* _orient;
  const gforce_t* _gforce;
  const float* _orientThreshold;
  const int* _accelThreshold;
  const vec3b_t* _accel;
};

}
#endif // ACCELEROMETER_HPP
