#include <QGuiApplication>
#include <QQuickView>

#include "input/WiiRemote.hpp"
#include "input/Wii.hpp"

// Second, define the singleton type provider function (callback).
static QObject *wii_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new wii::Wii();
}

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
