#include "htmlwriter.h"

HtmlWriter::HtmlWriter(const std::string& f_name) : file_name(f_name),show_grid(false)
{

}

void HtmlWriter::write()
{
    if(!rects_upper_left_bottom_right_points.empty())
    {
        int indent_level{0};
        std::unique_ptr<std::ofstream> html_file_stream = std::make_unique<std::ofstream>(file_name);
        html_file_stream->precision(3);
        if(html_file_stream->is_open())
        {
            std::string current_string("<!DOCTYPE html>\n");
            *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
            current_string = "<html>\n";
            *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
            indent_level++;
            current_string = "<head>\n";
            *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
            // document styling
            current_string = "<style>\n";
            indent_level++;
            *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
            current_string = "th, td {\n";
            indent_level++;
            *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
            if(show_grid)
            {
                current_string = "border: 1px solid black;\n";
                *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
            }
            current_string = "color: white;\n";
            *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
            current_string = "background-color: white;\n";
            *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
            current_string = std::string("font-size: ");
            *html_file_stream.get() << make_string_with_indent(current_string,indent_level) << GLB::get_row_height_in_vh_units(max_y) << std::string("vh;\n");
            current_string = std::string("width: ");
            *html_file_stream.get() << make_string_with_indent(current_string,indent_level) << GLB::get_column_width_in_percentage(max_x) << std::string("%;\n");
            current_string = "}\n";
            *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
            indent_level--;
            current_string = "</style>\n";
            *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
            indent_level--;
            current_string = "</head>\n";
            *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
            current_string = "<body>\n";
            *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
            indent_level++;
            // table formation
            current_string = "<table style=\"width: 100%;\"\n";
            *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
            indent_level++;
            for(int i = 0; i < max_x; ++i) // rows
            {
                current_string = "<tr>\n";
                *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
                indent_level++;
                for(int j = 0; j < max_y; ++j) // columns
                {
                    bool cell_belongs_to_rect{false};
                    // check, if current cell (i,j) is included in rectangle
                    // and if this so, set appropriate style
                    foreach(auto rect,rects_upper_left_bottom_right_points)
                    {
                        // if row is equal and current column is included in rect interval
                        if(((i >= std::get<0>(rect).getY()) && (i <= std::get<1>(rect).getY())) &&
                           ((j >= std::get<0>(rect).getX()) && (j <= std::get<1>(rect).getX())))
                        {
                            current_string = "<td style=\"background-color: " + rect_color + "; color: " + rect_color + ";\">1</td>\n";
                            *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
                            cell_belongs_to_rect = true;
                        }
                    }
                    if(!cell_belongs_to_rect)
                    {
                        current_string = "<td>1</td>\n";
                        *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
                    }
                }
                indent_level--;
                current_string = "</tr>\n";
                *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
            }
            indent_level--;
            current_string = "</table>\n";
            *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
            indent_level--;
            current_string = "</body>\n";
            *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
            indent_level--;
            current_string = "</html>\n";
            *html_file_stream.get() << make_string_with_indent(current_string,indent_level);
        }
        else
        {
            throw SYS::Error(QString("Unable to open file: %1").arg(QString::fromStdString(file_name)));
        }
    }
    else
    {
        throw SYS::Error("No rects available");
    }
}

std::string HtmlWriter::make_string_with_indent(const std::string& source_str, int indent_level)
{
    std::string indended_str;
    for(auto i = 0; i < indent_level; ++i)
    {
        indended_str.append(default_indent);
    }
    indended_str.append(source_str);
    return indended_str;
}
