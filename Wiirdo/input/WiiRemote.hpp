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

  Q_PROPERTY(bool twoHeld READ isTwoHeld NOTIFY twoHeldChanged)
  Q_PROPERTY(bool oneHeld READ isOneHeld NOTIFY oneHeldChanged)
  Q_PROPERTY(bool bHeld READ isBHeld NOTIFY bHeldChanged)
  Q_PROPERTY(bool aHeld READ isAHeld NOTIFY aHeldChanged)
  Q_PROPERTY(bool minusHeld READ isMinusHeld NOTIFY minusHeldChanged)
  Q_PROPERTY(bool homeHeld READ isHomeHeld NOTIFY homeHeldChanged)
  Q_PROPERTY(bool leftHeld READ isLeftHeld NOTIFY leftHeldChanged)
  Q_PROPERTY(bool rightHeld READ isRightHeld NOTIFY rightHeldChanged)
  Q_PROPERTY(bool upHeld READ isUpHeld NOTIFY upHeldChanged)
  Q_PROPERTY(bool downHeld READ isDownHeld NOTIFY downHeldChanged)
  Q_PROPERTY(bool plusHeld READ isPlusHeld NOTIFY plusHeldChanged)

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

  void buttonPressed(Button);
  void buttonReleased(Button);

  void twoPressed();
  void twoReleased();
  void twoHeldChanged();

  void onePressed();
  void oneReleased();
  void oneHeldChanged();

  void bPressed();
  void bReleased();
  void bHeldChanged();

  void aPressed();
  void aReleased();
  void aHeldChanged();

  void minusPressed();
  void minusReleased();
  void minusHeldChanged();

  void homePressed();
  void homeReleased();
  void homeHeldChanged();

  void leftPressed();
  void leftReleased();
  void leftHeldChanged();

  void rightPressed();
  void rightReleased();
  void rightHeldChanged();

  void upPressed();
  void upReleased();
  void upHeldChanged();

  void downPressed();
  void downReleased();
  void downHeldChanged();

  void plusPressed();
  void plusReleased();
  void plusHeldChanged();
public slots:

public:
  Accelerometer* getAccelerometer() { return &accelerometer; }
  const Accelerometer* getAccelerometer() const { return &accelerometer; }

  WiiMotionPlus* getMotionPlus() { return motionPlus; }
  const WiiMotionPlus* getMotionPlus() const { return motionPlus; }

  bool isAccelerometerEnabled() const;
  void setAccelerometerEnabled(bool);

  bool isRumbleEnabled() const;
  void setRumbleEnabled(bool);

  bool isMotionPlusEnabled() const;
  void setMotionPlusEnabled(bool);

  bool isSmoothingEnabled() const;
  void setSmoothingEnabled(bool);

  bool isButtonHeld(Button) const;
  bool isTwoHeld() const;
  bool isOneHeld() const;
  bool isBHeld() const;
  bool isAHeld() const;
  bool isMinusHeld() const;
  bool isHomeHeld() const;
  bool isLeftHeld() const;
  bool isRightHeld() const;
  bool isUpHeld() const;
  bool isDownHeld() const;
  bool isPlusHeld() const;

  int getId() const;
  QString getAddress() const;
  float getBattery() const;
private:
  wiimote_t* wiimote;
  Accelerometer accelerometer;
  WiiMotionPlus* motionPlus;
};
}
#endif // WIIREMOTE_HPP
