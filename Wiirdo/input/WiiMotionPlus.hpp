#ifndef WIIMOTIONPLUS_HPP
#define WIIMOTIONPLUS_HPP

#include <QObject>
#include <QVector3D>

#include <wiiuse.h>

namespace wii {

class WiiMotionPlus : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int gyroscopeThreshold READ getGyroscopeThreshold WRITE setGyroscopeThreshold NOTIFY gyroscopeThresholdChanged)
  Q_PROPERTY(QVector3D rates READ getRates NOTIFY ratesChanged)
  Q_PROPERTY(QVector3D rawRates READ getRawRates NOTIFY rawRatesChanged)

public:
  explicit WiiMotionPlus(motion_plus_t* mp, QObject *parent = 0);
  WiiMotionPlus() = delete;
  WiiMotionPlus& operator=(const WiiMotionPlus&) = delete;
  WiiMotionPlus(const WiiMotionPlus&) = delete;
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
  motion_plus_t* _mp;

};
}

#endif // WIIMOTIONPLUS_HPP
