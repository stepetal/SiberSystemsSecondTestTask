#ifndef CONFIGFILEREADER_H
#define CONFIGFILEREADER_H

#include "filereader.h"
#include <iostream>
#include <fstream>
#include <memory>
#include "point.h"
#include <QString>
#include <QStringList>
#include <QRegExp>
#include "exceptions.h"

class ConfigFileReader : public FileReader
{
    std::string file_name;
    std::vector<std::pair<Point,Point>> rects_upper_left_bottom_right_points;
public:
    ConfigFileReader(const std::string& f_name = std::string());
    void setFileName(const std::string& f_name) { file_name = f_name; }
    std::vector<std::pair<Point,Point>> getRectsPoints(){ return rects_upper_left_bottom_right_points; }
    // FileReader interface
    void read() override;
};

#endif // CONFIGFILEREADER_H
