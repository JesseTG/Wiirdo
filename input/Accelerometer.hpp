#ifndef ACCELEROMETER_HPP
#define ACCELEROMETER_HPP

#include <QObject>
#include <QVector3D>

#include <wiic/wiicpp.h>
#include <QDebug>

namespace wii {

class Accelerometer : public QObject
{
  Q_OBJECT

  Q_PROPERTY(float orientationThreshold READ getOrientationThreshold WRITE setOrientationThreshold NOTIFY orientationThresholdChanged)
  Q_PROPERTY(float accelerationThreshold READ getAccelerationThreshold WRITE setAccelerationThreshold NOTIFY accelerationThresholdChanged)
  Q_PROPERTY(QVector3D gravityCalibration READ getGravityCalibration WRITE setGravityCalibration NOTIFY gravityCalibrationChanged)
  Q_PROPERTY(QVector3D orientation READ getOrientation NOTIFY orientationChanged)
  Q_PROPERTY(QVector3D gravity READ getGravity NOTIFY gravityChanged)
  Q_PROPERTY(QVector3D gravityRaw READ getGravityRaw NOTIFY gravityRawChanged)

public:
  explicit Accelerometer(const CAccelerometer& _accelerometer, QObject *parent = nullptr);

signals:
  void orientationThresholdChanged(float threshold);
  void accelerationThresholdChanged(int threshold);
  void gravityCalibrationChanged(const QVector3D& calibration);
  void orientationChanged();
  void gravityChanged();
  void gravityRawChanged();

public slots:
private:
  CAccelerometer accelerometer;

  float getOrientationThreshold();
  void setOrientationThreshold(float threshold);

  int getAccelerationThreshold();
  void setAccelerationThreshold(int threshold);

  QVector3D getGravityCalibration();
  void setGravityCalibration(const QVector3D& calibration);

  QVector3D getOrientation();
  QVector3D getGravity();
  QVector3D getGravityRaw();
};

}
#endif // ACCELEROMETER_HPP
