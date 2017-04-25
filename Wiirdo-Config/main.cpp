#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "input/WiiRemote.hpp"
#include "input/Wii.hpp"

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  qmlRegisterUncreatableType<wii::Accelerometer>("wii", 1, 0, "Accelerometer", "Please obtain an Accelerometer from a WiiRemote or a Nunchuck");
  qmlRegisterType<wii::Wii>("wii", 1, 0, "Wii");
  qmlRegisterUncreatableType<wii::WiiRemote>("wii", 1, 0, "WiiRemote", "Please use the Wii singleton to obtain a WiiRemote object");

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  return app.exec();
}
