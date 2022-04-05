#include <QCoreApplication>

#include <iostream>
#include <QCommandLineParser>
#include <QVariantMap>
#include <QDebug>

#include <configfilereader.h>
#include <htmlwriter.h>
#include "exceptions.h"
#include "globals.h"


const QString defaultConfigFileName("config.txt");
const QString defaultHtmlFileName("colored_rects.html");



void parseCommandLine(QCommandLineParser &parser, QVariantMap& configMap){
    parser.setApplicationDescription("DrawRect:Application for creating html file with table of colored rectangles");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOptions({
              {{"p","configfilepath"},
                  QCoreApplication::translate("main", "<path> to config file"),
                  QCoreApplication::translate("main", "path")},
              {{"c","color"},
                  QCoreApplication::translate("main", "<color> of rectangle. Accepted values: red,green,blue"),
                  QCoreApplication::translate("main", "color")},
              {{"g","grid"},
                  QCoreApplication::translate("main", "Show grid")}
              });
    if(!parser.parse(QCoreApplication::arguments()))
    {
        throw SYS::Error("Parser error");
    }
    if (parser.isSet("version"))
    {
      parser.showVersion();
      return;
    }
    if (parser.isSet("help"))
    {
      parser.showHelp();
      return;
    }
    configMap["ConfigFilePath"] = parser.isSet("p") ? parser.value("p") : (QCoreApplication::applicationDirPath() + "/" + defaultConfigFileName);
    configMap["Color"] = parser.isSet("c") ? parser.value("c") : QString("blue");
    configMap["Grid"] = parser.isSet("g") ? QString("true") : QString("false");
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("DrawRect");
    QCoreApplication::setApplicationVersion("1.0");
    QCommandLineParser parser;
    QVariantMap cmdLineOptions;
    ConfigFileReader configFileReader;
    HtmlWriter htmlWriter;
    try
    {
        parseCommandLine(parser, cmdLineOptions);
        configFileReader.setFileName(cmdLineOptions["ConfigFilePath"].toString().toStdString());
        configFileReader.read();
        auto rects_points = configFileReader.getRectsPoints();
        htmlWriter.setFileName(defaultHtmlFileName.toStdString());
        htmlWriter.setRectsPoints(std::move(rects_points));
        htmlWriter.setMaxX(configFileReader.getMaxX());
        htmlWriter.setMaxY(configFileReader.getMaxY());
        htmlWriter.setRectColor(cmdLineOptions["Color"].toString().toStdString());
        htmlWriter.setShowGrid((cmdLineOptions["Grid"].toString().toStdString() == "true") ? true : false);
        htmlWriter.write();

    }
    catch (std::exception &error) {
        std::cout << error.what() << std::endl;
        return 0;
    }
}
