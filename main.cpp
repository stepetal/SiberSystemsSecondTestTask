#include <QCoreApplication>

#include <iostream>
#include <QCommandLineParser>
#include <QVariantMap>
#include <QDebug>

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
                  QCoreApplication::translate("main", "color")}
              });
    if(!parser.parse(QCoreApplication::arguments()))
    {
        throw "parser error";
    }
    if (parser.isSet("version")){
      parser.showVersion();
      return;
    }
    if (parser.isSet("help")){
      parser.showHelp();
      return;
    }
    configMap["ConfigFilePath"] = parser.isSet("p") ? parser.value("p") : (QCoreApplication::applicationDirPath() + "/" + defaultconfigFileName);
    configMap["Color"] = parser.isSet("c") ? parser.value("c") : QString("blue");
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("DrawRect");
    QCoreApplication::setApplicationVersion("1.0");
    QCommandLineParser parser;
    QVariantMap cmdLineOptions;
    try
    {
        std::cout << "Try to parse arguments..." << std::endl;
        parseCommandLine(parser, cmdLineOptions);
        std::cout << "Parsing completed" << std::endl;
        foreach (auto key, cmdLineOptions.keys()) {
            std::cout << "Key is: " << key.toStdString() << " Value is: " << cmdLineOptions[key].toString().toStdString() << std::endl;
        }
    }
    catch (std::exception &error) {
        std::cout << error.what() << std::endl;
        return 0;
    }
    return a.exec();
}
