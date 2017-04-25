#include <QGuiApplication>
#include <QQuickView>
#include <QKeyEvent>

#include "input/WiiRemote.hpp"
#include "input/Wii.hpp"

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  QQuickView engine;

  qmlRegisterUncreatableType<wii::Accelerometer>("wii", 1, 0, "Accelerometer", "Please obtain an Accelerometer from a WiiRemote or a Nunchuck");
  qmlRegisterType<wii::Wii>("wii", 1, 0, "Wii");
  qmlRegisterUncreatableType<wii::WiiRemote>("wii", 1, 0, "WiiRemote", "Please use the Wii singleton to obtain a WiiRemote object");


  engine.resize(800, 600);
  engine.setResizeMode(QQuickView::SizeRootObjectToView);
  engine.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
  engine.show();

  return app.exec();
}
