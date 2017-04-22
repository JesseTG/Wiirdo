#include <QCoreApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QtDebug>
#include <QTimer>
#include <QSharedPointer>

#include <GRT/DataStructures/Vector.h>
#include <GRT/DataStructures/TimeSeriesClassificationData.h>

#include "input/Wii.hpp"

constexpr unsigned int NUM_DIMENSIONS = 9;

using namespace wii;

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);
  app.setApplicationName("Wiirdo-Record");
  app.setApplicationVersion("0.1");
  QCommandLineParser parser;
  parser.setApplicationDescription(
    "Record gesture data for a Wii Remote, preparing it for use with Wiirdo-Train.\n"
    "Further instructions are provided once a Wii Remote is successfully connected.\n\n"
    "Each data file will be considered to represent one gesture, but you can (and should)\n"
    "record this gesture multiple times."
  );
  parser.addHelpOption();
  parser.addVersionOption();
  // clang-format off
  parser.addOptions({
    {
      {"n", "name"},
      "Name to give the data set (defaults to the filename). Use this to name the gesture. There should not be any spaces.",
      "gesture-name"
    },
    {
      {"o", "output"},
      "File to save the output to (will not overwrite existing files). Required. *.csv extension "
        "will output a CSV file, anything else will output a GRT-format file.",
      "path"
    },
    {
      {"i", "info"},
      "Extra info about this data. Use this to describe a gesture.",
      "description"
    },
    {
      {"s", "sample-interval"},
      "Sampling interval for the raw data. Smaller numbers means more samples and more CPU usage. Defaults to 8ms",
      "milliseconds",
      "8"
    }
    // TODO: Add polling rate
  });
  // clang-format on


  parser.process(app);

  if (!parser.isSet("output")) {
    parser.showHelp(2);
  }

  qInfo() << "Searching for a Wii Remote...";

  const QString path = parser.value("output");
  const QString name = parser.value(parser.isSet("name") ? "name" : "output");
  if (QFile::exists(path)) {
    qCritical() << "Will not overwrite existing file" << path;
    app.exit(2);
  }

  bool ok = true;
  QSharedPointer<bool> recording = QSharedPointer<bool>::create(false);
  QSharedPointer<QTimer> timer = QSharedPointer<QTimer>::create();
  QSharedPointer<Wii> wii = QSharedPointer<Wii>::create();
  QSharedPointer<GRT::MatrixDouble> sample = QSharedPointer<GRT::MatrixDouble>::create();
  GRT::UINT nameHash = qHash(name, 1);
  // I dunno of the default of 0 means "use 0 as the seed" or "use the global seed". Best to play it safe
  unsigned int sampleInterval = parser.value("sample-interval").toUInt(&ok);

  if (!ok) {
    qCritical() << "--sample-interval expects a valid positive integer, got" << parser.value("sample-interval");
    app.exit(2);
  }

  QSharedPointer<GRT::TimeSeriesClassificationData> data = QSharedPointer<GRT::TimeSeriesClassificationData>::create(
    NUM_DIMENSIONS,
    name.toStdString(),
    parser.value("info").toStdString()
  );
  data->setAllowNullGestureClass(false);

  QObject::connect(wii.data(), &Wii::connectionSucceeded, [sampleInterval, timer, wii, recording, sample, nameHash, data, path, name, &app]() {
    const QList<WiiRemote*>& wiimotes = wii->getWiimotesCpp();
    WiiRemote* wiimote = wiimotes[0];
    Accelerometer* accelerometer = wiimote->getAccelerometer();

    QObject::connect(timer.data(), &QTimer::timeout, [wii, recording, sample, accelerometer]() {
      wii->poll();

      if (*recording) {
        GRT::VectorDouble instant(NUM_DIMENSIONS, 0.0);
        QVector3D gravity = accelerometer->getGravity();
        QVector3D gravityRaw = accelerometer->getGravityRaw();
        QVector3D orientation = accelerometer->getOrientation();

        instant[0] = gravity.x();
        instant[1] = gravity.y();
        instant[2] = gravity.z();
        instant[3] = gravityRaw.x();
        instant[4] = gravityRaw.y();
        instant[5] = gravityRaw.z();
        instant[6] = orientation.x();
        instant[7] = orientation.y();
        instant[8] = orientation.z();

        if (!sample->push_back(instant)) {
          qWarning() << "Failed to append instant" << instant << "to sample";
        }
      }
    });

    QObject::connect(wiimote, &WiiRemote::aPressed, [recording, data]() {
      if (!*recording) {
        qInfo() << "[" << data->getNumSamples() << "] Move or swing the Wii Remote to record a sample, then release A to confirm it.";
        *recording = true;
      }
    });

    QObject::connect(wiimote, &WiiRemote::aReleased, [recording, path, sample, data, nameHash]() {
      if (*recording) {
        *recording = false;

        if (data->addSample(nameHash, *sample)) {
          qInfo() << "[" << data->getNumSamples() - 1 << "] Added a sample";
        }

        if (!sample->clear()) {
          qWarning() << "Failed to clear sample matrix";
        }
      }
    });

    QObject::connect(wiimote, &WiiRemote::homePressed, [&path, &recording, &data, &app, &timer]() {
      *recording = false;
      timer->stop();

      if (data->saveDatasetToFile(path.toStdString())) {
        qInfo() << "Recorded" << data->getNumSamples() << "samples to" << path;
        app.exit(0);
      }
      else {
        qCritical() << "Failed to save" << data->getNumSamples() << "to" << path;
        app.exit(1);
      }
    });

    qInfo() << "Press and hold the A button to begin recording a gesture";
    qInfo() << "Press the Home button to quit recording and save the data.";
    qInfo() << "Sample interval is" << sampleInterval << "milliseconds.";
    timer->start(sampleInterval);
  });

  QObject::connect(wii.data(), &Wii::connectionFailed, [&wii, &app]() {
    qCritical() << "Failed to find any Wii Remotes.  Exiting.";

    app.exit(1);
  });

  QObject::connect(&app, &QCoreApplication::aboutToQuit, [&]() {
    // Do any clean-up here
  });

  wii->findAndConnect(5, true, true);



  // take arg on command line for gesture file name
  // look for wiimote
  // hold a
  // make gesture
    // save data in a csv
  // release a
  return app.exec();
}
