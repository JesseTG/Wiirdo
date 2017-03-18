#ifndef WIIMOTIONPLUS_HPP
#define WIIMOTIONPLUS_HPP

#include <QObject>
#include <QVector3D>

#include <wiic/wiicpp.h>

namespace wii {

class WiiMotionPlus : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int gyroscopeThreshold READ getGyroscopeThreshold WRITE setGyroscopeThreshold NOTIFY gyroscopeThresholdChanged)
  Q_PROPERTY(QVector3D rates READ getRates NOTIFY ratesChanged)
  Q_PROPERTY(QVector3D rawRates READ getRawRates NOTIFY rawRatesChanged)

public:
  explicit WiiMotionPlus(const CMotionPlus& mp, QObject *parent = 0);

  int getGyroscopeThreshold();
  void setGyroscopeThreshold(int);
  QVector3D getRates();
  QVector3D getRawRates();

signals:
  void gyroscopeThresholdChanged(int);
  void ratesChanged();
  void rawRatesChanged();

public slots:
  void calibrate();

private:
  CMotionPlus motionPlus;

};
}

#endif // WIIMOTIONPLUS_HPP
