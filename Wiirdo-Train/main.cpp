#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QtDebug>
#include <QFile>

#include <GRT/ClassificationModules/DTW/DTW.h>
#include <GRT/DataStructures/TimeSeriesClassificationData.h>

constexpr unsigned int NUM_DIMENSIONS = 9;

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);
  app.setApplicationName("Wiirdo-Train");
  app.setApplicationVersion("0.1");

  /// Set up command-line options //////////////////////////////////////////////////////////////////////////////////////
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

  parser.addPositionalArgument(
    "inputs",
    "Files to load",
    "<path>..."
  );

  parser.addPositionalArgument(
      "output",
      "File to save the output to (will not overwrite existing files). ",
      "<path>"
  );

  parser.process(app);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /// Parse the simple boolean options /////////////////////////////////////////////////////////////////////////////////
  bool useScaling = parser.isSet("scaling");
  bool useNullRejection = parser.isSet("null-rejection");
  bool dtwConstrain = !parser.isSet("no-dtw-constrain");
  bool offsetUsingFirstSample = parser.isSet("offset-using-first-sample");
  bool useSmoothing = parser.isSet("smoothing");
  bool trimTrainingData = parser.isSet("trim");
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /// Null Rejection Coefficient ///////////////////////////////////////////////////////////////////////////////////////
  bool ok = true;
  double nullRejectionCoeff = parser.value("null-rejection-coefficient").toDouble(&ok);

  if (!ok) {
    qCritical() << parser.value("null-rejection-coefficient") << "cannot be parsed as a number";
    parser.showHelp(1);
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /// Rejection Mode ///////////////////////////////////////////////////////////////////////////////////////////////////
  QString rejectionModeString = parser.value("rejection-mode").toUpper();
  GRT::UINT rejectionMode = GRT::DTW::TEMPLATE_THRESHOLDS;
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
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /// Radius ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  double radius = parser.value("radius").toDouble(&ok);

  if (!ok || radius < 0 || radius > 1) {
    qCritical() << "Radius must be between 0 and 1, but received" << parser.value("radius");
    parser.showHelp(1);
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /// Smoothing Factor /////////////////////////////////////////////////////////////////////////////////////////////////
  unsigned int smoothingFactor = parser.value("smoothing-factor").toUInt(&ok, 10);

  if (!ok) {
    qCritical() << parser.value("smoothing-factor") << "cannot be parsed as an unsigned integer";
    parser.showHelp(1);
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /// Null Rejection Likelihood Threshold //////////////////////////////////////////////////////////////////////////////
  double nullRejectionLikelihoodThreshold =
      parser.value("null-rejection-likelihood").toDouble(&ok);

  if (!ok) {
    qCritical() << parser.value("null-rejection-likelihood") << "cannot be parsed as a number";
    parser.showHelp(1);
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /// Trim Values //////////////////////////////////////////////////////////////////////////////////////////////////////
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
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /// Load the actual data /////////////////////////////////////////////////////////////////////////////////////////////
  QStringList paths = parser.positionalArguments();

  if (paths.length() < 2) {
    qCritical() << "Must provide one or more inputs and one output";
    parser.showHelp(1);
  }

  const QString& output = paths.last();

  if (QFile::exists(output)) {
    qCritical() << "File" << output << "exists, will not overwrite it.";
    return 2;
  }

  GRT::TimeSeriesClassificationData allData;
  allData.setAllowNullGestureClass(false);
  allData.setNumDimensions(NUM_DIMENSIONS);

  for (int i = 0; i < paths.length() - 1; ++i) {
    // For each given input... (all pathnames except the last are inputs; the last is the output)

    GRT::TimeSeriesClassificationData data;
    const QString& input = paths[i];

    if (data.load(input.toStdString())) {
      qInfo() << "Loaded data file" << input;
    }
    else {
      qCritical() << "Failed to load" << input;
      return 2;
    }

    if (allData.merge(data)) {
      qInfo() << "Merged data file" << input;
    }
    else {
      qCritical() << "Failed to merge" << input << "into common data set";
      return 2;
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  GRT::DTW classifier(
    useScaling,
    useNullRejection,
    nullRejectionCoeff,
    rejectionMode,
    dtwConstrain,
    radius,
    offsetUsingFirstSample,
    useSmoothing,
    smoothingFactor,
    nullRejectionLikelihoodThreshold
  );
  // TODO: There are some other options in the base class, use those too

  if (!classifier.enableTrimTrainingData(trimTrainingData, trimThreshold, maximumTrimPercentage)) {
    qCritical() << "Failed to set trim parameters for training data";
    return 2;
  }

  if (!classifier.train(allData)) {
    qCritical() << "Failed to train classifier with data loaded from" << paths;
    return 2;
  }

  if (classifier.save(output.toStdString())) {
    qInfo() << "Saved classifier model to" << output;
  }
  else {
    qCritical() << "Failed to save classifier model to" << output;
    return 2;
  }

  return 0;
}
