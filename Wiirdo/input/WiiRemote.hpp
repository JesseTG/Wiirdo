#ifndef WIIREMOTE_HPP
#define WIIREMOTE_HPP

#include <QObject>
#include <QQmlListProperty>

#include <wiiuse.h>
#include "input/Accelerometer.hpp"
#include "input/WiiMotionPlus.hpp"

namespace wii {
class WiiRemote : public QObject
{
  Q_OBJECT

  Q_PROPERTY(Accelerometer* accelerometer READ getAccelerometer NOTIFY accelerometerChanged)
  Q_PROPERTY(WiiMotionPlus* motionPlus READ getMotionPlus NOTIFY motionPlusChanged)
  Q_PROPERTY(bool accelerometerEnabled READ isAccelerometerEnabled WRITE setAccelerometerEnabled NOTIFY accelerometerEnabledChanged)
  Q_PROPERTY(bool rumbleEnabled READ isRumbleEnabled WRITE setRumbleEnabled NOTIFY rumbleEnabledChanged)
  Q_PROPERTY(bool motionPlusEnabled READ isMotionPlusEnabled WRITE setMotionPlusEnabled NOTIFY motionPlusEnabledChanged)
  Q_PROPERTY(bool smoothingEnabled READ isSmoothingEnabled WRITE setSmoothingEnabled NOTIFY smoothingEnabledChanged)
  Q_PROPERTY(int id READ getId CONSTANT)
  Q_PROPERTY(QString address READ getAddress CONSTANT)
  Q_PROPERTY(float battery READ getBattery NOTIFY batteryChanged)

public:
  explicit WiiRemote(wiimote_t* w, QObject *parent = 0);
  WiiRemote(const WiiRemote& other) = delete;
  WiiRemote& operator=(const WiiRemote& other) = delete;
  WiiRemote() = delete;
  virtual ~WiiRemote();
  void update();

  enum Button {
    Two = WIIMOTE_BUTTON_TWO,
    One = WIIMOTE_BUTTON_ONE,
    B = WIIMOTE_BUTTON_B,
    A = WIIMOTE_BUTTON_A,
    Minus = WIIMOTE_BUTTON_MINUS,
    Home = WIIMOTE_BUTTON_HOME,
    Left = WIIMOTE_BUTTON_LEFT,
    Right = WIIMOTE_BUTTON_RIGHT,
    Down = WIIMOTE_BUTTON_DOWN,
    Up = WIIMOTE_BUTTON_UP,
    Plus = WIIMOTE_BUTTON_PLUS,
    Unknown = WIIMOTE_BUTTON_UNKNOWN,
    All = WIIMOTE_BUTTON_ALL,
  };
  Q_ENUM(Button)


signals:
  void accelerometerChanged();
  void motionPlusChanged();
  void accelerometerEnabledChanged(bool);
  void rumbleEnabledChanged(bool);
  void motionPlusEnabledChanged(bool);
  void smoothingEnabledChanged(bool);
  void batteryChanged();

public slots:

public:
  Accelerometer* getAccelerometer() { return &accelerometer; }
  WiiMotionPlus* getMotionPlus() { return motionPlus; }

  bool isAccelerometerEnabled();
  void setAccelerometerEnabled(bool);

  bool isRumbleEnabled();
  void setRumbleEnabled(bool);

  bool isMotionPlusEnabled();
  void setMotionPlusEnabled(bool);

  bool isSmoothingEnabled();
  void setSmoothingEnabled(bool);

  int getId();
  QString getAddress();
  float getBattery();
private:
  wiimote_t* wiimote;
  Accelerometer accelerometer;
  WiiMotionPlus* motionPlus;
};
}
#endif // WIIREMOTE_HPP
