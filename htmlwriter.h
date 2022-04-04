#ifndef HTMLWRITER_H
#define HTMLWRITER_H

#include "filewriter.h"

/*
 *
 * Class for creating html document
 *
 */

class HtmlWriter : public FileWriter
{
    const std::string file_name;
public:
    HtmlWriter(const std::string& f_name);

    // FileWriter interface
    void write() override;
};

#endif // HTMLWRITER_H
