#include "configfilereader.h"


ConfigFileReader::ConfigFileReader(const std::string &f_name) : file_name(f_name),max_x(0),max_y(0)
{

}

void ConfigFileReader::read()
{
    std::string config_line;
    std::unique_ptr<std::ifstream> config_file = std::make_unique<std::ifstream>(file_name);
    if(config_file->is_open())
    {
        std::vector<int> x_coords;
        std::vector<int> y_coords;

        while(std::getline(*config_file.get(),config_line))
        {
            QRegExp pointsRegExp("^(\\d+,\\d+);?(\\d+,\\d+)$");// capture two groups with coordinates: 1,2;3,4
            if(pointsRegExp.indexIn(QString::fromStdString(config_line)) != -1)
            {
                Point upperLeftPoint(pointsRegExp.cap(1).split(",").first().toInt(),pointsRegExp.cap(1).split(",").last().toInt());
                Point bottomRightPoint(pointsRegExp.cap(2).split(",").first().toInt(),pointsRegExp.cap(2).split(",").last().toInt());
                // validate points
                if((upperLeftPoint.getX()<bottomRightPoint.getX()) && (upperLeftPoint.getY() < bottomRightPoint.getY()))
                {
                    x_coords.push_back(bottomRightPoint.getX());
                    y_coords.push_back(bottomRightPoint.getY());
                    rects_upper_left_bottom_right_points.push_back(std::make_pair(upperLeftPoint,bottomRightPoint));
                }
                else
                {
                    throw SYS::Error(QString("Point with coordinates: %1,%2;%3,%4 is not valid").arg(upperLeftPoint.getX()).arg(upperLeftPoint.getY()).arg(bottomRightPoint.getX()).arg(bottomRightPoint.getY()));
                }
            }
            else
            {
                rects_upper_left_bottom_right_points.clear();
                throw SYS::Error(QString("Invalid config file. All lines should match the template: 1,2;3,4"));
            }
        }
        //get maximum elements and round them upper bound
        max_x = GLB::round_to_decade(*std::max_element(x_coords.begin(),x_coords.end()));
        max_y = GLB::round_to_decade(*std::max_element(y_coords.begin(),y_coords.end()));
    }
    else
    {
        throw SYS::Error(QString("Unable to open file: %1").arg(QString::fromStdString(file_name)));
    }
}
