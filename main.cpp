#include <QCoreApplication>

#include <iostream>
#include <QCommandLineParser>
#include <QVariantMap>
#include <QDebug>

#include <configfilereader.h>
#include "exceptions.h"

const QString defaultconfigFileName("config.txt");



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
    configMap["ConfigFilePath"] = parser.isSet("p") ? parser.value("p") : (QCoreApplication::applicationDirPath() + "/" + defaultconfigFileName);
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
    try
    {
        parseCommandLine(parser, cmdLineOptions);
        foreach (auto key, cmdLineOptions.keys()) {
            std::cout << "Key is: " << key.toStdString() << " Value is: " << cmdLineOptions[key].toString().toStdString() << std::endl;
            if(key == QString("ConfigFilePath"))
            {
                configFileReader.setFileName(cmdLineOptions[key].toString().toStdString());
                configFileReader.read();
                auto rects_points = configFileReader.getRectsPoints();
                std::cout << "Points have been successfully read" << std::endl;
                for(auto rect_points : rects_points)
                {
                    std::cout << "-------------Point start____________" << std::endl;
                    std::cout << "Upper left coordinates: " << std::get<0>(rect_points).getX() << "; " << std::get<0>(rect_points).getY() << std::endl;
                    std::cout << "Bottom right coordinates: " << std::get<1>(rect_points).getX() << "; " << std::get<1>(rect_points).getY() << std::endl;
                    std::cout << "-------------Point end____________" << std::endl;
                }
            }
        }
    }
    catch (std::exception &error) {
        std::cout << error.what() << std::endl;
        return 0;
    }
}
