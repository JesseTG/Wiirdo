#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QtDebug>

#include <GRT/ClassificationModules/DTW/DTW.h>
#include <GRT/DataStructures/TimeSeriesClassificationData.h>

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);
  app.setApplicationName("Wiirdo-Train");
  app.setApplicationVersion("0.1");
  QCommandLineParser parser;
  parser.addHelpOption();
  parser.addVersionOption();

  // clang-format off
  parser.addOptions({
      {
        {"s", "scaling"},
        "Enables the scaling of training and prediction data to a specific range."
      },
      {
        {"n", "null-rejection"},
        "Enables the usage of null rejection for realtime prediction. In this case "
          "the predicted class label will be set to 0 (the default null label) "
          "if the distance between the input vector and the closest template is greater "
          "than the null rejection threshold for the top predicted class. The null "
          "rejection threshold is computed for each class during the training phase."
      },
      {
        {"c", "null-rejection-coefficient"},
        "Sets the multipler that controls the null rejection threshold for each class. "
          "Requires --null-rejection. (Default: 3.0)",
        "coefficient",
        "3.0"
      },
      {
        {"m", "rejection-mode"},
        "Sets the null rejection method. Must be one of TEMPLATE_THRESHOLDS, "
          "CLASS_LIKELIHOODS or THRESHOLDS_AND_LIKELIHOODS. (Default: TEMPLATE_THRESHOLDS)",
        "mode",
        "TEMPLATE_THRESHOLDS"
      },
      {
        {"d", "no-dtw-constrain"},
        "Disables the DTW warping path should be constrained within a specific distance "
          "from the main radius of the cost matrix."
      },
      {
        {"r", "radius"},
        "Sets the warping path radius. Must be between 0 and 1. (Default: 0.2)",
        "rad",
        "0.2"
      },
      {
        {"o", "offset-using-first-sample"},
        "Offsets each time series by the first sample.",
      },
      {
        {"f", "smoothing"},
        "Enables the averaging and downsampling of the input time series."
      },
      {
        {"i", "smoothing-factor"},
         "Controls the amount of downsampling. Requires --smoothing. (Default: 5)",
         "factor",
         "5"
      },
      {
        {"l", "null-rejection-likelihood"},
        "Sets the null rejection threshold. Requires --rejection-mode to be "
          "CLASS_LIKELIHOODS or THRESHOLDS_AND_LIKELIHOODS. (Default: 0.99)",
        "threshold",
        "0.99"
      },
      {
        {"t", "trim"},
        "Trim extra data from both ends of the time series (e.g. if the user held still for a few seconds before or after recording"
      },
      {
        {"u", "trim-threshold"},
        "Threshold at which the data should be trimmed. Must be between 0 and 1. Requires --trim. (Default: 0.1)",
        "threshold",
        "0.1"
      },
      {
        {"p", "max-trim-percent"},
        "Maximum amount of data that can be trimmed for one sample. Must be between 0 and 100. Requires --trim. (Default: 90)",
        "percent",
        "90"
      }
  });
  // clang-format on

  parser.addPositionalArgument("input", "File to load",
                               "<paths>");

  parser.addPositionalArgument(
      "output",
      "File to save the output to (will not overwrite existing files). ",
      "<path>");

  parser.process(app);

  bool ok = true;
  bool useScaling = parser.isSet("scaling");
  bool useNullRejection = parser.isSet("null-rejection");
  double nullRejectionCoeff = parser.value("null-rejection-coefficient").toDouble(&ok);

  if (!ok) {
    qCritical() << parser.value("null-rejection-coefficient") << "cannot be parsed as a number";
    parser.showHelp(1);
  }

  QString rejectionModeString = parser.value("rejection-mode").toUpper();
  int rejectionMode = GRT::DTW::TEMPLATE_THRESHOLDS;
  if (rejectionModeString == "TEMPLATE_THRESHOLDS") {
    rejectionMode = GRT::DTW::TEMPLATE_THRESHOLDS;
  }
  else if (rejectionModeString == "CLASS_LIKELIHOODS") {
    rejectionMode = GRT::DTW::CLASS_LIKELIHOODS;
  }
  else if (rejectionModeString == "THRESHOLDS_AND_LIKELIHOODS") {
    rejectionMode = GRT::DTW::THRESHOLDS_AND_LIKELIHOODS;
  }
  else {
    parser.showHelp(1);
  }

  bool dtwConstrain = !parser.isSet("no-dtw-constrain");
  double radius = parser.value("radius").toDouble(&ok);

  if (!ok) {
    qCritical() << parser.value("radius") << "cannot be parsed as a number";
    parser.showHelp(1);
  }
  else if (radius < 0 || radius > 1) {
    qCritical() << "Radius must be between 0 and 1";
    parser.showHelp(1);
  }

  bool offsetUsingFirstSample = parser.isSet("offset-using-first-sample");
  bool useSmoothing = parser.isSet("smoothing");
  unsigned int smoothingFactor = parser.value("smoothing-factor").toUInt(&ok, 10);

  if (!ok) {
    qCritical() << parser.value("smoothing-factor") << "cannot be parsed as an unsigned integer";
    parser.showHelp(1);
  }

  double nullRejectionLikelihoodThreshold =
      parser.value("null-rejection-likelihood").toDouble(&ok);

  if (!ok) {
    qCritical() << parser.value("null-rejection-likelihood") << "cannot be parsed as a number";
    parser.showHelp(1);
  }

  QStringList paths = parser.positionalArguments();

  if (paths.length() < 2) {
    qCritical() << "Must provide an input and an output";
    parser.showHelp(1);
  }

  const QString& input = paths[0];
  const QString& output = paths[1];

  bool trimTrainingData = parser.isSet("trim");
  double trimThreshold = parser.value("trim-threshold").toDouble(&ok);
  if (!ok || trimThreshold < 0 || trimThreshold > 1) {
    qCritical() << parser.value("trim-threshold") << "is not a value between 0 and 1";
    parser.showHelp(1);
  }

  double maximumTrimPercentage = parser.value("max-trim-percent").toDouble(&ok);
  if (!ok || maximumTrimPercentage < 0 || maximumTrimPercentage > 100) {
    qCritical() << parser.value("max-trim-percent") << "is not a value between 0 and 100";
    parser.showHelp(1);
  }

  GRT::TimeSeriesClassificationData data(3, "test", "description");

  if (!data.load(input.toStdString())) {
    qCritical() << "Failed to load" << input;
    return 2;
  }

  GRT::DTW classifier(useScaling, useNullRejection, nullRejectionCoeff, 0,
                      dtwConstrain, radius, offsetUsingFirstSample,
                      useSmoothing, smoothingFactor,
                      nullRejectionLikelihoodThreshold);

  classifier.enableTrimTrainingData(trimTrainingData, trimThreshold, maximumTrimPercentage);

  if (!classifier.train(data) ){
      qCritical() << "Failed to train classifier with data loaded from" << input;
      return 2;
  }

  if (!classifier.save(output.toStdString())){
      qCritical() << "Failed to save classifier model to" << output;
      return 2;
  }

  return 0;
}
