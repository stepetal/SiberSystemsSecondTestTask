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
#include "algorithm"
#include "globals.h"


class ConfigFileReader : public FileReader
{
    std::string file_name;
    std::vector<std::pair<Point,Point>> rects_upper_left_bottom_right_points;
    // maximum x and y values will be used as reper points in creating axis
    int max_x;
    int max_y;
public:
    ConfigFileReader(const std::string& f_name = std::string());
    void setFileName(const std::string& f_name) { file_name = f_name; }
    std::vector<std::pair<Point,Point>> getRectsPoints(){ return rects_upper_left_bottom_right_points; }
    int getMaxX(){ return max_x; }
    int getMaxY(){ return max_y; }
    // FileReader interface
    void read() override;
};

#endif // CONFIGFILEREADER_H
