#ifndef HTMLWRITER_H
#define HTMLWRITER_H

#include "filewriter.h"
#include <QString>
#include <iostream>
#include "point.h"
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include "exceptions.h"
#include "globals.h"


/*
 *
 * Class for creating html document
 *
 */

const std::string default_indent("    ");

class HtmlWriter : public FileWriter
{
    std::string file_name;
    // maximum x and y values will be used as reper points in creating axis
    int max_x;
    int max_y;
    std::vector<std::pair<Point,Point>> rects_upper_left_bottom_right_points;
    bool show_grid;
    std::string rect_color;
public:
    HtmlWriter(const std::string& f_name = std::string());
    void setFileName(const std::string& f_name) { file_name = f_name; }
    void setRectsPoints(std::vector<std::pair<Point,Point>>&& rects_pts){ rects_upper_left_bottom_right_points = rects_pts; }
    void setMaxX(const int& m_x){ max_x = m_x; }
    void setMaxY(const int& m_y){ max_y = m_y; }
    void setRectColor(const std::string& color) { rect_color = color; }
    void setShowGrid(bool show_g){ show_grid = show_g; }
    // FileWriter interface
    void write() override;
private:
    std::string make_string_with_indent(const std::string &source_str, int indent_level);
};

#endif // HTMLWRITER_H
