#include <QCoreApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QtDebug>
#include <QTimer>

#include <GRT/DataStructures/TimeSeriesClassificationData.h>

#include "input/Wii.hpp"

using namespace wii;

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);
  app.setApplicationName("Wiirdo-Record");
  app.setApplicationVersion("0.1");
  QCommandLineParser parser;
  parser.setApplicationDescription(
    "Record gesture data for a Wii Remote, preparing it for use with Wiirdo-Train.\n"
    "Further instructions are provided once a Wii Remote is successfully connected."
  );
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument(
    "output",
    "File to save the output to (will not overwrite existing files). "
    "Paths beyond the first are ignored.",
    "<path>"
  );

  parser.process(app);

  if (parser.positionalArguments().empty()) {
    parser.showHelp(2);
  }

  qInfo() << "Searching for a Wii Remote...";

  Wii wii;
  QTimer timer;

  QObject::connect(&timer, &QTimer::timeout, [&wii]() {
    wii.poll();

    const QList<WiiRemote*>& wiimotes = wii.getWiimotesCpp();
    WiiRemote* wiimote = wiimotes[0];
    Accelerometer* accelerometer;
  });

  QObject::connect(&wii, &Wii::connectionSucceeded, [&wii]() {
    const QList<WiiRemote*>& wiimotes = wii.getWiimotesCpp();

    WiiRemote* wiimote = wiimotes[0];

  });

  QObject::connect(&wii, &Wii::connectionFailed, [&wii, &app]() {
    qCritical() << "Failed to find any Wii Remotes.  Exiting.";

    app.exit(1);
  });

  wii.findAndConnect(5, true, true);


  // take arg on command line for gesture file name
  // look for wiimote
  // hold a
  // make gesture
    // save data in a csv
  // release a
  return app.exec();
}
