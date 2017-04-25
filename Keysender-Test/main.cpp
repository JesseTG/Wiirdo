#include <QCoreApplication>
#include <QCommandLineParser>
#include <QKeySequence>
#include <QtDebug>
#include <QKeyEvent>

#include "Keysender.hpp"

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);
  app.setApplicationName("Keysender-Test");
  app.setApplicationVersion("0.1");
  QCommandLineParser parser;
  parser.setApplicationDescription(
    "TODO"
  );
  parser.addHelpOption();
  parser.addVersionOption();

  parser.process(app);


  QStringList sequences = parser.positionalArguments();
  if (sequences.empty()) {
    parser.showHelp(1);
  }

  wiirdo::Keysender keysender;


  for (const QString& s : sequences) {
    QKeySequence sequence(s);
    qInfo() << sequence;

    for (int i = 0; i < sequence.count(); ++i) {
      keysender.send(QKeyEvent(QKeyEvent::KeyPress, sequence[i], 0));
      keysender.send(QKeyEvent(QKeyEvent::KeyRelease, sequence[i], 0));
    }
  }

  return 0;
}
