#include "configfilereader.h"

ConfigFileReader::ConfigFileReader(const std::string &f_name) : file_name(f_name)
{

}

void ConfigFileReader::read()
{
    std::string config_line;
    std::unique_ptr<std::ifstream> config_file = std::make_unique<std::ifstream>(file_name);
    if(config_file->is_open())
    {
        while(std::getline(*config_file.get(),config_line))
        {
            QRegExp pointsRegExp("^(\\d+,\\d+);?(\\d+,\\d+)$");// capture two groups with coordinates: 1,2;3,4
            if(pointsRegExp.indexIn(QString::fromStdString(config_line)) != -1)
            {
                Point upperLeftPoint(pointsRegExp.cap(1).split(",").first().toInt(),pointsRegExp.cap(1).split(",").last().toInt());
                Point bottomRightPoint(pointsRegExp.cap(2).split(",").first().toInt(),pointsRegExp.cap(2).split(",").last().toInt());
                rects_upper_left_bottom_right_points.push_back(std::make_pair(upperLeftPoint,bottomRightPoint));
            }
            else
            {
                rects_upper_left_bottom_right_points.clear();
                throw SYS::Error(QString("Invalid config file. All lines should match the template: 1,2;3,4"));
            }
        }
    }
    else
    {
        throw SYS::Error(QString("Unable to open file: %1").arg(QString::fromStdString(file_name)));
    }
}
